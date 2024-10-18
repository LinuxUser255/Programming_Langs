#include <stdio.h>

// Basic example of a pointer to an integer
int main() {
    int num = 5;
    int* ptr = &num;

    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", &num);
    printf("Value of ptr: %p\n", ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);

    return 0;
}
