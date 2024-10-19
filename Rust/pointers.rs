// Example of pointers in Rust
fn main() {
    // Declare a mutable integer variable.
    let mut x = 5;

    // Create a pointer to the integer variable.
    let ptr_x = &mut x;

    // Change the value through the pointer.
    *ptr_x = 10;

    // Print the value through the pointer.
    println!("The value of x is: {}", x);

    // Declare a reference to a reference to an integer variable.
    let ptr_ptr_x = &ptr_x;

    // Change the value through the reference.
    **ptr_ptr_x = 20;

    // Print the value through the reference.
    println!("The value of x is: {}", x);
}
