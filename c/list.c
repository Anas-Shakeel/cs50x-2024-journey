// Lecture 05 - "Data Structures"
// Program 01

/*
What does this program do?
It defines a pointer `list` where we store a list of 3 integers. (well, the address actually).
We then, want to store another integer but there is no space in this list.
So we make another `tmp` list which mallocs the memory for 4 integers and then
 we copy all the integers from list to tmp.

Then we print the numbers

 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL) // malloc can return a NULL if finding memory was failed
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list); // free list before quitting to avoid memory leak
        return 1;
    }

    // Copy the values from list to tmp (only temporarily)
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3] = 4; // add the forth item in there, manually

    // Free the original list
    free(list);

    // Even though the list was freed, the address stays in the list pointer (jus the values get replaced by garbage values)
    list = tmp; // replace the address in list with address in tmp (aka, point to the new `tmp` chunk of memory)

    // Print the values
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // Free the list again because now program ends (good practice)
    free(list);
    return 0;
}