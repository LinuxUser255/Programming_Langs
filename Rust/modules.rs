//! modules.rs
//!
//! Introduction to Rust modules and project structure.
//! Shows how to organize code using mod, pub, and use.

fn main() {
    // Using items from the geometry module
    let rect: geometry::Rectangle = geometry::Rectangle {
        width: 10,
        height: 20,
    };

    println!("Rectangle area: {}", rect.area());
    println!("Rectangle perimeter: {}", rect.perimeter());

    // Using the math utilities
    let sum: i32 = math::add(15, 25);
    let product: i32 = math::multiply(6, 7);

    println!("Sum: {}", sum);
    println!("Product: {}", product);

    // Using a public function from a nested module
    let greeting: String = utils::strings::greet("Rust");
    println!("{}", greeting);
}

// ──────────────────────────────────────────────────────────────
// Module definitions
// ──────────────────────────────────────────────────────────────

// A module for geometry-related types and functions
mod geometry {
    pub struct Rectangle {
        pub width: i32,
        pub height: i32,
    }

    impl Rectangle {
        pub fn area(&self) -> i32 {
            self.width * self.height
        }

        pub fn perimeter(&self) -> i32 {
            2 * (self.width + self.height)
        }
    }
}

// A module for math utilities
mod math {
    pub fn add(a: i32, b: i32) -> i32 {
        a + b
    }

    pub fn multiply(a: i32, b: i32) -> i32 {
        a * b
    }
}

// A module with a nested module
mod utils {
    pub mod strings {
        pub fn greet(name: &str) -> String {
            format!("Hello, {}!", name)
        }
    }
}
