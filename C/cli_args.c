// command_line_args.c
// Using command-line arguments - making programs flexible and useful

#include <stdio.h>
#include <stdlib.h>   // for exit()

// Simple file copy program that takes input and output filenames from command line
int main(int argc, char *argv[]) {
    FILE *in_fp, *out_fp;
    int c;

    // argc = argument count, argv = argument vector (array of strings)
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    // Check correct usage
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    in_fp = fopen(argv[1], "r");
    if (in_fp == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open output file for writing
    out_fp = fopen(argv[2], "w");
    if (out_fp == NULL) {
        perror("Error opening output file");
        fclose(in_fp);          // clean up already opened file
        return 1;
    }

    // Copy character by character (building on your copy.c and file_io-01.c)
    while ((c = fgetc(in_fp)) != EOF) {
        fputc(c, out_fp);
    }

    fclose(in_fp);
    fclose(out_fp);

    printf("File copied successfully: %s -> %s\n", argv[1], argv[2]);

    return 0;
}
