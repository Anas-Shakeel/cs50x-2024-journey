# Lecture 06 - "Python"
# Program 09


def main():
    while True:
        n = int(input("height: "))
        if (n > 0):
            break
    
    for i in range(n):
        for j in range(n):
            print("#", end="")
        print()

if __name__ == '__main__':
    main()