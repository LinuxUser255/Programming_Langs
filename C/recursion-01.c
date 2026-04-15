// recursion-01.c
// Introduction to Recursion in C - Base cases, recursive calls, and the call stack

#include <stdio.h>

// 1. Classic recursive factorial
// n! = n * (n-1) * ... * 1
unsigned long factorial(unsigned int n) {
    if (n == 0 || n == 1) {        // Base case - stops the recursion
        return 1;
    }
    return n * factorial(n - 1);   // Recursive case - smaller problem
}

// 2. Recursive sum of first n natural numbers
int sum(int n) {
    if (n <= 0) {
        return 0;                  // Base case
    }
    return n + sum(n - 1);         // Recursive case
}

// 3. Print numbers from n down to 1 (countdown example)
void countdown(int n) {
    if (n < 1) {                   // Base case
        printf("\nBlast off!\n");
        return;
    }
    printf("%d ", n);
    countdown(n - 1);              // Recursive call
}

int main(void) {
    printf("=== Recursion Examples ===\n\n");

    // Factorial
    unsigned int num = 10;
    printf("Factorial of %u = %lu\n", num, factorial(num));

    // Sum
    int n = 5;
    printf("Sum of first %d numbers = %d\n", n, sum(n));

    // Countdown
    printf("Countdown from 5: ");
    countdown(5);

    // Warning about large inputs
    printf("\nNote: factorial(20) works, but factorial(100) would cause stack overflow!\n");

    return 0;
}
