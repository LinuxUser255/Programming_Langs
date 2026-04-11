/*
 * pointers_arrays.c
 *
 * Demonstrates that the name of an array is a pointer to its first element.
 * Shows both array notation and pointer notation are equivalent.
 */

#include <stdio.h>

int main(void) {
    int numbers[5] = {10, 20, 30, 40, 50};
    int *ptr = numbers;              // array name decays to pointer

    printf("Using array notation:\n");
    for (int i = 0; i < 5; ++i) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    printf("\nUsing pointer notation:\n");
    for (int i = 0; i < 5; ++i) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }

    return 0;
}
