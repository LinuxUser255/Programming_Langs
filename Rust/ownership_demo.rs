//! ownership_demo.rs
//!
//! Clear demonstration of Rust Ownership rules:
//! - Every value has a single owner
//! - When the owner goes out of scope, the value is dropped
//! - Assignment and function calls can move ownership
//! - You cannot use a value after it has been moved

fn main() {
    // 1. Basic ownership with String (heap-allocated)
    let s1: String = String::from("Hello, Rust!");

    println!("s1 owns the string: {}", s1);

    // 2. Moving ownership
    let s2: String = s1;           // s1 is moved into s2

    println!("s2 now owns the string: {}", s2);

    // The next line would cause a compile error:
    // println!("Trying to use s1 after move: {}", s1);

    // 3. Cloning to keep the original owner
    let s3: String = String::from("Original string");
    let s4: String = s3.clone();   // deep copy - both s3 and s4 own their data

    println!("s3: {}", s3);
    println!("s4 (clone of s3): {}", s4);

    // 4. Ownership and functions
    let s5: String = String::from("Passing to function");
    take_ownership(s5);            // s5 is moved into the function

    // s5 can no longer be used here (moved)

    // 5. Borrowing (temporary reference) - does not transfer ownership
    let s6: String = String::from("Borrowing example");
    borrow_string(&s6);            // &s6 creates a reference

    println!("s6 is still owned by main after borrowing: {}", s6);
}

// Takes ownership of the String
fn take_ownership(s: String) {
    println!("Function took ownership of: {}", s);
    // s is dropped here when the function ends
}

// Borrows the String (does not take ownership)
fn borrow_string(s: &String) {
    println!("Function borrowed the string: {}", s);
    // s goes out of scope here, but the original owner is unaffected
}
