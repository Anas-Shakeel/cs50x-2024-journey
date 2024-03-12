// Lecture 02 - "Arrays"
// program 16

#include "cs50.c"
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = "Anas";
    printf("Output: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", s[i]);
    }

    printf("\n");
    
}