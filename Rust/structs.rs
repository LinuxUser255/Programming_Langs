// Basic example of structs in Rust
struct Person {
    name: String,
    age: u8,
}

impl Person {
    // Constructor method
    fn new(name: &str, age: u8) -> Person {
        Person {
            name: name.to_string(),
            age,
        }
    }

    // Method to print person's details
    fn print_details(&self) {
        println!("Name: {}, Age: {}", self.name, self.age);
    }
}

fn main() {
    let john = Person::new("John Doe", 30);
    john.print_details();
}
