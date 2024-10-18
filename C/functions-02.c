#include <stdio.h>

int addNumbers(int a, int b) {
    return a + b;
}

int main() {
    int num1 = 5;
    int num2 = 10;
    int sum = addNumbers(num1, num2);

    printf("Sum: %d\n", sum);

    return 0;
}
