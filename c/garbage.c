// Lecture 04 - "Memory"
// Program 05 - "Garbage.c"


/* 
By default, if we do no assign a value to a variable say (an int),
some garbage value gets assigned to them.

 */

#include <stdio.h>

int main(void)
{
    // Create an array to 1024 items, but do not assign values to them
    int scores[1024];

    // Just blindly, without initializing, print the their garbage values
    for (int i = 0; i < 1024; i++)
    {
        printf("%i\n", scores[i]);
    }
    

    return 0;
}