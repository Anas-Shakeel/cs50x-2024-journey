from flask import Flask, render_template, request

# Creating a flask app, passing in, the name of the current py file
app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def index():
    # If method was POST
    if request.method == "POST":
        name = request.form.get("name")
        return render_template("greet.html", name=name)

    # If method was GET
    return render_template("index.html")
