// Lecture 04 - "Memory"
// program 01 - "addresses"

// Working with pointers!!!
/*
Q. What is a pointer?
A. A pointer is a variable that is used to store the address of
some other variable.

Syntax:

'*' is called 'Dereference Operator'
'&' is called 'Reference Operator'

'*' == means Get the value stored in the pointer
'&' == means Get the address of p

Getting the address of a variable?
&some_variable

Declaring a poinnter
int *p = &some_variable;

Getting the value stored in the variable whose address is stored in pointer?
'*p'
Example":
    int value = *p;

Printing the value stored in the pointer?
format specifier:
    %p

printf("%p", *p);

Printing the address stored in pointer?
printf("%p", p);


Q. What is Pointer Arithmetic?
A. Pointer Arithmetic is just arithmetic done on pointers!
*/

#include <stdio.h>

int main(void)
{
    char *s = "HI!";

    printf("%c", *(s + 0));
    printf("%c", *(s + 1));
    printf("%c\n", *(s + 2));
    return 0;
}