//! smart_pointers.rs
//!
//! Introduction to Rust smart pointers: Box<T>, Rc<T>, and Arc<T>.
//! Shows when to use each one and how they interact with ownership.

fn main() {
    // 1. Box<T> — owns data on the heap, fixed size on the stack
    let boxed_value: Box<i32> = Box::new(42);
    println!("Boxed value: {}", boxed_value);

    // 2. Rc<T> — enables multiple owners of the same data (single-threaded)
    let shared: std::rc::Rc<String> = std::rc::Rc::new(String::from("Shared data"));

    let owner1: std::rc::Rc<String> = std::rc::Rc::clone(&shared);
    let owner2: std::rc::Rc<String> = std::rc::Rc::clone(&shared);

    println!("Rc reference count: {}", std::rc::Rc::strong_count(&shared));
    println!("owner1: {}", owner1);
    println!("owner2: {}", owner2);

    // 3. Arc<T> — atomic reference counting (thread-safe)
    let thread_safe_shared: std::sync::Arc<String> =
        std::sync::Arc::new(String::from("Thread-safe shared data"));

    let t1: std::sync::Arc<String> = std::sync::Arc::clone(&thread_safe_shared);
    let t2: std::sync::Arc<String> = std::sync::Arc::clone(&thread_safe_shared);

    println!("\nArc reference count: {}", std::sync::Arc::strong_count(&thread_safe_shared));
    println!("t1: {}", t1);
    println!("t2: {}", t2);
}
