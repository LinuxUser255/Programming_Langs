// utils.c - Implementation of utility functions
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Print a friendly greeting
void print_greeting(const char *name) {
    if (name == NULL) {
        printf("Hello, stranger!\n");
        return;
    }
    printf("Hello, %s! Welcome to multi-file C programming.\n", name);
}

// Simple addition (demonstrates returning a value)
int add_numbers(int a, int b) {
    return a + b;
}

// File copy using command-line style arguments (reuses skills from previous lessons)
void copy_file(const char *src, const char *dest) {
    FILE *in = fopen(src, "r");
    if (in == NULL) {
        perror("Error opening source file");
        return;
    }

    FILE *out = fopen(dest, "w");
    if (out == NULL) {
        perror("Error opening destination file");
        fclose(in);
        return;
    }

    int c;
    while ((c = fgetc(in)) != EOF) {
        fputc(c, out);
    }

    fclose(in);
    fclose(out);
    printf("Successfully copied %s -> %s\n", src, dest);
}
