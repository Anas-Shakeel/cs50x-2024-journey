// Lecture 02 - "Arrays"

#include <stdio.h>

// Used as the length of array
const int N = 3;

// Prototypes
int get_int(char *prompt);
float average(int length, int array[]);

int main(void)
{
    int scores[N];

    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", average(N, scores));
}

int get_int(char *prompt)
{
    int temp;
    printf(prompt);
    scanf("%i", &temp);
    return temp;
}

float average(int length, int array[])
{
    // Find the average of array's items
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }

    return sum / (float)length;
}