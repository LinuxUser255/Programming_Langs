//! borrowing_examples.rs
//!
//! Three clear examples of borrowing in Rust based on section 5 of
//! Rust-Ownership-Basic.md — "Borrowing — Lending Without Giving Up Ownership".
//! Demonstrates immutable borrowing, multiple borrows, and practical usage.

// Example 1 helper function
fn calculate_length(s: &String) -> usize {
    s.len()
}

// Example 2 helper functions
fn count_words(text: &str) -> usize {
    text.split_whitespace().count()
}

fn count_chars(text: &str) -> usize {
    text.chars().count()
}

// Example 3: A simple struct to demonstrate borrowing
struct Person {
    name: String,
    age: i32,
}

fn get_person_summary(person: &Person) -> String {
    format!("{} is {} years old.", person.name, person.age)
}

fn main() {
    // ──────────────────────────────────────────────────────────────
    // Example 1: Basic immutable borrowing (from Rust-Ownership-Basic.md)
    // ──────────────────────────────────────────────────────────────
    let s1: String = String::from("hello");

    let len: usize = calculate_length(&s1);   // lend s1 to the function

    println!("Example 1 - The length of '{}' is {}.", s1, len);

    // s1 is still valid here — we only borrowed it

    // ──────────────────────────────────────────────────────────────
    // Example 2: Multiple immutable borrows (allowed simultaneously)
    // ──────────────────────────────────────────────────────────────
    let message: String = String::from("Rust borrowing is safe!");

    let word_count: usize = count_words(&message);
    let char_count: usize = count_chars(&message);

    println!("\nExample 2 - Message:    {}", message);
    println!("            Words:      {}", word_count);
    println!("            Characters: {}", char_count);

    // message is still fully owned by main()

    // ──────────────────────────────────────────────────────────────
    // Example 3: Borrowing a struct (practical real-world pattern)
    // ──────────────────────────────────────────────────────────────
    let person: Person = Person {
        name: String::from("Alice"),
        age: 32,
    };

    let summary: String = get_person_summary(&person);

    println!("\nExample 3 - {}", summary);
    println!("Person still exists: {} is {} years old.", person.name, person.age);
}

