//! testing.rs
//!
//! Introduction to Rust testing — unit tests, integration tests, and the test
//! attribute. Shows how to write and run tests using the built-in test framework.

fn main() {
    println!("Running the program...");
    println!("Sum of 2 + 3 = {}", add(2, 3));
}

// A simple function to test
fn add(a: i32, b: i32) -> i32 {
    a + b
}

// ──────────────────────────────────────────────────────────────
// Unit tests — placed in the same file for teaching purposes
// ──────────────────────────────────────────────────────────────

#[cfg(test)]
mod tests {
    use super::*;   // bring add() into scope for testing

    #[test]
    fn test_add_positive_numbers() {
        assert_eq!(add(2, 3), 5);
        assert_eq!(add(10, 20), 30);
    }

    #[test]
    fn test_add_negative_numbers() {
        assert_eq!(add(-5, 3), -2);
        assert_eq!(add(-10, -20), -30);
    }

    #[test]
    fn test_add_zero() {
        assert_eq!(add(0, 0), 0);
        assert_eq!(add(5, 0), 5);
    }

    #[test]
    #[should_panic(expected = "attempt to add with overflow")]
    fn test_add_overflow() {
        // This test is expected to panic on overflow (i32::MAX + 1)
        let _ = add(i32::MAX, 1);
    }
}
