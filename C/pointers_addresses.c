/*
 * pointers_addresses.c
 *
 * Demonstrates the relationship between variables, addresses,
 * and pointers. Shows how to declare a pointer, get an address
 * with &, and dereference with *.
 */

#include <stdio.h>

int main(void) {
    int x = 42;
    int *p = &x;                     // p now holds the address of x

    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", (void*)&x);
    printf("Value stored in pointer p: %p\n", (void*)p);
    printf("Value pointed to by p: %d\n", *p);

    /* Modify x through the pointer */
    *p = 100;

    printf("\nAfter *p = 100, value of x is now: %d\n", x);

    return 0;
}
