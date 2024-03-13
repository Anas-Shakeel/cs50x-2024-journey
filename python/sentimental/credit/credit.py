""" 
Write a program that prompts user for a credit card number and then reports 
(via print) whether it is a valid AMERICAN EXPRESS, MASTERCARD, or VISA
card number, exactly as you did in Problem Set 1.


Demo:
>> python credit.py
Number: 378282246310005
AMEX
>> python credit.py
Number: 5555555555554444
MASTERCARD
>> python credit.py
Number: 123456789
INVALID


Program Specification:
    - So that cs50 can automate some of our code, they ask that our program's
    last line of output be `AMEX\n` or `MASTERCARD\n` or `INVALID\n` etc.
    - For simplicity, we may assume that the user's input will entirely be
    numeric.
    - Best to use `get_int` or `get_string` from cs50 library to get 
    users input, depending on how you decide to implement this one .
    
    - It's possible to use regular expressions to validate user's input,
    using `re` module & check whether the user's input is indeed a sequence
    of digits of correct length.
    
    
Identifying the Credit card number:

All credit card numbers:
    have 13 - 16 digits
    All numeric values (numbers)
    No spaces, hyphens, or underscores
    All numbers start with a pattern (specific to company)

AMEX:
    - 15 digits
    - Starts with (34, 37)

MASTERCARD:
    - 16 digits
    - Starts with (51, 52, 53, 54, 55)

VISA:
    - 13 - 16 digits
    - Starts with (4)


There's also a `checksum` built into these numbers which lets the computers or 
human, to detect typos in the numbers.

Luhn's Checksum Algorithm:
    - Multiply every other digit by 2, starting with the 2nd-last digit,
    then add those product's digit together.
    - Add the sum to the sum of the digits that weren't multiplied  by 2
    - if the total's last digit is 0 (total modulo 10 == 0), the number is valid!


TODO
Prompt for the card number
Apply checksum algorithm
IF passed:
    Recognize the company
    print the company
ELSE:
    print INVALID


Test numbers:
AMEX:       378282246310005
MASTERCARD: 5555555555554444
VISA:       4003600000000014
INVALID:    1234567890

"""

import sys


def main():
    # Get the number
    number: str = get_string("Number: ")

    if number == None:
        print("INVALID")
        sys.exit(1)

    # Apply Checksum
    if (not checksum(number)):
        # Failed checksum
        print("INVALID")
        sys.exit(1)

    # Recognize the number
    recognized: str = recognize(number)

    # Print the company or INVALID
    print(recognized)

    sys.exit(0)


def get_string(prompt: str):
    # Get the input
    temp: str = input(prompt)

    # Numeric validation
    if not temp.isdigit():
        # All characters are not Numeric
        return None

    # Length validation
    if ((len(temp) >= 13) and (len(temp) <= 16)):
        return temp
    else:
        return None


# Checksum Algorithm
def checksum(number: str):
    last_digit: int = int(number[-1])

    sum_1: int = 0  # Sum of multiplied digits
    sum_2: int = 0  # Sum of non-multiplied digits

    # Iterate through the number.reversed
    for i, num in enumerate(number[:-1][::-1]):
        if (i % 2 == 0):  # take every even indexed digit
            # Multiply by 2 (t for temporary)
            t: int = int(num) * 2

            # If num is a 2-digit number, sum individually
            for j in str(t):
                # add j in sum_1
                sum_1 += int(j)
        else:
            # For odd indexed numbers, sum as it is
            sum_2 += int(num)

    # Add together
    result = sum_1 + sum_2 + last_digit

    # Check the last digit of result
    return True if (result % 10 == 0) else False


# Recognize the company of credit number
def recognize(number: str):
    length = len(number)

    if (length == 15) and (number[:2] in ["34", "37"]):
        # AMEX card
        return "AMEX"
    elif (length == 16) and (number[:2] in ["51", "52", "53", "54", "55"]):
        # MASTERCARD
        return "MASTERCARD"
    elif (length in range(13, 17, 1)) and (number[0] == "4"):
        # VISA
        return "VISA"
    else:
        # INVALID
        return "INVALID"


if __name__ == '__main__':
    main()
