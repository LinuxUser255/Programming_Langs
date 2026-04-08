#include <iostream>

int main() {
    int age = 20;

    if (age < 18) {
        std::cout << "Minor" << std::endl;
    } else if (age >= 18 && age < 65) {
        std::cout << "Adult" << std::endl;
    } else {
        std::cout << "Senior" << std::endl;
    }

    // Switch (C++ has no built-in match yet – switch is the classic)
    std::string status = "active";
    switch (status[0]) {  // simple demo
        case 'a': std::cout << "User is active" << std::endl; break;
        default:  std::cout << "Unknown" << std::endl;
    }
    return 0;
}
