""" 
Given a sequence of DNA, implement a program that identifies to 
whom this sequence of DNA belongs.

Task:
    Write a program that takes a sequence of DNA and a CSV file containing the
    STR counts for a list of individuals and then output to whom the DNA belongs.

Specifications:
    - The program should require as it's first argument, name of a CSV file 
    containing STR counts for a list of individuals and should require as 
    it's second argument, the name of a text file containing the DNA sequence 
    to identify.
        - If your program is executed with the incorrect number of command-line
        arguments, your program should print an error message of your device.
        If the correct number of arguments provided, you may assume that the 
        first argument is indeed the filename of a CSVfile and that the second
        argument is the filename of a valid txt file.
    
    - Your program should open the CSV file and read it's contents into memory
        - You may assume that the first row of the CSVfile will be the column
        names. the first column will be the word `name` and the remaining 
        columns will be STR sequences themselves.
    
    - Your program should open the DNA sequence and read it's contents into memory.
    
    - For each of the STRs your program should compute the longest run of 
    consecutive repeats of the STRs in the DNA sequence to identify. Notice that 
    we've defined a helper function for you, `longest_match`, which will do just that.
    
    - If the STR counts match exactly with any of the individuals in CSV file,
    your program should print out the name of the individual.
        - You may assume that the STR counts will not match with more than 1 person.
        - If STR counts don't match with any person in CSV file, print `No match`
    
"""


import csv
import sys


def main():

    # Check for command-line usage
    if (len(sys.argv) != 3):
        print("Missing command-line arguments.")

    csvfile = sys.argv[1]
    seq_file = sys.argv[2]

    # Rows of dicts of individuals in CSV
    database = []
    # Read database file into database
    with open(csvfile, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(seq_file, "r") as seq:
        dna_seq = seq.read()

    # Extract the fieldnames (first is name)
    fieldnames = []
    for key in database[0].keys():
        fieldnames.append(key)

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for subseq in fieldnames[1:]:
        str_count = longest_match(dna_seq, subseq)
        str_counts[subseq] = str_count

    # Check database for matching profiles
    match_count = 0
    for row in database:
        for str_ in str_counts:
            if (int(row[str_]) == str_counts[str_]):
                match_count += 1

        # Check if all three were matched!
        if match_count == len(fieldnames[1:]):
            print(row[fieldnames[0]])
            sys.exit(0)
        else:
            match_count = 0

    # No matches were found!
    print("No match")
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
