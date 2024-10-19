// Example of a function that takes a vector of integers and returns the maximum value
fn find_max(numbers: &[i32]) -> Option<i32> {
    if numbers.is_empty() {
        None
    } else {
        let mut max_value = numbers[0];
        for &num in numbers {
            if num > max_value {
                max_value = num;
            }
        }
        Some(max_value)
    }
}

fn main() {
    let numbers = vec![3, 5, 2, 1, 4];
    if let Some(max_value) = find_max(&numbers) {
        println!("The maximum value is: {}", max_value);
    } else {
        println!("The vector is empty");
    }
}
