// Lecture 04 - "Memory"
// Program 04 - "Memory.c"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Give me a '3 * (4 bytes)' of memory (although int can be of other sizes on other types of systems)
    int *x = malloc(3 * sizeof(int));

    // Store the values in the array
    x[0] = 72;
    x[1] = 73;
    x[2] = 33;

    // Free the memeory which was malloc'ked
    free(x);

    return 0;
}