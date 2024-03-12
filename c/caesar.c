// Lecture 02 - "Arrays"
// lecture's problem 03: Caesar

/*
Program: caesar.c
Description:
    Takes plaintext & a key, and encrypts it using "Caesar's Cipher".

What is Caesar's cipher?
    This cipher was used by a greek general 'Julius Caesar'. This cipher is
    believed to be the first encryption method ever!

What it does?
    It shifts every letter in plaintext (unencrypted text) by 'k' letters
    in alphabets. (k is the key)

    For example:
    if we want to encrypt the message 'hi' using a key of 1
        caesar's cipher would shift the letters in plaintext by '1' letter.
        so, for plaintext of 'hi'
            Shift letters by 1
                h > i
                i > j
            ciphertext = 'ij' (ciphertext is the encrypted text)

How does it work?
    Take a plaintext e.g 'hello' and a key e.g 3:
    for every letter in plaintext
        shift letter by k


Program's Specifications:
    - Implement your program in c.

    - Your program must accept a single command-line argument, a non-negative
    integer. Let's call it 'k' for the sake of discussion.

    - if your program is executed without any command-line argument, your
    program should print an error message of your choice and return a value
    of '1' (which signifies an error)

    - if any of the characters of the command-line arg is not a decimal
    digit, your program should print the message 'Usage: ./caesar key'
    and return from 'main' a value of '1'

    - Do not assume that k will be less than or equal to 26. Your program should
    work for all non-negative integeral values of 'k' less than '2^31 - 26'.
    in other words, you don't need to worry if your program eventually breaks
    if the user chooses a value for 'k' that is too big or almost to big to
    fit in an 'int'. (Recall that an int can overflow) But, even if 'k' is
    greater than 26, alphabetical characters in your program's input should
    remain alphabetical chars in program's output.
        For instance, if 'k' is 27, 'A' should not become '\' even though '\'
        is 27 positions away from 'A' in ASCII. 'A' should become 'B', since 'B'
        is 27 positions away from 'A', provided you wrap around from 'Z' to 'A'

    - Your program must output 'plaintext: ', (with two spaces but without
    a newline) and then prompt the user for a 'string' of
    plaintext (using 'get_string').

    - Your program must output 'ciphertext: ', (with two spaces but
    without a newline) followed by the plaintext's corresponding ciphertext,
    with each alphabetical char in the plaintext "rotated" by k positions,
    non-alphabetical characters should be outputted changed.

    - Your program must preserve case:
        capitalized letters, though rotated, must remain capitalized letters.
        lowercase letters, though rotated, must remain lowercase letters.

    - After outputting ciphertext, you should print a newline.
    Your program should then exit by returning 0 from 'main'.


To Summarize:
If argc is not 1 (2 in my case since i'm taking plaintext as well):
    print "Custom error message."
    return 1

if key is negative OR non-decimal:
    print "Usage: ./caesar key"
    return 1


Expected Output example:
Run 1:
>> ./caesar 1
>> plaintext: Hi
>> ciphertext: Ij

Run 2:
>> ./caesar 1 2 3
Usage: ./caesar key

Run 3:
>> ./caesar HELLO
Usage: ./caesar key

Run 4:
>> ./caesar 26
>> plaintext: This is CS50.
>> ciphertext: This is CS50.


*/

#include "cs50.c"
#include <stdio.h>
#include <string.h>

char rotate_letter(char letter, int by);
char rotate(char letter, int by);
bool only_digits(string arg);

int main(int argc, string argv[])
{
    // Make sure argc is 2
    if (argc != 3)
    {
        // Exit the program
        printf("Command-line arguments: '2' expected, ('%i' were given).\n", argc - 1);
        return 1;
    }

    // Make sure every character in argv is a digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Get the key from command-line args
    int key = atoi(argv[1]); // Convert to int before assigning!!!

    // Store plaintext
    string plaintext = argv[2];
    printf("Plaintext:  %s\n", plaintext);

    printf("Ciphertext: ");
    // Rotate letters from plaintext (i.e encrypt)
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Rotate, then print the letter
        char cipher_letter = rotate(plaintext[i], key);
        // char cipher_letter = rotate_letter(plaintext[i], key);
        printf("%c", cipher_letter);
    }
    printf("\n");

    return 0;
}

/*
### Only Digits
Checks whether or not the letters in a string are infact digits. Returns a bool.
 */
bool only_digits(string arg)
{
    // Iterate throught the string
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        // if any digit is (not a digit)
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }

    return true;
}

/*
### Rotate Letter
Rotates the letter in ascii inrange 'A-Z' OR 'a-z'. and perfectly wraps
around the ASCII alphabets (both UPPER & lowercase).
 */
char rotate_letter(char letter, int by) // TODO: **BUG** (wierd behaviour on key 100)
{
    //  Formula == > ci = (pi + k) % 26

    // Check if letter is an alphabetical letter
    if (!isalpha(letter))
    {
        // letter is not alphabetic
        return letter;
    }

    // Add Key to number
    int result = (int)letter + by;

    // Check for range exceeding (for wrap-around)
    if ((isupper(letter) && result > 90) || (islower(letter) && result > 122))
    {
        // wrap-around
        result -= 26;
    }

    // printf(" cipher: %i=", result);

    return (char)result;
}

char rotate(char letter, int by)
{
    // Algorithm
    /*
    Enciphering the letter (aka. shifting by key)
    - Convert the letter into integer 0
        How? > if upper>(subtract by 65) || if lower>(subtract by 97)

    - Shift the letter using the formula "ci = (pi + k) % 26"
    - Add back the subtract integer
    - convert the result back into ascii

    */

    // Check if letter is an alphabetical letter
    if (!isalpha(letter))
    {
        // letter is not alphabetic
        return letter;
    }

    // Covvert letter into integer (starting from zero UPTO 26)
    int int_value = (int)letter;
    int result = 0; // will hold ciphered letter

    if (isupper(letter))
    {
        int_value -= 65;
        result = ((int_value + by) % 26) + 65;
    }
    else
    {
        int_value -= 97;
        result = ((int_value + by) % 26) + 97;
    }

    return (char)result;
}