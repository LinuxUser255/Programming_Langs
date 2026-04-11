#include <stdio.h>
#include <string.h>

int main(void) {
    /* Create a fixed-size array on the stack — exactly 100 bytes. */
    char your_name[100];

    printf("Enter your name: ");

    /* Safely read user input into the array fixed buffer. */
    if (fgets(your_name, sizeof(your_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    /* Remove training whitespace from the end of the string. */
    your_name[strcspn(your_name, "\n")] = '\0';

    printf("Hello, %s!\n", your_name);

    return 0;
}
