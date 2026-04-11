/*
 * char_pointers.c
 *
 * Shows how character pointers are used to work with C strings.
 * Demonstrates walking a string using pointer arithmetic and the
 * null terminator.
 */

#include <stdio.h>

void print_string(const char *str) {
    while (*str != '\0') {
        putchar(*str);
        ++str;
    }
    putchar('\n');
}

int main(void) {
    char *message = "Hello from a character pointer!";

    printf("Using printf: %s\n", message);
    printf("Using our own function: ");
    print_string(message);

    return 0;
}
