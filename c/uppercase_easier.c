// Lecture 02 - "Arrays"
// program 18

#include "cs50.c"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string s = "Anas";
    printf("Before: %s\n", s);

    printf("After: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Store current character
        char current_char = s[i];
        // Convert to uppercase and print
        printf("%c", toupper(current_char));
    }
    printf("\n");

    return 0;
}