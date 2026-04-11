// 08_pointers_references.cpp
//
// Pointers and references — the most important C++ concept
// that has no direct equivalent in Python.
//
// A pointer stores the memory address of another variable.
// A reference is an alias — another name for the same variable.
//
// Compile: g++ -std=c++17 -Wall -o 08_pointers_references 08_pointers_references.cpp

#include <iostream>
#include <string>

// ── Pass by value vs pass by reference ───────────────────────────────────────

// Pass by value: function gets a copy — original unchanged
void double_by_value(int x) {
    x = x * 2;
    std::cout << "  inside double_by_value: x = " << x << std::endl;
}

// Pass by reference: function operates on the original variable
void double_by_reference(int &x) {
    x = x * 2;
    std::cout << "  inside double_by_reference: x = " << x << std::endl;
}

// Pass by pointer: caller passes address, function dereferences it
void double_by_pointer(int *x) {
    *x = *x * 2;
    std::cout << "  inside double_by_pointer: *x = " << *x << std::endl;
}

// ── Returning a reference ─────────────────────────────────────────────────────

// Return a reference to an element inside an array
// NOTE: only safe if the array outlives the function call
int &get_element(int arr[], int index) {
    return arr[index];
}

// ── Pointer arithmetic ────────────────────────────────────────────────────────

void demonstrate_pointer_arithmetic() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;   // ptr points to first element

    std::cout << "\nPointer arithmetic:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  ptr + " << i << " = " << *(ptr + i) << std::endl;
    }
}

// ── nullptr — safe null pointer ───────────────────────────────────────────────

void check_pointer(int *ptr) {
    if (ptr == nullptr) {
        std::cout << "  pointer is null — nothing to dereference" << std::endl;
    } else {
        std::cout << "  pointer holds value: " << *ptr << std::endl;
    }
}

int main() {
    // ── 1. Basic pointer ──────────────────────────────────────────────────────
    std::cout << "=== 1. Basic Pointer ===" << std::endl;

    int score = 42;
    int *ptr = &score;   // & means "address of"

    std::cout << "score         = " << score   << std::endl;
    std::cout << "address (&score) = " << &score  << std::endl;
    std::cout << "ptr           = " << ptr     << std::endl;  // same address
    std::cout << "deref (*ptr)  = " << *ptr    << std::endl;  // value at address

    // Modifying through a pointer
    *ptr = 100;
    std::cout << "After *ptr = 100, score = " << score << std::endl;

    // ── 2. References ─────────────────────────────────────────────────────────
    std::cout << "\n=== 2. References ===" << std::endl;

    int original = 10;
    int &ref = original;   // ref is another name for original

    std::cout << "original = " << original << std::endl;
    std::cout << "ref      = " << ref      << std::endl;

    ref = 99;   // modifying ref modifies original
    std::cout << "After ref = 99, original = " << original << std::endl;

    // ── 3. Pass by value vs reference vs pointer ──────────────────────────────
    std::cout << "\n=== 3. Pass By Value / Reference / Pointer ===" << std::endl;

    int a = 5;
    std::cout << "Before double_by_value: a = " << a << std::endl;
    double_by_value(a);
    std::cout << "After  double_by_value: a = " << a << "  (unchanged)" << std::endl;

    std::cout << std::endl;

    int b = 5;
    std::cout << "Before double_by_reference: b = " << b << std::endl;
    double_by_reference(b);
    std::cout << "After  double_by_reference: b = " << b << "  (changed)" << std::endl;

    std::cout << std::endl;

    int c = 5;
    std::cout << "Before double_by_pointer: c = " << c << std::endl;
    double_by_pointer(&c);   // pass address of c
    std::cout << "After  double_by_pointer: c = " << c << "  (changed)" << std::endl;

    // ── 4. Pointer to pointer ─────────────────────────────────────────────────
    std::cout << "\n=== 4. Pointer to Pointer ===" << std::endl;

    int val   = 7;
    int *p    = &val;    // p points to val
    int **pp  = &p;      // pp points to p

    std::cout << "val   = " << val    << std::endl;
    std::cout << "*p    = " << *p     << std::endl;
    std::cout << "**pp  = " << **pp   << std::endl;

    // ── 5. const pointer vs pointer to const ─────────────────────────────────
    std::cout << "\n=== 5. const Pointers ===" << std::endl;

    int x = 10;
    int y = 20;

    // Pointer to const: can't change the value through the pointer
    const int *ptr_to_const = &x;
    std::cout << "*ptr_to_const = " << *ptr_to_const << std::endl;
    ptr_to_const = &y;   // ✅ can point to different variable
    // *ptr_to_const = 99;  // ❌ would not compile — value is const

    // Const pointer: can't change what it points to
    int *const const_ptr = &x;
    *const_ptr = 50;     // ✅ can change the value
    // const_ptr = &y;   // ❌ would not compile — pointer itself is const
    std::cout << "x after *const_ptr = 50: " << x << std::endl;

    // ── 6. Pointer arithmetic ─────────────────────────────────────────────────
    demonstrate_pointer_arithmetic();

    // ── 7. nullptr ────────────────────────────────────────────────────────────
    std::cout << "\n=== 7. nullptr ===" << std::endl;

    int *valid_ptr = &score;
    int *null_ptr  = nullptr;

    check_pointer(valid_ptr);
    check_pointer(null_ptr);

    // ── 8. References vs pointers — summary ──────────────────────────────────
    std::cout << "\n=== 8. Reference vs Pointer Summary ===" << std::endl;
    std::cout << "References:" << std::endl;
    std::cout << "  - Must be initialized at declaration" << std::endl;
    std::cout << "  - Cannot be null" << std::endl;
    std::cout << "  - Cannot be reseated (always refers to same object)" << std::endl;
    std::cout << "  - Cleaner syntax — no * or & at use site" << std::endl;
    std::cout << "Pointers:" << std::endl;
    std::cout << "  - Can be null (nullptr)" << std::endl;
    std::cout << "  - Can be repointed to a different object" << std::endl;
    std::cout << "  - Required for dynamic memory (new/delete)" << std::endl;
    std::cout << "  - Required for pointer arithmetic" << std::endl;

    return 0;
}
