# Lecture 06 - "Python"
# Program 11

people = {
    "carter": "+1-617-495-1000",
    "david": "+1-617-495-1000",
    "john": "+1-949-468-2750",
}

name = input("name: ")

if name in people:
    print(f"Name: {name}, Number: {people[name]}")
else:
    print("Not found")
