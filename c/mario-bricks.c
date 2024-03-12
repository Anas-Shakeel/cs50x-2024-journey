#include <stdio.h>

int main(void)
{
    // Take input (positive integer greater than 1)
    int n;
    do
    {
        printf("Enter size of grid: ");
        scanf("%i", &n);
    } while (n <= 1);

    // Print n-by-n grid of bricks
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}