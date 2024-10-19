// Example of a loop in Rust
fn main() {
    // A for loop is used to iterate over a range of values.
    for i in 0..10 {
        println!("Value of i is: {}", i);
    }

    // A while loop is used to repeat a block of code until a certain condition is met.
    let mut j = 0;
    while j < 10 {
        println!("Value of j is: {}", j);
        j += 1;
    }

    // A loop with a break statement is used to terminate the loop early.
    let mut k = 0;
    loop {
        println!("Value of k is: {}", k);
        k += 1;
        if k == 10 {
            break;
        }
    }
}
