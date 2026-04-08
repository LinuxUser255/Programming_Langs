#include <iostream>

int add(int a, int b) {
    return a + b;
}

void greet(std::string name, int age = 25) {
    std::cout << "Hello " << name << ", you are " << age << std::endl;
}

int main() {
    greet("Bob");
    greet("Alice", 32);
    std::cout << "Sum: " << add(5, 7) << std::endl;
    return 0;
}
