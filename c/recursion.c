// Lecture 03 - "Algorithms"
// program 30
// Program to draw mario-bricks (pyramid) from week 1. using RECURSIONS!

#include "cs50.c"
#include <stdio.h>

void draw(int n);

int main(void)
{
    // Get the height of pyramid...
    int height = get_int("Height: ");

    // Draw the pyramid...
    draw(height);

    return 0;
}

void draw(int n)
{
    // If nothing to draw, dont proceed , just return
    if (n <= 0)
    {
        return;
    }
    // Draw pyramid of height n-1
    draw(n - 1);

    // Print a single row of bricks of length n
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}