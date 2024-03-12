// Lecture 04 - "Memory"
// Program 02 - "Compare.c"

#include "cs50.c"
#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    char *t = "HI!";

    printf("%p\n", &s);
    printf("%p\n", &t);

    return 0;
}