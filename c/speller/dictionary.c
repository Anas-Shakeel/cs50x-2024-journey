// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Global : words counter
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    /*
    Hash the word to obtain its index
    Access linked list at that index in the hash table
    Traverse the linked list, looking for the word (strcasecmp for comparing case-insensitively)

    How to traverse a linked list?
        Start with a cursor, set to the first item in linked list
        Keep moving cursor until you get to NULL, checking each node for the word
    */

    // Setup a cursor
    node *cursor = table[hash(word)];

    // Traverse the linked list
    while (cursor != NULL)
    {
        // Check the word
        if (strcasecmp(cursor->word, word))
        {
            // Word matched!
            return true;
        }

        // Set the cursor to next node
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Sum (to store the sum of ascii values)
    int sum = strlen(word); // Store the length of the word

    // Sum the ascii values
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += toupper(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open a dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Character array to store each word (temporarily)
    char word[LENGTH + 1];
    // Read strings from file one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, word);

        // Hash word to obtain a hash value
        unsigned int hash_value = hash(new_node->word);

        // Insert node into hash table at that location
        new_node->next = table[hash_value];
        table[hash_value] = new_node;
        // Increase the word_count
        word_count++;
    }

    // Close the dictionary
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    /*
    How to free the nodes?
        Iterate through the hash table:
            node *tmp = NULL;
            node *cursor = NULL;
            set the cursor to current linked-list's head
            Iterate through the linked-list:
                IF (cursor == NULL)
                    / Nothing to free
                    skip to next iteration

                / set the tmp equal to cursor
                tmp = cursor
                / set the cursor to the next node
                cursor = cursor->next;
                free(tmp)
    */
    // Iterate through the hash table
    for (int i = 0; i < N; i++)
    {
        // Setup cursors and pointers
        node *cursor = table[i];
        node *temp = NULL;

        // Traverse the linked list
        while (cursor != NULL)
        {
            // Set the temp to cursor
            temp = cursor;
            // Set the cursor to the next node
            cursor = cursor->next;

            // Free the temp node
            free(temp);
        }
    }

    return true;
}

/*
Hash function
What to do?
    - Input:
        Take as argument a word (char *word) [with alphabetical chars
         and possible, apostrophes]
    - Output:
        Numerical index between 0 - 1 and N-1, inclusive
            N: Total buckets in the hash table
    - Deterministic

    Decisions:
        Larger N means more buckets
        Possible values that hash function can return
            Make sure return values are somewhere between 0 - N-1, inclusive
            If value greater than N
                value % N (should give a value in range)

    Example Hash Functions:
        - First letter:
            simple hash functions might take the first letter of the word
                if 1st-letter is 'A', hash value will be 0
                if 'B', hash value will be 1
                if 'Z', hash value will be 25

        - First two letters
        - Mathematical:
            Using sum of ASCII values of chars in that word
            Length or the word

    A good hashing function reduces "collisions" and has a (mostly!)
    even distribution across hash table "Buckets"


 */

/*
Load function
What to do?
    - Take as argument a dictionary file (char *dictionary)
    - Load the dictionary into memory,
        Return true if successful
        False if:
            not enough memory
            etc...
            FILE

How?
    Well to store the the dictionary, we are gonna use a `hash table`

    Hash Table:
        Hash table    - array of linked lists
        Hash function - assigns a number to every input

    How hash tables work?
        consider these five words (apple, banana, bat, car, book) that we would
        store inside a hash table
        - If we were to put all of them in a single linked list, it would be a pretty
        long list of five individual items, traversing each would be time consuming.

        - Instead we can put them a hash table, Creating several buckets,
            for example an 'A' bucket, 'B' bucket, 'C' bucket and so on.
            - Bucket 'A' for all words beginning with letter a
            - Bucket 'B' for all words beginning with letter b
                and so on

            And associate each word with a particular bucket.
                for example:
                    - Bucket 'A' will store word (apple)
                    - Bucket 'B' will store words (banana, bat, book)
                    - Bucket 'C' will store words (car)

            This will be done using a hash function.
                a function that takes these (one at a time) words as input and
                output which of the linked list we should put them in...

What to do?
    - Open a dictionary file
    - Read strings from file one at a time
    - Create a new node for each word
    - Hash word to obtain a hash value
    - Insert node into hash table at that location

- Open a dictionary file
    Use `fopen` to open the file
    Remember to check if return value is NULL

- Read strings from file one at a time
    `fscanf(file, "%s", word)`
            file: file to read the string from
            "%S": to read a string
            word: some place to read the word into
    `fscanf` Will return EOF once it reaches the end of the file

- Create a new node for each word
    Use `malloc` to allocate enough memory to store a node
    Remember to check if malloc returned NULL
    Copy the word into that node using `strcpy` function

- Hash word to obtain a hash value
    Use `hash` function
        Takes a string (a word)
        returns an index for the word's appropriate list

- Insert node into hash table at that location
    Recall that the hash table is an array of linked lists
        Index into the hash table to get the list we want to use to
            add this word into..
        Add a new node to the linked list
    Be sure to set pointers in the correct order.
        for example:
        we want to pre-pend the new_node into head node
            head -> bat -> book -> banana
            new_node -> blue

        if we point head to new node, we lose the address of head list
        if we point new_node to head node, we lose the new_node

        So we first point the `blue` node's `next` to the head's first node `bat`
        Then, we point the head node to this `blue` node

        head     bat
          \     /
            blue


 */