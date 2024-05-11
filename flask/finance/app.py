from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


def get_username(value):
    """ Just returns the username """
    return db.execute("SELECT username FROM users WHERE id=?", session['user_id'])[0]['username']

app.jinja_env.filters["USERNAME"] = get_username

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get the the user_data or purchase track
    rows = db.execute("SELECT symbol, price, shares from purchase_track where user_id=?", session['user_id'])

    # Calculate the remaining after subtracting the shares' price
    cash = db.execute("SELECT cash FROM users where id=?", session['user_id'])[0]['cash']
    stock_total = 0
    for row in rows:
        stock_total += row['price'] * row['shares']

    return render_template("index.html", rows=rows, cash=cash, stock_total=cash+stock_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get the symbol & shares
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Symbol Required!")
        # Check if symbol is valid
        lookup_result = lookup(symbol)
        if not lookup_result:
            return apology("Invalid Symbol!")

        if (not shares):
            return apology("Invalid share value")
        try:
            shares = int(shares)
            if int(shares) <= 0:
                raise ValueError
        except ValueError:
            return apology("Invalid shares value")

        # Get the current user's  idm, username and cash value
        user_data = db.execute("SELECT id, username, cash FROM users WHERE id=?", session['user_id'])[0]

        # Confirm if user can purchase the shares
        if (user_data['cash'] < (shares*lookup_result['price'])):
            return apology("Not Enough Cash!")

        # Reduce the cash in user's account
        db.execute("UPDATE users SET cash=? WHERE id=?", user_data['cash'] - (shares * lookup_result['price']), user_data['id'])

        # Store the data into purchase_track table (purchase history)
        # Get the row from the database
        rows = db.execute("SELECT symbol, shares, price FROM purchase_track WHERE user_id=? AND symbol=?", user_data['id'], symbol.upper())
        if not rows:
            # Create a row and store the data
            db.execute("INSERT INTO purchase_track(user_id, username, shares, symbol, price, transacted) VALUES(?, ?, ?, ?, ?, strftime('%Y-%m-%d %H:%M:%S', 'now'))", user_data['id'], user_data['username'], shares, lookup_result['symbol'], lookup_result['price'])

        else:
            # Update the existing row and store the data
            db.execute("UPDATE purchase_track SET shares=?, price=?, transacted=strftime('%Y-%m-%d %H:%M:%S', 'now') WHERE user_id=? AND symbol=?", shares+rows[0]['shares'], lookup_result['price'], session['user_id'], symbol.upper())


        # Also store the data into history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, status, transacted) VALUES (?, ?, ?, ?, ?, strftime('%Y-%m-%d %H:%M:%S', 'now'))", user_data['id'], symbol.upper(), shares, lookup_result['price'], "BOUGHT")

        # If all goes well, user will be redirected to homepage
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get the history data of current user from database
    rows = db.execute("SELECT * FROM history WHERE user_id=?", session['user_id'])

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Get the symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol Required!")

        lookup_result = lookup(symbol)
        if not lookup_result:
            return apology("Invalid Symbol!")

        return render_template("quoted.html", lookup_result=lookup_result)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        ILLEGAL_CHARS = [' ', '\\','/',':', ';','*','?','"', "'", '`', '<','>','|', '%', '//', '-', '=', '+', ',']
        # Get the username and password & confirm password
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        # Username validation:
        # Length: 4-20
        # Chars : no illegal chars allowed
        # non-empty non-existing
        if not username:
            # username is blank
            return apology("Username is required!")
        if not (len(username) >= 4):
            return apology("Must have atleast 4 characters")
        if not (len(username) <= 20):
            return apology("Maximum 20 characters allowed")
        for char in ILLEGAL_CHARS:
            if char in username:
                return apology(f" {char} not allowed.")

        # check the database if username exists!
        rows = db.execute("SELECT * FROM users WHERE username=?", username)
        if len(rows) != 0:
            return apology("Username already exist!")

        # Password Validation:
        # Length: 4-20
        # Chars : no spaces allowed
        if not password:
            return apology("Password is required!")
        if not confirm_password:
            return apology("Confirm your password")
        if (password != confirm_password):
            return apology("Passwords do not match!")
        if len(password) > 20 or len(password) < 4:
            return apology("Password length: 4-20")
        if ' ' in password:
            return apology("Spaces are not allowed")

        # Register the user
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get the symbols
    symbols = db.execute("SELECT DISTINCT symbol FROM purchase_track WHERE user_id=?", session['user_id'])

    if request.method == "POST":
        # Get the symbol from user
        symbol = request.form.get("symbol")

        # symbol not in symbols
        if not symbol:
            return apology("Invalid Symbol!")

        # Get the shares value from user
        shares = int(request.form.get("shares"))
        shares_info = db.execute("SELECT price, shares from purchase_track WHERE user_id=? AND symbol=?", session['user_id'], symbol.upper())
        shares_owned = shares_info[0]['shares']
        if shares <= 0:
            return apology("Invalid Shares!")
        # shares must be owned!
        if shares > shares_owned:
            return apology("Not enough shares!")

        # Update the database
        cash_owned = db.execute("SELECT cash from users where id=?", session['user_id'])[0]['cash']
        lookup_result = lookup(symbol)
        total_stock_price = lookup_result['price'] * shares
        db.execute("UPDATE users SET cash=? WHERE id=?", cash_owned + total_stock_price, session['user_id'])


        # If shares are the same as shares_owned, just remove whole row
        if shares == shares_owned:
            db.execute("DELETE from purchase_track WHERE user_id=? AND symbol=?", session['user_id'], symbol.upper())
        # If they are less, Update and remove some shares
        else:
            db.execute("UPDATE purchase_track SET shares=shares-? WHERE user_id=? AND symbol=?", shares, session['user_id'], symbol.upper())

        # Also store the data into history table
        db.execute("INSERT INTO history (user_id, symbol, shares, price, status, transacted) VALUES (?, ?, ?, ?, ?, strftime('%Y-%m-%d %H:%M:%S', 'now'))", session['user_id'], symbol.upper(), shares, lookup_result['price'], "SOLD")

        return redirect("/")

    else:
        return render_template("sell.html", symbols=symbols)

@app.route("/account")
@login_required
def account():
    user_data = db.execute("SELECT * FROM users WHERE id=?", session['user_id'])[0]
    cash = user_data['cash']
    username = user_data['username']

    return render_template("account.html", user_cash=f"{cash:,.2f}", username=username)


@app.route("/change_username", methods=["GET", "POST"])
@login_required
def change_username():
    ILLEGAL_CHARS = [' ', '\\','/',':', ';','*','?','"', "'", '`', '<','>','|', '%', '//', '-', '=', '+', ',']
    if request.method == "POST":
        # Get the username from user
        username = request.form.get("username")

        # Validate username:
        # Length: 4 - 20
        # Chars : everything allowed except ILLEGAL_CHARS
        # Non-empty + non-existing
        if not username:
            return apology("Username Required!")
        if not (len(username) >= 4):
            return apology("Must have atleast 4 characters")
        if not (len(username) <= 20):
            return apology("Maximum 20 characters allowed")
        for char in ILLEGAL_CHARS:
            if char in username:
                return apology(f" {char} not allowed.")
        # Check if username already exists in database
        all_users = db.execute("SELECT * from users WHERE username=?", username)
        if len(all_users) != 0:
            return apology(f"username '{username}' already exists!")

        # Query and update the username for current user
        db.execute("UPDATE users SET username=? WHERE id=?", username, session['user_id'])
        return redirect("/account")
    else:
        return apology("Doesn't work like that!")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        # Get the passwords from user
        password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")

        # Validate passwords
        # non-empty
        # Length: 4 - 20
        # Chars : everything except space is allowed!
        # password and confirm_password must match!

        if (not password) or (not confirm_password):
            return apology("Enter a password, then confirm it!")
        if password != confirm_password:
            return apology("Passwords must match!")
        if len(password) > 20 or len(password) < 4:
            return apology("Password length: 4-20")
        if ' ' in password:
            return apology("Spaces are not allowed")

        # Update the hash of user's password to new hash
        db.execute("UPDATE users SET hash=? WHERE id=?", generate_password_hash(password), session['user_id'])

        return redirect("/account")
    else:
        return apology("Doesn't work like that!")

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        # Get the cash to add
        cash_to_add = request.form.get("cash_to_add")
        # Validate cash value
        # Non-empty numeric
        # Max value to enter: $1 - $25k | 25,000 | 25000
        # Max cash to store in DB: $ 1 million | 1,000,000 | 1000000
        if not cash_to_add:
            return apology("Transaction Failed! Enter Cash.")

        # convert to float
        try:
            cash_to_add = float(cash_to_add)
        except ValueError:
            return apology("Cash must be numeric!")

        if cash_to_add < 1:
            return apology("Min Transaction Limit: $1")
        if cash_to_add > 25000:
            return apology("Max Transaction Limit: $25k")
        # Get the cash owned
        cash_owned = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]['cash']
        new_cash = cash_owned + cash_to_add
        if new_cash > 1000000:
            return apology("That's Enough! no more cash please.")

        # Add cash to user's account (database)
        db.execute("UPDATE users SET cash=? WHERE id=?", new_cash, session['user_id'])

        return redirect("/account")
    else:
        return apology("Doesn't work like that!")

@app.route("/delete_account", methods=["GET", "POST"])
@login_required
def delete_account():
    if request.method == "POST":
        # Get the userid from session
        user_id = session['user_id']
        # Get the password
        password = request.form.get("password")
        if not password:
            return apology("Password is required!")
        # Check if password matches with database
        user_password = db.execute("SELECT hash FROM users WHERE id=?", user_id)[0]['hash']
        if not check_password_hash(user_password, password):
            return apology("Incorrect Password! Try Again.")

        # Delete current user's account
        db.execute("DELETE FROM history WHERE user_id=?", user_id)
        db.execute("DELETE FROM purchase_track WHERE user_id=?", user_id)
        db.execute("DELETE FROM users WHERE id=?", user_id)

        return redirect("/login")
    else:
        return apology("Doesn't work like that!")
