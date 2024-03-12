// Lecture 04 - "Memory"
// Program 03 - "Copy.c"

/*
?. What is malloc?
malloc is a function in '<stdlib.h>' library for C.
It takes in an argument 'size_t'.

?. What is Does?
malloc asks the operating system (windows in my case) to find you a 'size_t'
bytes of empty memory.

So for example,
>> malloc(4)
    Will ask the OS to find a 4 bytes empty space.

?. What does malloc return?
malloc(4) for example, Finds a chunk of empty space in memory and returns
the address of the first byte of that chunk.

Example:
>> malloc(4) will find a 4 bytes empty space in the memory
[ ][ ][ ][ ]

All of them have addresses
[ ]    [ ]    [ ]    [ ]
0x123  0x124  0x125  0x126

malloc returns the address of the first byte.

First byte == [ ]  (address => 0x123)

'malloc()' can also return a 'NULL' which is basically the address 0x00000000
turns out, when we malloc() a greater size of memory, and there is no more
memory to allocate, malloc returns the NULL value to indicate that there is no
more memory in the system to give! (AKA. computer has run out of memory!)


?. What is Free?
'free()' is another function is '<stdlib.h>' Library that is the
opposite of 'malloc()'

'malloc', allocates the chunk of memory whereas 'free', frees the memory and
tells the OS to use it for it's own purposes however it likes!
SO free, inshort, gives the memory back to OS which was taken by us using
malloc function.

WE SHOULD ALWAYS FREE THE MEMORY AFTER IT'S BEED USED BACK TO OS!
WE SHOULD USE FREE ONLY ON MEMORY THAT WE 'MALLOC'KED OURSELVES!

 */

#include "cs50.c"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *s = "hi!";
    char *t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        // If malloc returns NULL, (means there is no more memory to give)
        return 1;
    }

    // Manually copy the data from S into T
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // Auto-copy the data from S into T
    // strcpy(t, s);

    printf("%s\n", s);
    printf("%s\n", t);

    // Free the memory, which we took for our purposes (using malloc())
    free(t);
    return 0;
}