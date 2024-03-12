// Lecture 02 - "Arrays"

#include "cs50.c"
#include <stdio.h>

int string_length(string s);

int main(void)
{
    // String to find the length of...
    string name = "Anas";
    int length = string_length(name);
    printf("Length: %i", length);

    return 0;
}

/* 
### String Length
Find the length of any string
*/
int string_length(string s)
{
    // Find the length of a string
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }

    // Return the length
    return len;
}