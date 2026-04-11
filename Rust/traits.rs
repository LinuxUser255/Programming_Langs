//! traits.rs
//!
//! Introduction to Rust traits — the language's way of defining shared behavior.
//! Shows trait definition, implementation, and trait bounds.

fn main() {
    let dog: Dog = Dog { name: String::from("Buddy") };
    let cat: Cat = Cat { name: String::from("Whiskers") };

    println!("Dog says: {}", dog.make_sound());
    println!("Cat says: {}", cat.make_sound());

    // Using a trait bound function
    print_animal_sound(&dog);
    print_animal_sound(&cat);
}

// 1. Define a trait (like an interface)
trait Animal {
    fn make_sound(&self) -> String;
    fn describe(&self) -> String {
        String::from("This is an animal")
    }
}

// 2. Implement the trait for a concrete type
struct Dog {
    name: String,
}

impl Animal for Dog {
    fn make_sound(&self) -> String {
        format!("{} says Woof!", self.name)
    }
}

struct Cat {
    name: String,
}

impl Animal for Cat {
    fn make_sound(&self) -> String {
        format!("{} says Meow!", self.name)
    }
}

// 3. Function that accepts any type that implements the Animal trait
fn print_animal_sound<T: Animal>(animal: &T) {
    println!("Animal sound: {}", animal.make_sound());
}
