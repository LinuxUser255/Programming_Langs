#include <stdio.h>

// Basic example of a function
// Double the number passed in as 'x', returning the new value to the function caller.
int double_number_a(int x) {
    return 2 * x;
}

// Double the number pointed to by 'x', storing the result in the original variable.
void double_number_b(int* x) {
    *x *= 2;
}

int main() {
    int num = 5;
    printf("%d\n", double_number_a(num));
    printf("%d\n", num);
    double_number_b(&num);
    printf("%d\n", num);
    return 0;
}
