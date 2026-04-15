// pointers_advanced.c
// Advanced Pointers - function pointers, void*, const correctness

#include <stdio.h>

// 1. Function pointer type
typedef int (*MathOperation)(int, int);

// Function examples
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

// 2. Function that takes a function pointer
void perform_operation(MathOperation op, int x, int y) {
    int result = op(x, y);
    printf("Result: %d\n", result);
}

// 3. Void pointer example (generic pointer)
void print_anything(void *data, char type) {
    if (type == 'i') {
        printf("Integer: %d\n", *(int*)data);
    } else if (type == 'f') {
        printf("Float: %.2f\n", *(float*)data);
    }
}

int main(void) {
    printf("=== Advanced Pointers ===\n\n");

    // Function pointer usage
    MathOperation op = add;
    perform_operation(op, 10, 20);

    op = multiply;
    perform_operation(op, 6, 7);

    // Array of function pointers (very powerful pattern)
    MathOperation operations[] = {add, subtract, multiply};
    const char *names[] = {"Add", "Subtract", "Multiply"};

    printf("\nUsing array of function pointers:\n");
    for (int i = 0; i < 3; i++) {
        printf("%s(10, 5) = ", names[i]);
        perform_operation(operations[i], 10, 5);
    }

    // Void pointer
    int num = 42;
    float pi = 3.14f;
    print_anything(&num, 'i');
    print_anything(&pi, 'f');

    // Const correctness
    const int *ptr = &num;     // pointer to const int
    // *ptr = 100;             // ERROR - cannot modify
    printf("Const pointer value: %d\n", *ptr);

    return 0;
}
