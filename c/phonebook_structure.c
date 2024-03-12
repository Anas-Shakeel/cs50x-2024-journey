// Lecture 03 - "Algorithms"
// program 28
// Phonebook Structure implementations (creating my own data type)

#include "cs50.c"
#include <stdio.h>
#include <string.h>

// Person datatype (stores a name & a number)
typedef struct
{
    string name;
    string number;
} person;

int main(int argc, string argv[])
{
    // string names[] = {"Carter", "David", "John"};
    // string numbers[] = {"+1-617-495-1000", "+1-617-495-1000", "+1-949-468-2750"};

    // Creating an array of 3 persons
    person people[3];

    // Initializing array
    people[0].name = "Carter";
    people[0].number = "+1-617-495-1000";

    people[1].name = "David";
    people[1].number = "+1-617-495-1000";

    people[2].name = "John";
    people[2].number = "+1-949-468-2750";

    // Name to search for...
    string name = argv[1];

    // Search...
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            // Name matches...
            printf("Found! %s\n", people[i].number);
            return 0;
        }
    }

    printf("Not found!\n");
    return 1;

    return 0;
}