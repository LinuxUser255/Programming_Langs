
// `count_words`,  Takes a borrowed reference to a String (indicated as &String)
fn count_words(text: &String) -> usize {
    text.split_whitespace().count()
}


fn main() {

    // `reference_this` Retains ownership of the String
    let reference_this = String::from("Rust is awesome!");

    // the `&` creates a borrowed reference to the String without transferring ownership.
    count_words(&reference_this);


    println!("Message: {reference_this}");
}

