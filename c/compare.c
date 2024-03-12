// Compare.c
// Program to take inputs as integers and compare the integes


#include <stdio.h>

int main(void)

{
    int x, y;
    // Taking inputs
    printf("What's x? ");
    scanf("%i", &x);

    printf("What's y? ");
    scanf("%i", &y);

    // Printing inputs
    printf("x:%i, y:%i\n", x, y);

    // Comparing inputs
    if (x < y)
    {
        printf("X is less than Y.\n");
    }
    else if (x > y)
    {
        printf("X is greater than Y.\n");
    }
    else
    {
        printf("X is equal to Y.\n");
    }

    return 0;
}