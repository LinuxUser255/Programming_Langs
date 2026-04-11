//! types.rs
//!
//! Comprehensive introduction to Rust's type system.
//! Covers primitive types, String vs &str, tuples, arrays,
//! and the difference between stack and heap allocation.

fn main() {
    // 1. Primitive scalar types
    let integer: i32 = 42;           // signed 32-bit integer (most common)
    let unsigned: u32 = 100;         // unsigned 32-bit integer
    let float: f64 = 3.14159;        // 64-bit floating point (default for decimals)
    let boolean: bool = true;
    let character: char = '🦀';       // Unicode scalar value (4 bytes)

    println!("Integer: {}", integer);
    println!("Unsigned: {}", unsigned);
    println!("Float: {}", float);
    println!("Boolean: {}", boolean);
    println!("Character: {}", character);

    // 2. String types - very important distinction!
    let string_literal: &str = "Hello, Rust!";           // &str = string slice (immutable, stored in binary)
    let owned_string: String = String::from("Owned string on the heap");

    println!("\nString literal (&str): {}", string_literal);
    println!("Owned String: {}", owned_string);

    // 3. Tuples - fixed-size, heterogeneous collections
    let person: (String, i32, bool) = ("Alice".to_string(), 30, true);
    println!("Tuple - Name: {}, Age: {}, Active: {}", person.0, person.1, person.2);

    // Destructuring a tuple
    let (name, age, _active) = person; // the underscore (_) tells Rust we don't use the bool
    println!("Destructured → Name: {}, Age: {}", name, age);

    // 4. Arrays - fixed size, same type, stored on the stack
    let numbers: [i32; 5] = [10, 20, 30, 40, 50];
    println!("\nArray first element: {}", numbers[0]);
    println!("Array length: {}", numbers.len());

    // 5. Quick demo of stack vs heap
    println!("\nNote:");
    println!("- Primitive types and arrays are usually on the stack.");
    println!("- String (owned) and Vec are on the heap.");
}
