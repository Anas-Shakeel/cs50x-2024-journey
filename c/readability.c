// Lecture 02 - "Arrays"
// lecture's problem 02: Readability

/*
Program: readability.c
What is it?
Takes an english sentence or paragraph and tells the reading level of it!

Output example:
>> Text: Congratulations! Today is your day. You're off to Great Places! -
    You're off and away!
Grade 3


How?
    Observations:
        Longer words means a higher reading level.
        More words per sentence means higher reading level.

There are formulas to calculate (based on any particular text), what grade level
might be appropriate for that text.
One such formula is "Coleman-Liau Index"

    Coleman-liau index:
        index = 0.0588 * L - 0.296 * S - 15.8
            - L : is the average number of letters per 100 words
            - S : is the average number of sentences per 100 words

    Applying "Coleman-liau index" formula:
        Figuring out how many letters per 100 words: (in the text)
            Count the number of uppercase and lowercase letters in text
                (to determine total number of letters)

        Figuring out how many words in a sentence: (in the text)
            - Count the number of words in a sentence.
            - A word is any sequence of characters separated by a space.

        Figuring out how many sentences: (in the text)
            For this problem,
                Any period, exclamation point or question mark -
                indicates a sentence

        Calculating:
            - You should have three values: letters, words and sentences
            Plug the values in the formula

Output:
    - Be sure to round score to the nearest whole number!
        (if index 2.8, round to 3)
    - Output should be "Grade X" (X is the grade level)
    - If index is less than 1,  output "Before Grade 1"
    - If index is greater than 16, output "Grade 16+"
    - If index in range 1 - 16, output "Grade X" (x is the index)

*/

// Test results
/*
All are working except these...

>> When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.
Grade 7 (expecting Grade 8)

>> In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.
Grade 8 (expecting Grade 7)

 */

#include "cs50.c"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int compute_index(int letters, int words, int sentences);

int main(int argc, string argv[])
{
    // Get the text from user
    if (argc != 2)
    {
        printf("Missing command-line argument.\n");
        return 1;
    }
    string text = argv[1];

    // Count the number of letters, words and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the "Coleman-liau index"
    int index = compute_index(letters, words, sentences);

    // Print the grade level
    if (index < 1)
    {
        // Less than 1
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        // Greater than 16
        printf("Grade 16+\n");
    }
    else
    {
        // Inrange
        printf("Grade %i\n", index);
    }

    return 0;
}

/*
### Count letters
Count the number of alphabetic letters in text.
*/
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            // If letter is alphabetical
            letters++;
        }
    }
    return letters;
}

/*
### Count words
Count the number of words in text
##### bug: current version does not tolerate multiple spaces
*/
int count_words(string text)
{
    int words = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            // if encountered a space, end of word
            words++;
        }
    }

    return words + 1;
}

/*
### Count Sentences
Count the number of sentences in text
 */
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            // end of sentence
            sentences++;
        }
    }

    return sentences;
}

/*
### Compute Index
Computes the "Coleman-Liau Index" based on number of
letters, words and sentences
*/
int compute_index(int letters, int words, int sentences)
{
    // Calculate L and S
    float L = (letters / (float)words) * 100;
    float S = (sentences / (float)words) * 100;

    // Plug values into the "Coleman-Liau Index" formula
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}