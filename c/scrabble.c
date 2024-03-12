// Lecture 02 - "Arrays"
// lecture's problem 01: Scrabble

/*
Scrabble :> A word puzzle game of two players

What is this game?
This is a word-puzzle game of two players where each player enters/types a
word that gets scored.

Each character/letter of the alphabet has a score such as:
A has a score of 1
B has a score of 3
C has score 3
D has 2
and so on!

So, if a player enters/types the word "CODE",
The score would be 7! because,
C = 3, O = 1, D = 2, E = 1
3 + 1 + 2 + 1 = 7
So the word "CODE" is worth 7 points.


Program to create:
In a file called 'scrabble.c', implement a program in C that determines
the winner of a short Scrabble-like game.
- Your program should prompt for input twice
    - Once for player 1 to input their word
    - Once for player 2 to input their word
Then, depending on which player scores the most points,
your program should either print "Player 1 wins!", "Player 2 wins!",
"Tie!" (in the event the two players score equal points)

Program output example:
Output 1:
    >> Player 1: Questions?
    >> Player 2: Questions!
    Tie!
Output 2:
    >> Player 1: red
    >> Player 2: wheelbarrow
    Player 2 wins!
Output 3:
    >> Player 1: COMPUTER
    >> Player 2: science
    Player 1 wins!

*/

#include "cs50.c"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Points associated with alphabet letters
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Prototypes
int compute_score(string w1);

// Program Entry
int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Missing command-line argument\n");
        return 1;
    }

    // TODO: 1. Prompt user for two words
    string word1 = argv[1];
    string word2 = argv[2];

    // TODO: 2. Compute the score of each word
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // printf("Score1: %i\nScore2: %i\n", score1, score2);

    // TODO: 3. Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

// Compute the score based on the words
int compute_score(string word)
{
    // Keep track of score
    int score = 0;

    // Iterate through the word 'w1'
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Get current char in w1
        char current_char = word[i];

        int index = 0;
        if (isupper(current_char))
        {
            // Add score from POINTS
            score += POINTS[current_char - 'A'];
        }
        else if (islower(current_char))
        {
            // Add score from POINTS
            score += POINTS[current_char - 'a'];
        }
        else
        {
            // Add zero to score
            score += 0;
        }
    }

    return score;
}