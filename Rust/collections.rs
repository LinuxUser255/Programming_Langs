//! collections.rs
//!
//! Introduction to Rust's most commonly used collections.
//! Covers Vec<T>, String, and HashMap<K, V> with explicit types.

use std::collections::HashMap;

fn main() {
    // 1. Vec<T> - growable array (most common collection)
    let mut numbers: Vec<i32> = Vec::new();

    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    numbers.push(40);

    println!("Vec contents:");
    for i in 0..numbers.len() {
        println!("numbers[{}] = {}", i, numbers[i]);
    }

    // 2. String - owned, growable UTF-8 string
    let mut greeting: String = String::from("Hello");
    greeting.push_str(", Rust!");

    println!("\nString: {}", greeting);
    println!("String length: {}", greeting.len());

    // 3. HashMap<K, V> - key-value store
    let mut scores: HashMap<&str, i32> = HashMap::new();

    scores.insert("Alice", 95);
    scores.insert("Bob", 82);
    scores.insert("Carol", 91);

    println!("\nHashMap contents:");
    match scores.get("Alice") {
        Some(score) => println!("Alice's score: {}", score),
        None => println!("Alice not found"),
    }

    match scores.get("Bob") {
        Some(score) => println!("Bob's score: {}", score),
        None => println!("Bob not found"),
    }

    // Iterate over the entire HashMap
    println!("\nAll scores:");
    for (name, score) in &scores {
        println!("{}: {}", name, score);
    }
}
