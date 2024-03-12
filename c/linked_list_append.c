// Lecture 05 - "Data Structures"
// Program 03

/*
What does this program do?
- Implements a linked list
- Inserts command-line arguments (int)s into the list
- Prints the items (int)s in the list

It uses append mode to insert in this list, instead of append mode.
Prepend: Items or (integers in this case), get inserted at the beginning of the list
Append : Items get inserted at the end of the list

*/

#include <stdio.h>
#include <stdlib.h>

// Creating a structure called "Node" (aka. Linked List)
typedef struct node
{
    int number;        // Will store an integer
    struct node *next; // Will store the address of the next integer (POINTER)
} node;

int main(int argc, char *argv[])
{
    // Initializing the node
    node *list = NULL;

    // Iterate over the arguments
    for (int i = 1; i < argc; i++)
    {
        // Convert the string to int
        int number = atoi(argv[i]);

        // Allocate the memory for this number's node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        // Populate the node
        n->number = number; // Store number in number
        n->next = NULL;     // Store null in next pointer

        if (list == NULL)
        {
            list = n;
        }
        else
        {
            // Append the node in the list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // If at the end of the list
                if (ptr->next == NULL)
                {
                    // Append the node
                    ptr->next = n;
                    break;

                }
            }
        }
    }

    // Print the linked list
    node *ptr = list; // Point to the address that 'list' is pointing to
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number); // print the value of 'number' that 'ptr' is pointing to
        ptr = ptr->next;             // Update 'ptr' to hold the next node's address
    }

    return 0;
}
