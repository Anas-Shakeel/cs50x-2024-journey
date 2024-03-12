# Lecture 06 - "Python"
# Program 13


import sys

if len(sys.argv) != 2:
    print("Missing commandline args")
    sys.exit(1)


print(f"Hello, {sys.argv[1]}")
sys.exit(0)
