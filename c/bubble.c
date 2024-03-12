// Implementing a Bubble sorting algorithm

/*
What is Bubble sort?
Bubble sort is a sorting algorithm that is used to sort an array (a collection
 of consecutive items).

How it Works?
Bubble sort works by comparing two values at a time and swaps the smaller value
with the greater value. it repeats this process until the array is sorted!

Pseudo Code: (algorithm)
Bubble_sort(array):
    for i=0 in array - 1:
        for j=i+1 in array:
            if array[j] < array[i]:
                swap array[j] and array[i]

        end of inner-loop
    end of outer-loop

    return sorted_array

 */

#include <stdio.h>

void print_array(int array[], int len);

int main(void)
{
    // Array to sort
    int array[] = {1, 5, 4, 8, 7, 0, 9, 2, 3, 6};
    // getting the length of the array dynamically!
    int len = sizeof(array) / sizeof(array[0]);

    // Print Before
    printf("Before: ");
    print_array(array, len);
    printf("\n");

    int temp; // used to swap variables
    // Sort & print the array
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (array[j] < array[i])
            {
                // Swap
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    // Print After
    printf("After:  ");
    print_array(array, len);
    printf("\n");
    return 0;
}

/*
### Print Array
Prints the array in one line with space-separated values.
*/
void print_array(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", array[i]);
    }
}

/*
Implementing the Bubble Sort:

Iterate through the array[n-1]:
    If array[i] > array[i+1]:
        / first is greater than second
        / do nothing
    else:
        / second is greater than first
        / swap array[i] with array[i+1]

 */