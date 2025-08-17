// 1: Define the Book struct - this is a compile-time definition
struct Book {
    pages: u32,
    rating: u8,
}

// 2: Program execution starts here
fn main() {
    // 3: Create a Book instance - memory is allocated on the stack
    // Ownership of the Book struct is transferred to the 'book' variable
    let book = Book::new(300, 4);

    // 4: Call display_page_count method - Rust automatically passes a reference
    // to 'book'
    // The `&self` parameter in the display_page_count(&self)
    // receives this borrowed reference (similar to Python's self)
    book.display_page_count();

    // 5: Call display_rating method - Another temporary borrow occurs
    // The book variable lends itself to the method via &self
    book.display_rating();

    // 6: End of main function scope - the Book struct is deallocated from the stack
}

impl Book {
    // Constructor method - called during step 3
    fn new(pages: u32, rating: u8) -> Self {
        Self { pages, rating }
    }

    // Method implementation - called during step 4
    // &self receives the borrowed reference to the book instance/object
    fn display_page_count(&self) {
        println!("Book has {} pages", self.pages);
    }

    // Method implementation - called during step 5
    // &self receives the borrowed reference to the book instance
    fn display_rating(&self) {
        println!("Book has a rating of {}/5", self.rating);
    }
}
