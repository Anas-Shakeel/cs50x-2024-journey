// Lecture 05 - "Data Structures"
// Program 02

/*
What does this program do?
- Implements a linked list
- Inserts command-line arguments (int)s into the list
- Prints the items (int)s in the list

It uses prepend mode to insert in this list, instead of append mode.
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
    for (int i = 1; i < argc; i++)
    {
        // Convert the string to int and store
        int number = atoi(argv[i]);
        // Allocate a chunk of memory of size 'node'
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Free memory thus far
            return 1;
        }

        n->number = number; // Store the number into node's number
        n->next = list;     // Store the address of
        list = n;           // Store the address stored in 'n' in 'list' (aka. point to the thing that n is pointing to)
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
