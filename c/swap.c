// Lecture 04 - "Memory"
// Program 06 - "Swap.c"

/*
Swap values of two integers

 */

#include <stdio.h>
#include <stdlib.h>

void swap_incorrect(int a, int b);
void swap_correct(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    // Swap with incorrect function
    printf("Swapping with 'swap_incorrect'\n");
    printf("Before Swap: x is %i and y is %i\n", x, y);
    swap_incorrect(x, y);
    printf("After Swap: x is %i and y is %i\n", x, y);

    printf("\n");

    // Swap with correct function
    printf("Swapping with 'swap_correct'\n");
    printf("Before Swap: x is %i and y is %i\n", x, y);
    swap_correct(&x, &y);
    printf("After Swap: x is %i and y is %i\n", x, y);

    return 0;
}

/*
### Swap Incorrect
This function will not swap the values passed (in-place)
Because the values are (passed by value) so instead of the actual variable,
it copies the values of those variables and does the swapping on them,
without returning the values!

 */
void swap_incorrect(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

/*
### Swap Correct
This function will swap the passed values.
Because this function takes pointers to the actual variables to
 swap, instead of just the values.
 */
void swap_correct(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}