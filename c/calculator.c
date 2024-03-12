// Calculator.c
// A simple basic calculator program that takes two integers and
// an operation_code and performs operations based on that code

#include <stdio.h>

int get_int(char *message);
int get_opcode(char *prompt);

int main(void)
{
    int x = get_int("Enter x: ");
    int y = get_int("Enter y: ");
    int op_code = get_opcode("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\nEnter Operation (number): ");

    // Calculate the values
    float float_result;
    switch (op_code)
    {
    case 1:
        // Add values
        float_result = (float)x + (float)y;
        break;
    case 2:
        // Subtract values
        float_result = (float)x - (float)y;
        break;
    case 3:
        // Multiply values
        float_result = (float)x * (float)y;
        break;
    case 4:
        // Divide values
        float_result = (float)x / (float)y;
        break;

    default:
        // default case
        break;
    }

    // Print result
    printf("%.3f\n", float_result);

    return 0;
}

// Get integer from user
int get_int(char *prompt)
{
    int integer;
    printf(prompt);
    scanf("%i", &integer);
    return integer;
}

// Get opcode from user
int get_opcode(char *prompt)
{
    int opcode;
    while (1)
    {
        printf(prompt);
        scanf("%i", &opcode);
        if (opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4)
        {
            return opcode;
        }
    }
}