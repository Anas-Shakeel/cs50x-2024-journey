// Lecture 03 - "Algorithms"
// program 27
// Phonebook implementations

#include "cs50.c"
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    string names[] = {"Carter", "David", "John"};
    string numbers[] = {"+1-617-495-1000", "+1-617-495-1000", "+1-949-468-2750"};

    // Name to search for...
    string name = argv[1];

    // Search...
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            // Name matches...
            printf("Found! %s\n", numbers[i]);
            return 0;
        }
    }

    printf("Not found!\n");
    return 1;

    return 0;
}