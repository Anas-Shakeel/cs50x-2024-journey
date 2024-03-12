// Add.c
// A simple addition program which adds two integers

#include <stdio.h>

int add(int x, int y);

int main(void)
{
    // Take inputs
    int x;
    printf("x: ");
    scanf("%i", &x);
    int y;
    printf("y: ");
    scanf("%i", &y);

    printf("%i + %i = %i", x, y, add(x, y));

    return 0;
}

int add(int x, int y)
{
    return x + y;
}