# Lecture 06 - "Python"
# Program 04


def main():
    x = get_int("x: ")
    y = get_int("y: ")

    print(x + y)


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            pass

main()
