//! lifetimes.rs
//!
//! Introduction to Rust lifetimes — one of the most important concepts
//! for understanding references and borrowing. Shows why lifetimes exist
//! and how the compiler uses them.

fn main() {
    // Example 1: A simple function that takes a reference
    let text: &str = "Hello, Rust lifetimes!";

    let result: &str = longest_word(text, "short");
    println!("The longest word is: {}", result);

    // Example 2: Multiple references with explicit lifetime annotation
    let string1: String = String::from("long string here");
    let string2: String = String::from("short");

    let longest: &str = longest_word(&string1, &string2);
    println!("Longest between two strings: {}", longest);
}

// This function takes two string slices and returns a reference to the longest one.
// The lifetime 'a tells the compiler that the returned reference will live
// at least as long as the shortest input reference.
fn longest_word<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
