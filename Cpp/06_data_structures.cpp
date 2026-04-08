#include <iostream>
#include <vector>
#include <map>
#include <set>

int main() {
    // Vector (dynamic array)
    std::vector<int> nums = {1, 2, 3, 4, 5};
    nums.push_back(6);

    // Map (dictionary)
    std::map<std::string, int> person = {{"age", 28}, {"city", 0}}; // demo

    // Set
    std::set<int> unique = {1, 2, 2, 3};

    std::cout << "Vector size: " << nums.size() << std::endl;
    std::cout << "Unique set size: " << unique.size() << std::endl;
    return 0;
}
