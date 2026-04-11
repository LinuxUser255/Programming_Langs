// 09_memory_management.cpp
//
// Memory management in C++: stack vs heap, new/delete,
// RAII, and smart pointers (unique_ptr, shared_ptr).
//
// The golden rule: every `new` must have a matching `delete`.
// Smart pointers enforce this automatically.
//
// Compile: g++ -std=c++17 -Wall -o 09_memory_management 09_memory_management.cpp

#include <iostream>
#include <string>
#include <memory>    // unique_ptr, shared_ptr

// ── RAII — Resource Acquisition Is Initialization ────────────────────────────
// A class that manages a resource: acquires in constructor, releases in destructor.
// This pattern is the foundation of all modern C++ memory management.

class ManagedBuffer {
private:
    int  *data;
    int   size;

public:
    // Constructor: allocate on heap
    ManagedBuffer(int sz) : size(sz) {
        data = new int[sz];
        std::cout << "  ManagedBuffer: allocated " << sz << " ints on heap" << std::endl;
        for (int i = 0; i < sz; ++i) {
            data[i] = i * 10;
        }
    }

    // Destructor: automatically called when object goes out of scope
    ~ManagedBuffer() {
        delete[] data;
        std::cout << "  ManagedBuffer: freed heap memory (destructor called)" << std::endl;
    }

    void print() const {
        std::cout << "  Buffer contents: ";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Disable copy to keep ownership clear (Rule of Three/Five)
    ManagedBuffer(const ManagedBuffer &)            = delete;
    ManagedBuffer &operator=(const ManagedBuffer &) = delete;
};

// ── Simple class to demonstrate unique_ptr ────────────────────────────────────

class Widget {
public:
    std::string name;

    Widget(const std::string &n) : name(n) {
        std::cout << "  Widget '" << name << "' created" << std::endl;
    }

    ~Widget() {
        std::cout << "  Widget '" << name << "' destroyed" << std::endl;
    }

    void use() const {
        std::cout << "  Using widget: " << name << std::endl;
    }
};

// ── Function that would leak memory without smart pointers ────────────────────
// BAD pattern — shown for comparison only
void raw_pointer_leak_example() {
    std::cout << "\n  [raw pointer — no smart pointer, memory leak if exception thrown]" << std::endl;
    int *p = new int(42);
    std::cout << "  allocated: " << *p << std::endl;
    delete p;   // if an exception fired before this line, p would leak
    std::cout << "  freed manually" << std::endl;
}

int main() {
    // ── 1. Stack vs Heap ──────────────────────────────────────────────────────
    std::cout << "=== 1. Stack vs Heap ===" << std::endl;

    // Stack allocation — automatic, fast, limited size
    int stack_var = 42;
    std::cout << "Stack variable: " << stack_var << std::endl;
    std::cout << "Stack address:  " << &stack_var << std::endl;

    // Heap allocation — manual, larger, must free explicitly
    int *heap_var = new int(99);
    std::cout << "Heap variable:  " << *heap_var << std::endl;
    std::cout << "Heap address:   " << heap_var  << std::endl;
    delete heap_var;   // release heap memory
    heap_var = nullptr;   // prevent dangling pointer
    std::cout << "Heap memory freed" << std::endl;

    // ── 2. new and delete for arrays ──────────────────────────────────────────
    std::cout << "\n=== 2. new[] and delete[] ===" << std::endl;

    int size = 5;
    int *arr = new int[size];   // allocate array on heap

    for (int i = 0; i < size; ++i) {
        arr[i] = (i + 1) * 100;
    }

    std::cout << "Heap array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;   // must use delete[] for arrays, not delete
    arr = nullptr;
    std::cout << "Array freed" << std::endl;

    // ── 3. RAII — automatic cleanup ───────────────────────────────────────────
    std::cout << "\n=== 3. RAII ===" << std::endl;
    std::cout << "Creating ManagedBuffer (enters scope):" << std::endl;
    {
        ManagedBuffer buf(4);
        buf.print();
        std::cout << "  (buf goes out of scope here)" << std::endl;
    }   // destructor called automatically here — no manual delete needed
    std::cout << "After scope — memory already freed" << std::endl;

    // ── 4. Raw pointer memory leak example ───────────────────────────────────
    std::cout << "\n=== 4. Raw Pointer (manual) ===" << std::endl;
    raw_pointer_leak_example();

    // ── 5. unique_ptr — sole ownership ───────────────────────────────────────
    std::cout << "\n=== 5. unique_ptr — Sole Ownership ===" << std::endl;

    // make_unique is the preferred way — never use new with smart pointers
    std::unique_ptr<Widget> w1 = std::make_unique<Widget>("Button");
    w1->use();

    std::cout << "  Transferring ownership with std::move..." << std::endl;
    std::unique_ptr<Widget> w2 = std::move(w1);   // w1 is now empty
    w2->use();

    if (w1 == nullptr) {
        std::cout << "  w1 is now empty — it transferred ownership to w2" << std::endl;
    }

    // w2 goes out of scope here — Widget destructor called automatically
    std::cout << "  (w2 goes out of scope at end of block)" << std::endl;

    // ── 6. unique_ptr for arrays ──────────────────────────────────────────────
    std::cout << "\n=== 6. unique_ptr for Arrays ===" << std::endl;

    std::unique_ptr<int[]> arr2 = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        arr2[i] = i * i;
    }
    std::cout << "  unique_ptr array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;
    // freed automatically when arr2 goes out of scope

    // ── 7. shared_ptr — shared ownership ─────────────────────────────────────
    std::cout << "\n=== 7. shared_ptr — Shared Ownership ===" << std::endl;

    std::shared_ptr<Widget> sp1 = std::make_shared<Widget>("Slider");
    std::cout << "  sp1 use_count: " << sp1.use_count() << std::endl;

    {
        std::shared_ptr<Widget> sp2 = sp1;   // both now own the Widget
        std::cout << "  sp1 use_count after sp2 = sp1: " << sp1.use_count() << std::endl;
        sp2->use();
        std::cout << "  (sp2 goes out of scope here)" << std::endl;
    }   // sp2 destroyed — reference count drops to 1

    std::cout << "  sp1 use_count after sp2 out of scope: " << sp1.use_count() << std::endl;
    sp1->use();
    std::cout << "  (sp1 goes out of scope — Widget will be destroyed)" << std::endl;

    // ── 8. When to use which ──────────────────────────────────────────────────
    std::cout << "\n=== 8. Which Smart Pointer to Use ===" << std::endl;
    std::cout << "  unique_ptr  — default choice; one owner; zero overhead" << std::endl;
    std::cout << "  shared_ptr  — shared ownership; reference counted; slight overhead" << std::endl;
    std::cout << "  weak_ptr    — non-owning observer of a shared_ptr (breaks cycles)" << std::endl;
    std::cout << "  raw pointer — only for non-owning observation; never for ownership" << std::endl;
    std::cout << "  new/delete  — avoid in modern C++; use make_unique/make_shared" << std::endl;

    return 0;
}
