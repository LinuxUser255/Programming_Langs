//! error_handling.rs
//!
//! Introduction to Rust's error handling using Result<T, E>.
//! Demonstrates match, the ? operator (not used here for teaching clarity),
//! expect(), and proper error propagation.

fn main() {
    // Example 1: Parsing a string to number (can fail)
    let user_input: &str = "42";
    let parsed_number: Result<i32, std::num::ParseIntError> = user_input.parse();

    match parsed_number {
        Ok(num) => println!("Successfully parsed number: {}", num),
        Err(e) => println!("Failed to parse number: {}", e),
    }

    // Example 2: Using expect() when we are certain the operation should succeed
    let safe_number: i32 = "100"
        .parse()
        .expect("This should always be a valid integer");

    println!("Safe number using expect(): {}", safe_number);

    // Example 3: Function that returns Result
    match divide(10, 2) {
        Ok(result) => println!("10 / 2 = {}", result),
        Err(error) => println!("Division error: {}", error),
    }

    match divide(10, 0) {
        Ok(result) => println!("10 / 0 = {}", result),
        Err(error) => println!("Division error: {}", error),
    }
}

// Function that returns a Result
fn divide(a: i32, b: i32) -> Result<i32, String> {
    if b == 0 {
        Err(String::from("Cannot divide by zero"))
    } else {
        Ok(a / b)
    }
}
