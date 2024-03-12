// Lecture 02 - "Arrays"
// program 19

#include "cs50.c"
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Greet the user
        printf("Hello, %s\n", argv[1]);
    }
    else 
    {
        printf("Hello, world\n");
    }

    // Printing all arguments
    for (int i = 0; i < argc; i++)
    {
        printf("Arg-%i: %s\n", i, argv[i]);
    }
    

    return 0;
}