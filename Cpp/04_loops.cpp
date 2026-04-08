#include <iostream>
#include <vector>

int main() {
    // For loop
    for (int i = 0; i < 5; ++i) {
        std::cout << "For: " << i << " ";
    }
    std::cout << std::endl;

    // Range-based for (modern C++)
    std::vector<int> numbers = {10, 20, 30};
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // While
    int count = 0;
    while (count < 3) {
        std::cout << "While: " << count++ << std::endl;
    }
    return 0;
}
