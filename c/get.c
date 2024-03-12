// Lecture 04 - "Memory"
// Program 07 - "Get.c"

#include <stdio.h>

int get_int(char *prompt);

int main(void)
{
    // Getting an integer & printing
    /*
    int n;
    printf("n: ");
    scanf("%i", &n);
    printf("n: %i\n", n);

    */

    // Getting a string & printing
    /*
    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
     */

    return 0;
}

int get_int(char *prompt)
{
    int temp;
    printf(prompt);
    scanf("%i", &temp);
    return temp;
}
