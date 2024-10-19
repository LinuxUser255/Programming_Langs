// Example of using a pointer in Rust
fn main() {
    // Create a mutable integer pointer
    let mut num_ptr = Box::new(5);

    // Dereference the pointer to get the value
    *num_ptr += 10;

    println!("Value of the pointer: {}", *num_ptr);
}
