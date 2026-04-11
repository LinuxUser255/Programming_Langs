// 10_templates.cpp
//
// Templates — generic programming in C++.
// Write code once, use it with any type.
// The compiler generates a concrete version for each type you use.
//
// Compile: g++ -std=c++17 -Wall -o 10_templates 10_templates.cpp

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// ── Function Templates ────────────────────────────────────────────────────────

// A single function that works with any comparable type
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Template with multiple type parameters
template <typename T, typename U>
void print_pair(const T &first, const U &second) {
    std::cout << "  (" << first << ", " << second << ")" << std::endl;
}

// Template function that works on any container supporting .size() and []
template <typename T>
void print_array(const T *arr, int size, const std::string &label) {
    std::cout << "  " << label << ": [";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Template with a non-type parameter (compile-time constant)
template <typename T, int SIZE>
class FixedArray {
private:
    T data[SIZE];

public:
    FixedArray() {
        for (int i = 0; i < SIZE; ++i) {
            data[i] = T{};   // value-initialize each element
        }
    }

    T &operator[](int index) {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range("FixedArray index out of range");
        }
        return data[index];
    }

    const T &operator[](int index) const {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range("FixedArray index out of range");
        }
        return data[index];
    }

    int size() const { return SIZE; }

    void print() const {
        std::cout << "  FixedArray<" << SIZE << ">: [";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << data[i];
            if (i < SIZE - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// ── Class Template ────────────────────────────────────────────────────────────
// A generic stack that works with any type

template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T &value) {
        elements.push_back(value);
    }

    T pop() {
        if (empty()) {
            throw std::runtime_error("Stack::pop() called on empty stack");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }

    const T &peek() const {
        if (empty()) {
            throw std::runtime_error("Stack::peek() called on empty stack");
        }
        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }

    int size() const {
        return static_cast<int>(elements.size());
    }
};

// ── Template Specialization ───────────────────────────────────────────────────
// Override the generic template for a specific type

// Generic swap
template <typename T>
void my_swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Specialization for std::string — could use a more efficient approach
template <>
void my_swap<std::string>(std::string &a, std::string &b) {
    std::cout << "  (using string specialization of my_swap)" << std::endl;
    a.swap(b);   // std::string::swap is more efficient than copy
}

// ── auto and type deduction (C++11+) ─────────────────────────────────────────
// The compiler deduces template types — you rarely need to specify them

int main() {
    // ── 1. Function template with different types ─────────────────────────────
    std::cout << "=== 1. Function Template ===" << std::endl;

    std::cout << "  maximum(3, 7)         = " << maximum(3, 7)           << std::endl;
    std::cout << "  maximum(3.14, 2.71)   = " << maximum(3.14, 2.71)     << std::endl;
    std::cout << "  maximum('a', 'z')     = " << maximum('a', 'z')       << std::endl;
    std::cout << "  maximum(\"apple\",\"mango\") = "
              << maximum(std::string("apple"), std::string("mango"))      << std::endl;

    // ── 2. Explicit template type ─────────────────────────────────────────────
    std::cout << "\n=== 2. Explicit Template Type ===" << std::endl;
    // Compiler deduces int, but you can be explicit:
    std::cout << "  maximum<int>(10, 20)  = " << maximum<int>(10, 20)    << std::endl;
    std::cout << "  maximum<double>(1, 2) = " << maximum<double>(1, 2)   << std::endl;

    // ── 3. Multiple type parameters ───────────────────────────────────────────
    std::cout << "\n=== 3. Multiple Type Parameters ===" << std::endl;
    print_pair("score", 95);
    print_pair(3.14, "pi");
    print_pair(true, 42);

    // ── 4. Template with arrays ───────────────────────────────────────────────
    std::cout << "\n=== 4. Template with Arrays ===" << std::endl;

    int    ints[]    = {1, 2, 3, 4, 5};
    double doubles[] = {1.1, 2.2, 3.3};
    char   chars[]   = {'R', 'u', 's', 't'};

    print_array(ints,    5, "ints");
    print_array(doubles, 3, "doubles");
    print_array(chars,   4, "chars");

    // ── 5. Non-type template parameter ───────────────────────────────────────
    std::cout << "\n=== 5. Non-Type Template Parameter ===" << std::endl;

    FixedArray<int, 5> fixed_ints;
    for (int i = 0; i < fixed_ints.size(); ++i) {
        fixed_ints[i] = (i + 1) * 10;
    }
    fixed_ints.print();

    FixedArray<std::string, 3> fixed_strings;
    fixed_strings[0] = "alpha";
    fixed_strings[1] = "beta";
    fixed_strings[2] = "gamma";
    fixed_strings.print();

    // ── 6. Class template — Stack ─────────────────────────────────────────────
    std::cout << "\n=== 6. Class Template — Stack<T> ===" << std::endl;

    Stack<int> int_stack;
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    std::cout << "  int_stack size: " << int_stack.size() << std::endl;
    std::cout << "  peek: " << int_stack.peek() << std::endl;
    std::cout << "  pop:  " << int_stack.pop()  << std::endl;
    std::cout << "  pop:  " << int_stack.pop()  << std::endl;
    std::cout << "  pop:  " << int_stack.pop()  << std::endl;
    std::cout << "  empty? " << (int_stack.empty() ? "yes" : "no") << std::endl;

    Stack<std::string> str_stack;
    str_stack.push("first");
    str_stack.push("second");
    str_stack.push("third");
    std::cout << "  str_stack top: " << str_stack.peek() << std::endl;
    while (!str_stack.empty()) {
        std::cout << "  popped: " << str_stack.pop() << std::endl;
    }

    // ── 7. Template specialization ────────────────────────────────────────────
    std::cout << "\n=== 7. Template Specialization ===" << std::endl;

    int x = 5, y = 10;
    std::cout << "  Before swap: x=" << x << " y=" << y << std::endl;
    my_swap(x, y);
    std::cout << "  After swap:  x=" << x << " y=" << y << std::endl;

    std::string s1 = "hello", s2 = "world";
    std::cout << "  Before swap: s1=" << s1 << " s2=" << s2 << std::endl;
    my_swap(s1, s2);   // calls the string specialization
    std::cout << "  After swap:  s1=" << s1 << " s2=" << s2 << std::endl;

    // ── 8. auto — compiler deduces type ──────────────────────────────────────
    std::cout << "\n=== 8. auto Type Deduction ===" << std::endl;

    auto i   = 42;          // int
    auto d   = 3.14;        // double
    auto s   = std::string("hello");   // std::string
    auto max = maximum(100, 200);      // int — deduced from arguments

    std::cout << "  auto i   = " << i   << "  (int)"    << std::endl;
    std::cout << "  auto d   = " << d   << "  (double)" << std::endl;
    std::cout << "  auto s   = " << s   << "  (string)" << std::endl;
    std::cout << "  auto max = " << max << "  (int)"    << std::endl;

    return 0;
}
