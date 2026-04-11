//! closures.rs
//!
//! Introduction to Rust closures — anonymous functions that can capture
//! variables from their environment. Shows different capture modes and
//! common use cases with iterators.

fn main() {
    // 1. Basic closure
    let add: fn(i32, i32) -> i32 = |a: i32, b: i32| a + b;
    println!("2 + 3 = {}", add(2, 3));

    // 2. Closure that captures a variable from the environment
    let factor: i32 = 10;
    let multiply_by_factor = |x: i32| x * factor;   // captures factor by reference

    println!("7 * 10 = {}", multiply_by_factor(7));

    // 3. Mutable closure (captures by mutable reference)
    let mut counter: i32 = 0;
    let mut increment = || {
        counter += 1;
        counter
    };

    println!("Counter: {}", increment());
    println!("Counter: {}", increment());
    println!("Counter: {}", increment());

    // 4. Common use case: passing closure to iterator methods
    let numbers: Vec<i32> = vec![1, 2, 3, 4, 5, 6];

    let squares: Vec<i32> = numbers
        .iter()
        .map(|&x| x * x)                // closure passed to map
        .filter(|&x| x > 10)            // another closure
        .collect();

    println!("\nSquares greater than 10: {:?}", squares);
}
