// Lecture 03 - "Algorithms"
// program 25
// Linear search algorithm (searching numbers)

#include "cs50.c"
#include <stdio.h>

int main(void)
{
    // Array to search in...
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    // get the number to search for...
    int n = get_int("Number: ");

    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == n)
        {
            // Number found
            printf("Found!\n");
            return 0;
        }
    }

    // Number not found!
    printf("Not found!\n");
    return 1;
}