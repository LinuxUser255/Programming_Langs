#include <iostream>
#include <string>

int main() {
    // Variables
    std::string name = "Alice";
    int age = 30;
    double height = 5.9;
    bool is_active = true;

    // Constants
    const int MAX_USERS = 100;
    constexpr double PI = 3.14159;

    std::cout << "Name: " << name << ", Age: " << age << std::endl;
    std::cout << "Max users: " << MAX_USERS << ", PI: " << PI << std::endl;
    return 0;
}
