# Lecture 06 - "Python"
# Program 05

def main():
    x = get_int("What's x? ")
    y = get_int("What's y? ")

    if x < y:
        print("X is less than y")
    elif x > y:
        print("X is greater than y")
    else:
        print("X is equal to y")


def get_int(prompt):
    # Get int from user and return
    while True:
        try:
            result = int(input(prompt))
            return result
        except ValueError:
            print("Expected an 'int', try again!")


if __name__ == '__main__':
    main()
