//! iterators.rs
//!
//! Introduction to Rust iterators — one of the most powerful and idiomatic
//! features in Rust. Shows how to create, consume, and chain iterators.

fn main() {
    // 1. Basic iterator from a range
    println!("Iterating over a range:");
    for i in 0..5 {
        println!("i = {}", i);
    }

    // 2. Iterator from a Vec
    let numbers: Vec<i32> = vec![10, 20, 30, 40, 50];

    println!("\nIterating over a Vec using .iter():");
    for num in numbers.iter() {
        println!("Value: {}", num);
    }

    // 3. Consuming iterator (takes ownership)
    let fruits: Vec<String> = vec![
        String::from("apple"),
        String::from("banana"),
        String::from("cherry"),
    ];

    println!("\nConsuming iterator with .into_iter():");
    for fruit in fruits.into_iter() {
        println!("Fruit: {}", fruit);
    }
    // fruits is no longer usable after .into_iter()

    // 4. Iterator adapters (chaining methods)
    let data: Vec<i32> = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

    let result: i32 = data
        .iter()                    // create iterator
        .filter(|&x| x % 2 == 0)   // keep only even numbers
        .map(|&x| x * x)           // square each number
        .sum();                    // sum the results

    println!("\nSum of squares of even numbers: {}", result);

    // 5. Using .collect() to build a new collection
    let words: Vec<&str> = vec!["hello", "rust", "world"];

    let uppercase: Vec<String> = words
        .iter()
        .map(|&w| w.to_uppercase())
        .collect();

    println!("\nUppercase words: {:?}", uppercase);
}
