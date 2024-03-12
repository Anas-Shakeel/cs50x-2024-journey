// Agree.c
// Program to take a char as input and tell agreed or not based on that input.

#include <stdio.h>

int main(void)
{
    char c;
    // Take input chars
    printf("Do you agree? (y/n) ");
    scanf("%c", &c);

    // Check if agreed
    if (c == 'y' || c == 'Y')
    {
        printf("Agreed!\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Not Agreed!\n");
    }

    return 0;
}