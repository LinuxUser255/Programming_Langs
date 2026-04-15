// strings-01.c
// Working with C strings - the most common source of bugs and the most useful tool

#include <stdio.h>
#include <string.h>     // strlen, strcpy, strcat, strcmp, etc.
#include <stdlib.h>     // for malloc and free (we'll use it safely)

int main(void) {
    // 1. String literals are stored in read-only memory
    const char *greeting = "Hello, BSides Triad!";   // pointer to literal
    printf("Greeting: %s\n", greeting);
    printf("Length of greeting: %zu\n", strlen(greeting));  // size_t is correct type

    // 2. Character arrays (mutable strings)
    char buffer[100];                    // plenty of space
    strcpy(buffer, "C Programming is powerful");
    printf("Buffer after strcpy: %s\n", buffer);

    // 3. Concatenation
    strcat(buffer, " and fun!");
    printf("After strcat: %s\n", buffer);

    // 4. Comparing strings
    char str1[] = "apple";
    char str2[] = "banana";

    if (strcmp(str1, str2) < 0) {
        printf("'%s' comes before '%s' alphabetically\n", str1, str2);
    }

    // 5. Safe string copying with strncpy (and why we still need to be careful)
    char safe[20];
    strncpy(safe, "This is a long string", sizeof(safe) - 1);
    safe[sizeof(safe) - 1] = '\0';      // ALWAYS null-terminate!
    printf("Safely copied: %s\n", safe);

    // 6. Finding substrings
    char *found = strstr(buffer, "powerful");
    if (found) {
        printf("Found 'powerful' at position %td\n", found - buffer);
    }

    // 7. Dynamic string allocation example (bonus - ties into your malloc lesson)
    char *dynamic = malloc(strlen("Dynamic strings in C!") + 1);
    if (dynamic) {
        strcpy(dynamic, "Dynamic strings in C!");
        printf("Dynamic string: %s\n", dynamic);
        free(dynamic);                  // Always free what you malloc
    }

    return 0;
}
