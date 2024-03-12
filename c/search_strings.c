// Lecture 03 - "Algorithms"
// program 26
// Linear search algorithm (searching strings)
// Pass in, the string to find at program execution as command-line argument

#include "cs50.c"
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Array to search in...
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    // get the string to search for...
    string s = argv[1];

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            // String found
            printf("Found!\n");
            return 0;
        }
    }

    // String not found!
    printf("Not found!\n");
    return 1;
}