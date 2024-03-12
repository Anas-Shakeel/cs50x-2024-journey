// Lecture 02 - "Arrays"
// Lecture's program "Substitution"

/*
Q. What is the problem?
A. Problem is to make a encryption program that takes a key and a string, and
encrypts (enciphers) it using "Substitution" cipher.

Q. What is Substitution cipher?
A. A Substitution cipher is a cipher that substitute (that is replaces) every
letter from the plaintext (string to encrypt) with it's substitution letter.

For example:
    if the key is "ZXCVMNBASDFLKJHGQWERTYPOIU"
    and plaintext is "HI"
    we replace the each letter from plaintext into it's corresponding
        letter from the ciphertext.
    Since, 'H' is the 10th character in the alphabets
    We replace it with the 10th character in the key
        which is 'D'.
        So H becomes D
    we'll do the same for 'I', it is 11th character.
    replacing it with 11th character from key will give 'F'.
    Before encryption: HI
    After encryption: DF

Program's Specifications:
- implement this program in C.

- your program must accept a single command-line argument, the key to use
for the substitution. The key itself should be case-insensitive, so whether
any character in the key is uppercase or lowercase should not affect the
behaviour of the program.

- if your program is executed without any command-line argument or with more
than one command-line argument, your program should print an error message of
your choice, and return from 'main' a value of '1' (to signify an error)

- if the key is invalid (as by not containing 26 characters, containing
non-alphabetic characters, or not containing each letter once),
your program should print an error message and return '1'.

- your program must output 'plaintext: ' (without a newline) and then prompt
the user for a 'string' of plaintext.

- Your program must output 'ciphertext' (without a newline) followed by the
plaintext's corresponding ciphertext, with each alphabetical character in the
plaintext substituted for the corresponding character in the ciphertext;
non-alphabetical characters should be outputted unchanged.

- your program must preserve case:
    - capitalized letters, must remain capitalized letters
    - lowercase letters, must remain capitalized letters

- after outputting ciphertext, you should print a newline.
your program should then exit by returning 0 from 'main'.


TODO: What to do?
validate args (must be 2, 'program name' & 'key')
    if not valid, Halt + error

get key from args
validate the key (length = 26, each char must appear once, only alpha, )
    if not valid, Halt + error

// convert key to lower or uppercase (for case-insensitivity)
Get the plaintext
encipher the plaintext
    for each letter in plaintext:
        replace the ith letter of plaintext, with ith letter of key

    return the ciphertext

print the ciphertext


OUTPUT Example:
>> ./substitution YTNSHKVEFXRBAUQZCLWDMIPJGO
>> plaintext:  Hello!
ciphertext: Ehbbq!

>> ./substitution 1 2 3
Usage: ./substitution key

>> ./substitution
Usage: ./substitution key

 */

#include "cs50.c"
#include <ctype.h>
#include <stdio.h>

bool key_is_valid(string key);

int main(int argc, string argv[])
{
    // check the length (must be 26)
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // other validations (alpha + duplications)
    if (!key_is_valid(argv[1]))
    {
        // key is not valid
        printf("Usage: ./substitution key");
        return 1;
    }
    string key = argv[1];

    // Take a plaintext
    string plaintext = argv[2];

    // Encipher
    printf("ciphertext: ");
    int index;     // will hold the index of the plaintext's letter
    char ciphered; // will hold the cipher letter
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // if alphabetic, only then encipher
        if (isalpha(plaintext[i]))
        {
            // Get the index of letter (starting from 0)
            if (isupper(plaintext[i]))
            {
                index = plaintext[i] - 65;
                ciphered = toupper(key[index]);
            }
            else
            {
                index = plaintext[i] - 97;
                ciphered = tolower(key[index]);
            }
        }
        else
        {
            // otherwise, just use the current letter as is!
            ciphered = plaintext[i];
        }
        // Print the character
        printf("%c", ciphered);
    }
    printf("\n");

    return 0;
}
/*
#### Key is valid
Returns `true(1)` is the key is valid, `false(0)` otherwise
 */
bool key_is_valid(string key)
{
    int len = strlen(key);
    int dup_count; // to count duplicate characters

    // Each char must appear once
    for (int i = 0; i < len; i++)
    {
        // check if alphabetic
        if (!isalpha(key[i]))
        {
            return false;
        }

        dup_count = 0;
        // check if any other char matches
        for (int j = 0; j < len; j++)
        {
            // check if matching with key[i]
            if (key[j] == key[i])
            {
                dup_count++;
            }

            // check duplicate count
            if (dup_count == 2)
            {
                // Duplicate found, Return false
                return false;
            }
        }
    }

    // everything was fine, return true
    return true;
}
