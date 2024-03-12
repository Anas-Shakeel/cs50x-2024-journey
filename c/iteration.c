// Lecture 03 - "Algorithms"
// program 29
// Program to draw mario-bricks (pyramid) from 
// week 1. using ITERATION (loops)!

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
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i+1; j++)
        {
            printf("#");
        }
        printf("\n");
        
    }
    
}