// Lecture 04 - "Memory"
// Program 08 - "Phonebook.c"

/*
A program that creates a new csv file and writes the name & number in it
 */

#include "cs50.c"
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Open a file (or in this case, Create a file) called 'phonebook.csv'
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }

    // Name & number to write in the file
    char *name = "Anas";
    char *number = "+246-654-456"; // some garbage number, **not mine ;)**

    // Write the name & number in the file
    fprintf(file, "%s,%s\n", name, number);
    // Close the file
    fclose(file);

    return 0;
}