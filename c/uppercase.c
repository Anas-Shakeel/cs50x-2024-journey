// Lecture 02 - "Arrays"
// program 17

#include "cs50.c"
#include <stdio.h>
#include <string.h>

int main(void)
{
    // String to convert to UPPERCASE
    string s = "Anas";
    printf("Before: %s\n", s);

    printf("Before: ");
    // Converting to UPPERCASE
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // For performance! store the current char
        // to avoid getting char again!
        char current_char = s[i];

        // If lowercase
        if (current_char >= 'a' && current_char <= 'z')
        {
            // Force it to uppercase
            printf("%c", current_char - 32);
        }
        else
        {
            printf("%c", current_char);
        }
    }
    printf("\n");
}