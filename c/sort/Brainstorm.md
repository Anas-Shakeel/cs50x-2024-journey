What Do I Know About These Sorting Algorithms?

>> Selection Sort:
How it works:
Selection sort works by taking an array of numbers and looking through that 
entire array of numbers to try and find the smallest item in that entire array.
And then bringing that smallest number to the beginning of the array.
Then we search through the remainder of the array, looking for the next 
smallest item, and when we find it, we bring that next smallest number to
the beginning of the remainging array, And we repeat the process until finished.

Time/Space Complexity
Big Oh: O(n^2)
Omega:  _O_(n^2)

Things to consider:
- Selection sort will take the most time when sorting an already sorted array among all three of these algorithms as it has a time complexity of omega(n^2).

- Selection sort will take longer to sort a random array than merge sort.

# ############################################################################ #

>> Bubble Sort:
How it works:
Bubble sort compares two values at a time. it looks at every pair of value, and
tries to determine whether that pair is in correct order (that is to say, if you're sorting from smallest to largest number, in every pair, the smaller number is to the left of the larger number).
It finds two numbers that are out of order and swaps them. and it will contineuly go through this process.


Time/Space Complexity
Big Oh: O(n^2)
Omega:  _O_(n)


Things to consider:
- Bubble sort can sort the "Sorted items" quickly than the rest of these algorithms because it has Omega(n). Others have bigger time complexity when the array is already sorted.

- Bubble sort will take exactly the same time as selection sort when sorting a random array. these two will take longer to sort a random array than merge sort.


# ############################################################################ #

>> Merge Sort:
How it works:
Merge sort works by taking an array and dividing it into a left half and a right half and sorting each of those halves first, and after it recusively sorts each of those halves, it merges those halves together.


Time/Space Complexity
Big Oh: O(n log n)
Omega:  _O_(n log n)


Things to consider:
- Merge sort will take more time to sort a sorted array than bubble sort but will take less time than selection sort.

- Merge sort will take the least time when sorting a random array because of O(n log n) time complexity.


# ############################################################################ #
<!-- sort1   |sorted5000 |  0.030s     | -->
<!-- sort1   |sorted10000|  0.056s     | -->

program |   file      |   time (sys)|
sort1   |sorted50000  |  0.260s     |
sort1   |reversed50000|  0.294s     |
sort1   |random50000  |  0.290s     |

sort2   |sorted50000  |  0.250s     |
sort2   |reversed50000|  0.250s     |
sort2   |random50000  |  0.259s     |

sort3   |sorted50000  |  0.265s     |
sort3   |reversed50000|  0.280s     |
sort3   |random50000  |  0.250s     |




For Sorted 
sort1 >> 1.2 2.0 2.3 1.5 1.5 1.8 | 3.8 3.4 1.8 2.1 1.9
sort2 >> 1.3 1.9 3.2 1.7 1.8 2.0 | 1.3 2.2 1.1 1.8 2.3
sort3 >> 4.3 3.7 3.4 3.5 3.7 3.5 | 3.3 3.7 4.2 3.6 3.8

For Random
sort1 >> 6.8 6.5 7.1 6.9 7.4
sort2 >> 1.8 1.5 1.9 2.5 1.5
sort3 >> 5.0 5.4 4.3 4.6 4.5




Conclusions:
Sort1 is using "Bubble sort"
Why?
    because Bubble sort has lesser omega time complexity than selection sort or merge sort, hence it performs well comparing other two algorithms when sorting already sorted numbers.

Sort2 is using "Merge sort"
Why?
    because Merge sort has lesser big oh time complexity than bubble sort or selection sort hence, performs significantly faster when sorting random numbers.

Sort3 is using "Selection sort"
Why?
    because selection sort has time complexities O(n^2) & Omega(n^2), So for numbers that are sorted, its slower than bubble sort, and for numbers that are random, its slower than merge sort, that leaves with only one conclusion, its selection sort.
    it is slower than bubble sort when sorting already sorted numbers and it's slower than merge sort when sorting random numbers.