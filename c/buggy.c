// Lecture 02 - "Arrays"

#include <stdio.h>

void print_column(int h);

int main(void)
{
    int h;
    printf("Enter height: ");
    scanf("%i", &h);
    print_column(h);
    return 0;
}

void print_column(int h)
{
    for (int i = 0; i < h; i++)
    {
        printf("#\n");
    }
}