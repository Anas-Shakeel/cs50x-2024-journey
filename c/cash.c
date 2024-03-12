/*
$1.00 == 100 cents
$0.50 == 50 cents

Quarters == 25 cents
Dimes == 10 cents
Nickels == 5 cents
Pennies == 1 cent

Problem to be solved:
Yield the fewest coins possible!

If some customer is owed "41 cents", the biggest first bite out
of it will be "25 cents".

Now the "41 cents" problem is down to "16 cents" problem, Since 41 - 25 = 16

Now, another "25 cents" would be too big, so the greedy cashier would now move
onto the next biggest first bite, which is "10 cents"

Leaving him/her with a "6 cents" problem.
Next bite would be "5 cent" followed by a "1 cent"
Problem solved!

the customer recieves a quarter, a dime, a nickel and a penny! 4 coins in total.

 */

#include <stdio.h>

int get_int(char *message);
int find_coins(int cents);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    } while (cents < 0);

    // Find total coins to give
    int coins = find_coins(cents);

    // Print the coins
    printf("%i\n", coins);
}

int get_int(char *message)
{
    int temp;
    printf(message);
    scanf("%d", &temp);
    return temp;
}

int find_coins(int cents)
{
    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(cents);
    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate how many dimes you should give customer
    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);

    // Calculate how many nickels you should give customer
    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);

    // Calculate how many pennies you should give customer
    int pennies = calculate_pennies(cents);
    cents = cents - (pennies * 1);

    // Sum the number of quarters, dimes, nickels, and pennies used
    int coins = quarters + dimes + nickels + pennies;
    return coins;
}

int calculate_quarters(int cents)
{
    // Calculate how many quarters should be given?
    int quarters = cents / 25;
    return quarters;
}

int calculate_dimes(int cents)
{
    // Calculate how many quarters should be given?
    int dimes = cents / 10;
    return dimes;
}

int calculate_nickels(int cents)
{
    // Calculate how many quarters should be given?
    int nickels = cents / 5;
    return nickels;
}

int calculate_pennies(int cents)
{
    // Calculate how many quarters should be given?
    int pennies = cents / 1;
    return pennies;
}