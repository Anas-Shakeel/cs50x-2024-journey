// Meow.c
// Printing "Meow" three times on screen

#include <stdio.h>

void meow(void);
void meow_times(int n);

int main(void)
{
    // Meowing using while loop
    /*
    int i = 0;
    while (i < 3)
    {
        printf("Meow\n");
        i++;
    }
     */

    // Meowing using for loop
    /*
    for (int i=0; i<3; i++){
        printf("Meow\n");
    }
     */

    // Meowing using function
    /*
    for (int i = 0; i < 3; i++)
    {
        meow();
    }
     */

    // Meowing using only function
    meow_times(3);

    return 0;
}

void meow(void)
{
    printf("Meow\n");
}

void meow_times(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Meow\n");
    }
}