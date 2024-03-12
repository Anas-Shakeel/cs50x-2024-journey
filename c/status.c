// Lecture 02 - "Arrays"
// program 20

#include "cs50.c"
#include <stdio.h>

int main(int argc, string argv[])
{
    // Status codes
    if (argc != 2)
    {
        // If invalid args, Return status code 1
        printf("Missing command-line argument.\n");
        return 1;
    }

    // Greet user
    printf("Hello, %s\n", argv[1]);
    return 0;
}