// Program to print a pyramid pattern
/*
Problem:
Print a pyramid of height (1-8) inclusive, with a gap of 2 hashes
inbetween both sides.

Example:
Enter height: 3
  #
 ##
###

*/

#include <stdio.h>

int get_int(char *message);
void print_pyramid(int height);
void print_bricks(int bricks);
void print_spaces(int spaces);

int main(void)
{
    // Take height input
    int height;
    do
    {
        height = get_int("Enter height: ");
    } while (height < 1 || height > 8);

    // Print a pyramid of height `height`
    print_pyramid(height);

    return 0;
}

int get_int(char *message)
{
    int temp;
    printf(message);
    scanf("%d", &temp);
    return temp;
}

void print_pyramid(int height)
{
    // Print pyramid
    for (int i = 0; i < height; i++)
    {
        // Print spaces
        print_spaces(height - i);
        // Print row of bricks
        print_bricks(i + 1);
        // Print Gap
        print_spaces(3);
        // Print row of bricks
        print_bricks(i + 1);

        // Print newline
        printf("\n");
    }
}

void print_spaces(int spaces)
{
    // Print spaces
    for (int i = 1; i < spaces; i++)
    {
        printf(" ");
    }
}

void print_bricks(int bricks)
{
    // Print bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}