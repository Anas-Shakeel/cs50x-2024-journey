# Commit message:
# Sentimental Readability PSET03 WEEK06


"""
Write a program that asks the user to type in some text, and then outputs the
grade level of that text, according to the Coleman-liau formula, exactly as you
did in Problem Set 02.


Specifications:
    Recall that the coleman-liau index is calculated as:
        0.0588 * L - 0.296 * S - 15.8
            Where:
                L is the avg number of letters per 100 words in the text
                S is the avg number of sentences per 100 numbers in the text

    User `get_string` from cs50 library, to get the input from user, and
    `print` to output the grade level.

    Your program should count the number of letters, words, and sentences in
    the text. You may assume that a letter is:
            - any alphabet (lower/upper)

        any sequence of characters separated by space should count as word
        any period,exclamation mark or question mark marks the end of sentence

    Your program should print as output `Grade X` where x is the grade level
    computed by Coleman-liau formula, rounded to the nearest integer.

    If resulting index number is 16 or higher, program should output "Grade 16+"
    If index number is less than 1, program should output "Before Grade 1"


Test cases:
    Before Grade 1:
        One fish. Two fish. Red fish. Blue fish.

    Grade 2:
        Would you like them here or there? I would not like them here or there. I would like them anywhere.

    Grade 3:
        Congratulations! Today is your day. You're off to great places! You're off and away!
    
    Grade 7:
        In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.
    
    Grade 16+:
        A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays, of integers, finite families of finite sets, boolean formulas and elements of other countable domains.
    
"""


def main():
    # Get the text
    text: str = input("Text: ")

    # Count letters, words & sentences
    l: int = count_letters(text)
    w: int = count_words(text)
    s: int = count_sentences(text)

    # Coleman-liau formula
    index: int = coleman_index(l, w, s)

    # Print the grade
    print(grade(index))


def coleman_index(letters: int, words: int, sentences: int) -> int:
    """ Implementation of coleman-liau index """
    L: float = (letters / float(words)) * 100
    S: float = (sentences / float(words)) * 100

    # Apply Coleman-liau formula
    index: int = round(0.0588 * L - 0.296 * S - 15.8)

    return index


def count_letters(text: str) -> int:
    # Break the text in individual letters
    letters: list[str] = list(text)

    counter = 0
    # Iterate through the words
    for letter in letters:
        # Letter is alphabetic
        if letter.isalpha():
            counter += 1

    return counter


def count_words(text: str) -> int:
    # Break the text in individual words, then return length of them
    return len(text.split())


def count_sentences(text: str):
    counter: int = 0
    # Iterate through the text (letter by letter)
    for letter in text:
        if (letter in ['.', '!', '?']):
            # End of a sentence
            counter += 1

    return counter


def grade(index: int) -> str:
    grade: str = ""

    # Process grades
    if (index < 1):
        grade = "Before Grade 1"
    elif (index > 16):
        grade = "Grade 16+"
    else:
        grade = f"Grade {index}"

    return grade


if __name__ == '__main__':
    main()
