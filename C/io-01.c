// file_io-01.c
// Introduction to File Input/Output in C - Reading and writing files safely

#include <stdio.h>
#include <stdlib.h>   // for exit()

int main(void) {
    FILE *fp;
    int c;
    int line_count = 0;
    int char_count = 0;

    // 1. Opening a file for reading
    fp = fopen("test_input.txt", "r");        // "r" = read text mode
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;                             // Exit with error
    }

    printf("Reading from test_input.txt...\n");

    // Read character by character (similar to your copy.c and linecount.c)
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);                           // Echo to screen
        char_count++;

        if (c == '\n') {
            line_count++;
        }
    }

    fclose(fp);                               // Always close files!

    printf("\n--- Summary ---\n");
    printf("Characters read: %d\n", char_count);
    printf("Lines read: %d\n", line_count);

    // 2. Writing to a file
    fp = fopen("output.txt", "w");            // "w" = write text mode (creates or overwrites)
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    fprintf(fp, "C Programming File I/O Example\n");
    fprintf(fp, "Characters: %d\n", char_count);
    fprintf(fp, "Lines: %d\n", line_count);
    fprintf(fp, "Written by BSides Triad student!\n");

    fclose(fp);

    printf("Output written to output.txt\n");

    // 3. Bonus: Reading lines with fgets (safer for strings)
    fp = fopen("test_input.txt", "r");
    if (fp == NULL) {
        perror("Error reopening file");
        return 1;
    }

    char line[256];                           // Buffer for one line
    printf("\nReading lines with fgets:\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("Line: %s", line);             // fgets includes the newline
    }

    fclose(fp);

    return 0;
}
