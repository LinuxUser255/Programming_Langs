Beginner-friendly set of lessons covering **variables**, **data
types**, **functions**, and **control flow** in Rust, broken into digestible
parts with examples and hands-on exercises. This is perfect if you're
transitioning from Python, Bash, or C.

---

## 🧱 **Lesson 1: Variables & Mutability**

### ✅ Key Concepts:

* Variables are **immutable by default**
* Use `mut` to make them mutable
* Use `let` to define variables

### 📘 Example:

```rust
fn main() {
    let x = 5;       // immutable
    let mut y = 10;  // mutable

    println!("x = {}", x);
    y = y + 1;
    println!("y = {}", y);
}
```

### 🧠 Exercise:

1. Create an immutable variable `name` with your name.
2. Create a mutable variable `counter` and increase it twice.

---

## 🔢 **Lesson 2: Data Types**

### ✅ Key Concepts:

Rust is statically typed. You can declare types explicitly:

#### 🔸 Scalar types:

* `i32`, `u32` (integers)
* `f32`, `f64` (floats)
* `bool`
* `char` (single Unicode characters)

#### 🔹 Compound types:

* Tuples: `(i32, f64, char)`
* Arrays: `[i32; 3]`

### 📘 Example:

```rust
fn main() {
    let tup: (i32, f64, char) = (500, 6.4, 'z');
    let (x, y, z) = tup;

    let arr: [i32; 4] = [1, 2, 3, 4];
    println!("Tuple y: {}, Array[2]: {}", y, arr[2]);
}
```

### 🧠 Exercise:

1. Define a tuple with your age, height, and favorite character.
2. Create an array with 5 favorite numbers.

---

## 🛠️ **Lesson 3: Functions**

### ✅ Key Concepts:

* Functions use `fn` keyword
* Parameters must have types
* Return values use `->` and the last line is returned (no `return` needed)

### 📘 Example:

```rust
fn main() {
    greet("Alice");
    let result = square(4);
    println!("Square is: {}", result);
}

fn greet(name: &str) {
    println!("Hello, {}!", name);
}

fn square(x: i32) -> i32 {
    x * x
}
```

### 🧠 Exercise:

1. Write a function that takes a name and prints a greeting.
2. Write a function that takes two integers and returns their sum.

---

## 🔁 **Lesson 4: Control Flow (if, match, loops)**

### ✅ Key Concepts:

#### 🧮 `if` statements:

```rust
fn main() {
    let number = 7;
    if number < 10 {
        println!("Less than 10");
    } else {
        println!("10 or more");
    }
}
```

#### 🎯 `match` expressions:

```rust
fn main() {
    let code = 2;
    match code {
        1 => println!("One"),
        2 => println!("Two"),
        _ => println!("Other"),
    }
}
```

#### 🔁 Loops:

* `loop` → infinite
* `while` → condition
* `for` → iterator

```rust
fn main() {
    for i in 0..3 {
        println!("i = {}", i);
    }
}
```

### 🧠 Exercises:

1. Write a program that prints if a number is odd or even using `if`.
2. Use `match` to print a message based on a number (1 = "Low", 2 = "Medium", 3 = "High").
3. Write a loop that counts down from 5 to 1 using `for`.

---

## 📘 Suggested Format for Practice

Try each concept in a `.rs` file using:

```bash
rustc filename.rs && ./filename
```

Or use [https://play.rust-lang.org/](https://play.rust-lang.org/) to try examples interactively online.

---

Next topics: **ownership**, **borrowing**, and **structs/enums**?

**beginner-friendly lesson series for Rust's** core concepts of **Ownership**, **Borrowing**, and **Structs/Enums**, with explanations, examples, and small exercises after each.

---

## 🧠 **Lesson 5: Ownership**

### ✅ Key Concepts:

* Rust enforces memory safety **without a garbage collector** using **ownership rules**.
* Each value in Rust has a **single owner**.
* When ownership is transferred (moved), the old variable becomes invalid.

### 📘 Example:

```rust
fn main() {
    let s1 = String::from("hello");
    let s2 = s1; // s1 is moved into s2

    // println!("{}", s1); // ❌ Error: s1 is no longer valid
    println!("{}", s2);    // ✅ Ok
}
```

To **clone** instead of move:

```rust
let s1 = String::from("hello");
let s2 = s1.clone();  // now both are valid
```

### 🧠 Exercises:

1. Create a `String`, move it to another variable, and observe what happens.
2. Clone the string and print both variables.

---

## 📤 **Lesson 6: Borrowing & References**

### ✅ Key Concepts:

* You can **borrow** a variable using a **reference (`&`)**.
* **Immutable references** allow reading, **mutable references** allow modifying.
* At any given time:

  * Only **one mutable reference** OR
  * Any number of **immutable references**

### 📘 Example:

```rust
fn main() {
    let s = String::from("hello");

    // Immutable borrow
    print_string(&s);
    println!("After print: {}", s);

    // Mutable borrow
    let mut s2 = String::from("hi");
    change_string(&mut s2);
    println!("Changed: {}", s2);
}

fn print_string(s: &String) {
    println!("String is: {}", s);
}

fn change_string(s: &mut String) {
    s.push_str(", world!");
}
```

### 🧠 Exercises:

1. Write a function that takes a string reference and prints it.
2. Write a function that mutably borrows a string and appends "!" to it.

---

## 🏗️ **Lesson 7: Structs**

### ✅ Key Concepts:

* Structs group related data into a custom type.
* Can implement methods with `impl`.

### 📘 Example:

```rust
struct User {
    username: String,
    email: String,
    active: bool,
}

impl User {
    fn greet(&self) {
        println!("Hi, {}!", self.username);
    }
}

fn main() {
    let user1 = User {
        username: String::from("alice"),
        email: String::from("alice@example.com"),
        active: true,
    };

    user1.greet();
}
```

### 🧠 Exercises:

1. Define a `Book` struct with `title`, `author`, and `pages`.
2. Add a method `summary()` that prints a short summary.

---

## 🎭 **Lesson 8: Enums & Pattern Matching**

### ✅ Key Concepts:

* Enums define a type that can be one of many variants.
* Use `match` to handle different enum values.

### 📘 Example:

```rust
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
}

fn handle_message(msg: Message) {
    match msg {
        Message::Quit => println!("Quit message"),
        Message::Move { x, y } => println!("Move to ({}, {})", x, y),
        Message::Write(text) => println!("Message: {}", text),
    }
}

fn main() {
    let m1 = Message::Write(String::from("Hello"));
    let m2 = Message::Move { x: 10, y: 20 };

    handle_message(m1);
    handle_message(m2);
}
```

### 🧠 Exercises:

1. Define an enum `TrafficLight` with variants: `Red`, `Yellow`, `Green`.
2. Write a `match` statement that prints the action to take based on the light.

---

## 🗂️ Summary Table

| Concept   | Keyword          | Notes                         |
| --------- | ---------------- | ----------------------------- |
| Ownership | `let`, `move`    | One owner at a time           |
| Borrowing | `&`, `&mut`      | Shared or exclusive access    |
| Structs   | `struct`, `impl` | Define custom types           |
| Enums     | `enum`, `match`  | Choose from a set of variants |

---


