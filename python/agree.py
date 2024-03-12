# Lecture 06 - "Python"
# Program 06

s = input("Do you agree? ").lower()

if s in ["y", "yes"]:
    print("Agreed")
elif s in ["n", "no"]:
    print("Not agreed")
else:
    print("Please choose only (yes/no).")