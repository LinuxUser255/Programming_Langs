/*
 * pointer_arithmetic.c
 *
 * Demonstrates pointer arithmetic: adding/subtracting integers
 * to a pointer automatically scales by the size of the pointed-to type.
 */

#include <stdio.h>

int main(void) {
    int arr[6] = {100, 200, 300, 400, 500, 600};
    int *p = arr;

    printf("p     points to %d\n", *p);
    printf("p+1   points to %d\n", *(p + 1));
    printf("p+2   points to %d\n", *(p + 2));

    p += 3;                          // move pointer forward 3 integers

    printf("\nAfter p += 3, p now points to %d\n", *p);

    return 0;
}
