""" 
Program to create/implement:
    Mario (from week01 "C")

Implement a program that recreates the half-pyramid using hashes (#) for blocks,
exactly as you did in 'Problem Set 1'.

Program output:
>> Height: 3
  #  #
 ##  ##
###  ###

Specification:
    - Prompt user using get_int(from cs50) for the half-pyramid's height, a 
    positive integer between 1 and 8 inclusive.
    
    "GAP should be 2 spaces"
    
    - If user fails to provide a positive integer (no greater than 8), you 
    should reprompt.
    - Then generate the desired half-pyramids
    - 


height = 3

print (height-1 spaces)(i+1 Hashes)(2 space gap)(i+1 Hashes)

"""


# Uncomment below line
# from cs50 import get_int

def main():
    # Get the height from the user
    height = get_int("Height: ")

    # Create the half-pyramid
    for i in range(height):
        # Print spaces
        print(" "*(height-(i+1)), end="")

        # Print hashes
        print("#"*(i+1), end="")

        # Print 2-space GAP
        print("  ", end="")

        # Print hashes again
        print("#"*(i+1))


# Accept integer inputs between 1 - 8 inclusive
def get_int(prompt):
    while True:
        try:
            temp = int(input(prompt))
            if (temp > 0) and (temp <= 8):
                return temp
        except ValueError:
            pass


if __name__ == '__main__':
    main()
