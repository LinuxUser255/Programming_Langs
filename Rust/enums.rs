//! enums.rs
//!
//! Introduction to Rust enums — one of Rust's most powerful features.
//! Covers basic enums, enums with data, and the match expression.

fn main() {
    // 1. Basic enum (no data)
    #[derive(Debug)]
    enum Color {
        Red,
        Green,
        Blue,
    }

    let favorite_color: Color = Color::Blue;
    let primary_color: Color = Color::Red;
    let secondary_color: Color = Color::Green;

    println!("Favorite color: {:?}", favorite_color);
    println!("Primary color:  {:?}", primary_color);
    println!("Secondary color: {:?}", secondary_color);

    // 2. Enum with data (most useful form)
    #[derive(Debug)]
    enum Message {
        Quit,
        Move { x: i32, y: i32 },
        Write(String),
        ChangeColor(i32, i32, i32),
    }

    let msg1: Message = Message::Quit;
    let msg2: Message = Message::Move { x: 10, y: 20 };
    let msg3: Message = Message::Write(String::from("Hello Rust!"));
    let msg4: Message = Message::ChangeColor(255, 0, 128);

    // 3. Using match to handle every variant
    fn process_message(msg: Message) {
        match msg {
            Message::Quit => println!("The program is quitting..."),

            Message::Move { x, y } => {
                println!("Moving to coordinates: ({}, {})", x, y);
            }

            Message::Write(text) => {
                println!("Writing message: {}", text);
            }

            Message::ChangeColor(r, g, b) => {
                println!("Changing color to RGB({}, {}, {})", r, g, b);
            }
        }
    }

    // Process every message variant
    process_message(msg1);
    process_message(msg2);
    process_message(msg3);
    process_message(msg4);
}
