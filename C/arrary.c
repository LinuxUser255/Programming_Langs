#include <stdio.h>
// An arraray is a collection of items stored in contiguous memory locations.
// Elements in can be accessed by their index.

int main(void) {
    int my_array[5]; // Declare an array of 5 integers
    int my_array_b[] = {1, 2, 3, 4, 5}; // Declare and initialize an array of 5 integers

    size_t length = sizeof(my_array) / sizeof(my_array[0]); // Get the length of the array
    for(size_t i = 0; i < length; i++) {
        my_array[i] = i; // Assign values to the array
    }
    printf("%d\n", my_array[2]); // Print the value at index 2
    return 0;
}
