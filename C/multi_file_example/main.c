// main.c - The main program that uses our utility functions
#include "utils.h"

int main(void) {
    printf("=== Multi-File C Program Example ===\n\n");

    // Using functions from utils.c
    print_greeting("BSides Triad");

    int result = add_numbers(15, 27);
    printf("15 + 27 = %d\n\n", result);

    // Demonstrate file operation (create a test file first if you want)
    // copy_file("test_input.txt", "copied_output.txt");

    printf("This program is built from multiple source files!\n");
    printf("Header: utils.h\n");
    printf("Implementation: utils.c\n");
    printf("Entry point: main.c\n");

    return 0;
}
