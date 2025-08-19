# Rust Ownership and Python OOP

```rust

struct Book {
    pages: u32,
    rating: u8,
}


impl Book {
    fn new(pages: u32, rating: u8) -> Self {
        Self { pages, rating }
    }

    fn display_page_count(&self) {
        println!("Pages: {}", self.pages);
    }

    fn display_rating(&self) {
        println!("Rating: {}/5", self.rating);
    }
}

fn main() {
    let book = Book::new(300, 4);
    book.display_page_count();
    book.display_rating();
}

```

```
```

## Step-by-Step Execution Order

**Step 1:** Program starts and calls the `main` function (entry point)

**Step 2:** Inside `main`, `Book::new(300, 4)` is called
- This creates a new `Book` instance with `pages: 300` and `rating: 4`
- The `Book` struct is allocated on the stack
- Ownership of this `Book` is given to the variable `book`

**Step 3:** `book.display_page_count()` is called
- The `book` variable **borrows** itself (`&self`) to the method
- Prints "Pages: 300"
- The borrow ends, ownership returns to `book`

**Step 4:** `book.display_rating()` is called
- Again, `book` **borrows** itself (`&self`) to the method
- Prints "Rating: 4/5"
- The borrow ends, ownership returns to `book`

**Step 5:** `main` function ends
- The `book` variable goes out of scope
- Rust automatically calls the destructor and frees the memory
- Program terminates

## Beginner-Friendly Ownership & Memory Management Explanation

### 🏠 Think of Ownership Like House Ownership

**Ownership Rules (The Golden Rules):**
1. Each value has exactly **one owner** at a time
2. When the owner goes out of scope, the value is **automatically cleaned up**
3. You can **borrow** values temporarily without taking ownership

### 📖 Let's Break Down Our Book Example

```rust
let book = Book::new(300, 4);  // 'book' OWNS the Book instance
```

**What happens here:**
- A `Book` struct is created in memory (on the stack)
- The variable `book` becomes the **owner** of this data
- Only `book` can decide what happens to this memory

### 🤝 Borrowing (The `&self` Magic)

```rust
fn display_page_count(&self) {  // &self means "borrow me temporarily"
    println!("Pages: {}", self.pages);
}
```

**What `&self` means:**
- "Hey, let me **borrow** this Book temporarily"
- "I promise to give it back when I'm done"
- "I won't modify it or steal ownership"

**When we call:**
```rust
book.display_page_count();  // book lends itself temporarily
```

**The borrowing process:**
1. `book` says: "Here, you can look at my data"
2. Method reads the data: `self.pages`
3. Method finishes and returns the "borrowed" book
4. `book` gets full ownership back

### 🧠 Memory Management Magic

**Traditional languages (like C++):**
```cpp
Book* book = new Book(300, 4);  // You create it
// ... use book ...
delete book;  // YOU must remember to delete it!
```

**Rust's automatic approach:**
```rust
{
    let book = Book::new(300, 4);  // Rust tracks this
    // ... use book ...
}  // Rust automatically cleans up here - NO MEMORY LEAKS!
```

### 🔄 Why This Prevents Common Bugs

**1. No Memory Leaks:**
- Rust automatically frees memory when owner goes out of scope
- You can't forget to clean up!

**2. No Use-After-Free:**
- Once `book` is gone, you can't accidentally use it
- Compiler prevents this at compile time!

**3. No Double-Free:**
- Only one owner means only one cleanup
- Impossible to free the same memory twice!

### 🎯 Key Takeaways for Beginners

1. **Ownership = Responsibility**: The owner is responsible for cleanup
2. **Borrowing = Temporary Access**: You can look but not keep
3. **Automatic Cleanup**: Rust handles memory management for you
4. **Compile-Time Safety**: Most memory bugs are caught before your program runs

This ownership system makes Rust programs both **fast** (no garbage collector) and **safe** (no memory bugs)!

---


## Object/Instance Creation Comparison:

```python
printer = Printer()           # Python: creates instance
```
```rust
let printer = Printer::new(); // Rust: creates instance
```

Both lines do **exactly the same thing** - they create a new instance of the Printer and assign it to a variable named `printer`.

## The Key Differences in Syntax:

### **Python's Magic**
```python
printer = Printer()  # Python automatically calls __init__
```
- Python automatically knows how to create instances
- `()` directly calls the class constructor

### **Rust's Explicitness**
```rust
let printer = Printer::new();  # Rust calls our custom constructor
```
- Rust requires explicit constructor functions
- `::new()` is a **convention** (not built-in magic)
- We had to write the `new()` function ourselves

## Why Rust Uses `::new()` Instead of `()`

```rust
// This WON'T work in Rust:
let printer = Printer();  // ❌ Error! Structs aren't callable

// This is the Rust way:
let printer = Printer::new();  // ✅ Calls our constructor function
```

## Memory-wise, They're Identical:

```python
printer = Printer()     # Creates object in memory, assigns to 'printer'
```
```rust
let printer = Printer::new();  // Creates struct in memory, assigns to 'printer'
```

**Both result in:**
- Memory allocated for the object/struct
- Variable holds reference to that memory
- Methods can be called on the instance


# Python OOP to Rust analyzed

```python

class Vehicle:
    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year
        # use a print statement to show the object's creation'
        print(f"I created a car object: {self.make} {self.model} {self.year}.")

# create an instance of the Vehicle class
# This is where the code execution begins
my_car = Vehicle("Toyota", "Camry", 2004)

```
**THE RUST EQUIVALENT WITH DETAILED BORROW CHECKER AND MEMORY MANAGEMENT**
```rust
struct Vehicle {
    make: String,
    model: String,
    year: u32,
}

impl Vehicle {
    fn new(make: String, model: String, year: u32) -> Self {
        // Print statement to show object creation
        println!("I created a car object: {} {} {}.", make, model, year);

        Self { make, model, year }
    }
}


fn main() {
    // This is where code execution begins
    let my_car = Vehicle::new("Toyota".to_string(), "Camry".to_string(), 2004);
}

```

## Side-by-Side Comparison:

### **Constructor with Data**
```python
def __init__(self, make, model, year):
    self.make = make        # Python: simple assignment
    self.model = model
    self.year = year
```
```rust
fn new(make: String, model: String, year: u32) -> Self {
    Self { make, model, year }  // Rust: ownership transfer
}
```

### **Instance Creation**
```python
my_car = Vehicle("Toyota", "Camry", 2004)  # Python: strings are immutable objects
```
```rust
let my_car = Vehicle::new("Toyota".to_string(), "Camry".to_string(), 2004);
// Rust: explicit string conversion and ownership transfer
```

## 🔍 Borrow Checker & Memory Management Deep Dive:

### **Step 1: String Creation & Ownership**
```rust
let my_car = Vehicle::new("Toyota".to_string(), "Camry".to_string(), 2004);
```

**What happens:**
1. `"Toyota".to_string()` creates a **heap-allocated** `String`
2. `"Camry".to_string()` creates another **heap-allocated** `String`
3. `2004` is a simple integer (stack-allocated)

### **Step 2: Ownership Transfer (The Magic)**
```rust
fn new(make: String, model: String, year: u32) -> Self {
    //     ^^^^^^        ^^^^^^
    //   OWNERSHIP    OWNERSHIP
    //   MOVED IN     MOVED IN
```

**Borrow Checker Analysis:**
- The `String` values are **moved** into the function parameters
- Original string literals are **consumed** (no longer accessible)
- Function **owns** the strings temporarily

### **Step 3: Struct Creation & Final Ownership**
```rust
Self { make, model, year }  // Ownership transferred to struct fields
```

**Memory Layout:**
```
Stack:                    Heap:
┌─────────────┐          ┌─────────────┐
│   my_car    │          │   "Toyota"  │ ← make points here
│  ┌────────┐ │          │             │
│  │ make   │─┼─────────→│   [T,o,y,o,t,a]
│  │ model  │─┼─────────→│   "Camry"   │ ← model points here
│  │ year   │ │          │             │
│  │  2004  │ │          │   [C,a,m,r,y]
│  └────────┘ │          └─────────────┘
└─────────────┘
```

## 🆚 Python vs Rust Memory Management:

### **Python's Approach:**
```python
my_car = Vehicle("Toyota", "Camry", 2004)
# Python: Reference counting + garbage collector
# Memory freed "eventually" when no more references exist
```

**Python Memory Timeline:**
1. Objects created in memory
2. References tracked automatically
3. Garbage collector runs periodically
4. Memory freed when convenient for Python

### **Rust's Approach:**
```rust
{
    let my_car = Vehicle::new("Toyota".to_string(), "Camry".to_string(), 2004);
    // Rust: Ownership tracking at compile time
    // Memory freed EXACTLY when my_car goes out of scope
}  // ← Memory freed HERE, guaranteed!
```

**Rust Memory Timeline:**
1. Objects created with explicit ownership
2. Borrow checker tracks ownership at compile time
3. Memory freed immediately when owner goes out of scope
4. **Zero runtime overhead** for memory management

## 🛡️ Borrow Checker Benefits:

### **Prevents Common Bugs:**
```python
# Python: This could cause issues
car1 = Vehicle("Toyota", "Camry", 2004)
car2 = car1  # Both reference same object
del car1     # car2 might still try to use deleted data
```

```rust
// Rust: Borrow checker prevents this at compile time
let car1 = Vehicle::new("Toyota".to_string(), "Camry".to_string(), 2004);
let car2 = car1;  // Ownership MOVED to car2
// println!("{}", car1.make);  // ❌ Compile error! car1 no longer valid
```

## 🎯 Key Takeaways:

1. **Explicit Ownership**: Rust makes ownership transfers explicit
2. **Compile-Time Safety**: Memory bugs caught before runtime
3. **Zero-Cost**: No garbage collector overhead
4. **Predictable**: Memory freed at exact, predictable points

The borrow checker ensures **memory safety** without **runtime cost** - something Python's garbage collector can't guarantee!

## Detailed explanation of `(&self)`
#### Refining your understanding

When you call `book.display_page_count()` on line 13, the `book` variable **lends** (or allows borrowing of) itself to the method. The `&self` parameter in the method signature is what **receives** this borrowed reference.

So it's more accurate to say:
- The `book` variable **lends itself** to the method
- The `&self` parameter **borrows** the `book` variable

## What `&self` Means in Detail

**`&self` is syntactic sugar** for a more explicit parameter. These two function signatures are equivalent:

```rust
// What you write (syntactic sugar)
fn display_page_count(&self) {
    println!("Book has {} pages", self.pages);
}

// What it actually means (expanded form)
fn display_page_count(self: &Self) {
    println!("Book has {} pages", self.pages);
}

// Or even more explicitly
fn display_page_count(self: &Book) {
    println!("Book has {} pages", self.pages);
}
```

## The Three Forms of `self`

1. **`self`** - Takes ownership (moves the value)
2. **`&self`** - Borrows immutably (read-only access)
3. **`&mut self`** - Borrows mutably (read-write access)

## What Happens During the Method Call

When you write `book.display_page_count()`:

1. Rust automatically passes a reference to `book` as the first argument
2. This reference becomes the `&self` parameter inside the method
3. The method can read the data through this reference
4. When the method ends, the borrow ends
5. The `book` variable regains full control

## Why Use `&self` Instead of `self`?

If we used `self` (without the `&`):

```rust
// This would take ownership and consume the book!
fn display_page_count(self) {  // No & here
    println!("Book has {} pages", self.pages);
    // book is consumed here and can't be used again
}

fn main() {
    let book = Book::new(300, 4);
    book.display_page_count();  // book is moved here
    book.display_rating();      // ERROR! book was already consumed
}
```

By using `&self`, we only borrow the data temporarily, allowing multiple method calls on the same instance.

## Memory Perspective

```rust
fn main() {
    let book = Book::new(300, 4);  // book owns the Book instance

    // When calling book.display_page_count():
    // - book temporarily lends a reference to its data
    // - &self receives this reference
    // - book still owns the data, just can't modify it during the borrow
    book.display_page_count();

    // Borrow ends, book regains full control
    book.display_rating();  // Another temporary borrow

    // book goes out of scope and the Book instance is deallocated
}
```

So `&self` is the mechanism that allows methods to access the instance's data without taking ownership of it, enabling multiple method calls on the same object.


## Python method to class attribute interface
There are strong conceptual similarities between Rust's `&self` and Python's `self`, but with some important differences due to Rust's ownership system.

## Similarities with Python

**Python:**
```python
class Car:
    def __init__(self, make, model):
        self.make = make
        self.model = model

    def display_info(self):  # self is the instance reference
        print(f"Car: {self.make} {self.model}")

car = Car("Toyota", "Camry")
car.display_info()  # Python automatically passes 'car' as 'self'
```

**Rust:**
```rust
struct Car {
    make: String,
    model: String,
}

impl Car {
    fn new(make: String, model: String) -> Self {
        Self { make, model }
    }

    fn display_info(&self) {  // &self is the borrowed instance reference
        println!("Car: {} {}", self.make, self.model);
    }
}

let car = Car::new("Toyota".to_string(), "Camry".to_string());
car.display_info();  // Rust automatically passes a reference to 'car' as '&self'
```

## Key Similarities

1. **Automatic passing**: Both languages automatically pass the instance as the first parameter
2. **Method syntax**: Both use `instance.method()` syntax
3. **Access to fields**: Both allow accessing instance data through `self`
4. **Instance methods**: Both distinguish between instance methods and static/associated functions

## Key Differences (Due to Rust's Ownership)

| Aspect                | Python                              | Rust                                     |
| --------------------- | ----------------------------------- | ---------------------------------------- |
| **Memory Management** | Garbage collected                   | Manual ownership                         |
| **Borrowing**         | No concept of borrowing             | Explicit borrowing with `&`              |
| **Mutability**        | Objects mutable by default          | Must explicitly use `&mut self`          |
| **Ownership**         | References don't transfer ownership | `self` vs `&self` vs `&mut self` matters |

## Rust's Three Forms of `self` (Python only has one)

```rust
impl Book {
    // 1. Takes ownership (consumes the instance)
    fn consume_book(self) {
        println!("Book consumed!");
        // book is dropped here
    }

    // 2. Borrows immutably (read-only, like Python's self)
    fn display_page_count(&self) {
        println!("Book has {} pages", self.pages);
    }

    // 3. Borrows mutably (read-write access)
    fn update_rating(&mut self, new_rating: u8) {
        self.rating = new_rating;
    }
}
```

## Updated Comments for the Book struct exmple

```rust
// 1: Define the Book struct - this is a compile-time definition
struct Book {
    pages: u32,
    rating: u8,
}


impl Book {
    // Constructor method - called during step 3
    fn new(pages: u32, rating: u8) -> Self {
        Self { pages, rating }
    }

    // Method implementation - called during step 4
    // &self receives the borrowed reference to the book instance
    fn display_page_count(&self) {
        println!("Book has {} pages", self.pages);
    }

    // Method implementation - called during step 5
    // &self receives the borrowed reference to the book instance
    fn display_rating(&self) {
        println!("Book has a rating of {}/5", self.rating);
    }
}


// 2: Program execution starts here
fn main() {
    // 3: Create a Book instance - memory is allocated on the stack
    // Ownership of the Book struct is transferred to the 'book' variable
    let book = Book::new(300, 4);

    // 4: Call display_page_count method - Rust automatically passes a reference to 'book'
    // The &self parameter receives this borrowed reference (similar to Python's self)
    book.display_page_count();

    // 5: Call display_rating method - Another temporary borrow occurs
    // The book variable lends itself to the method via &self
    book.display_rating();

    // 6: End of main function scope - the Book struct is deallocated from the stack
}

```

Rust's `&self` serves a very similar purpose to Python's `self`, but with the added complexity of Rust's ownership and borrowing system that ensures memory safety at compile time.

