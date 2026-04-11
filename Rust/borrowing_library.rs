//! borrowing_library.rs
//!
//! A realistic library catalog system demonstrating Rust borrowing.
//!
//! Concepts covered (from Ownership-Basic.md sections 5, 6, 7):
//!   Section 5 — Borrowing: passing &T to read data without taking ownership
//!   Section 6 — Mutable references: &mut T for modification, exclusivity rule
//!   Section 7 — &str vs &String: using &str in function signatures for flexibility
//!
//! Each function has a single responsibility.
//! main() calls all functions and is placed at the bottom.
//!
//! Compile: rustc borrowing_library.rs && ./borrowing_library

// ── Data types ────────────────────────────────────────────────────────────────

#[derive(Debug)]
struct Book {
    title:     String,
    author:    String,
    year:      u32,
    available: bool,
    checkouts: u32,
}

#[derive(Debug)]
struct Member {
    name:           String,
    checked_out:    Vec<String>,
    total_borrowed: u32,
}

struct Catalog {
    books:   Vec<Book>,
    members: Vec<Member>,
}

// ── Construction helpers ──────────────────────────────────────────────────────

/// Create a new Book. Takes &str — flexible, no ownership required.
fn new_book(title: &str, author: &str, year: u32) -> Book {
    Book {
        title:     title.to_string(),
        author:    author.to_string(),
        year,
        available: true,
        checkouts: 0,
    }
}

/// Create a new Member. Takes &str (Section 7).
fn new_member(name: &str) -> Member {
    Member {
        name:           name.to_string(),
        checked_out:    Vec::new(),
        total_borrowed: 0,
    }
}

// ── Section 5: Immutable borrows — &T ────────────────────────────────────────

/// Print one book's details.
/// Takes &Book — borrows it, caller keeps ownership, book is valid after this call.
fn print_book(book: &Book) {
    let status = if book.available { "Available" } else { "Checked out" };
    println!(
        "  [{status}] \"{title}\" by {author} ({year}) — borrowed {checkouts}x",
        title     = book.title,
        author    = book.author,
        year      = book.year,
        checkouts = book.checkouts,
    );
}

/// Print the full catalog.
/// Takes &Catalog — read-only borrow of the whole structure.
fn print_catalog(catalog: &Catalog) {
    println!("\n── Catalog ({} books) ──────────────────────", catalog.books.len());
    for book in &catalog.books {   // &catalog.books yields &[Book]; each element is &Book
        print_book(book);
    }
}

/// Print all members.
/// Takes &[Member] — a borrowed slice; works with &Vec<Member> via deref coercion.
fn print_members(members: &[Member]) {
    println!("\n── Members ({} registered) ─────────────────", members.len());
    for member in members {
        if member.checked_out.is_empty() {
            println!("  {} — nothing checked out", member.name);
        } else {
            println!("  {} — has: {}", member.name, member.checked_out.join(", "));
        }
    }
}

/// Count available books.
/// Takes &Catalog — just reads, no mutation needed.
fn count_available(catalog: &Catalog) -> usize {
    catalog.books.iter().filter(|b| b.available).count()
}

/// Count a member's current loans.
/// Takes &Member — borrows, does not consume.
fn count_checked_out(member: &Member) -> usize {
    member.checked_out.len()
}

/// Build a one-line summary string.
/// Borrows &Catalog — reads everything it needs.
fn catalog_summary(catalog: &Catalog) -> String {
    let available   = count_available(catalog);
    let checked_out = catalog.books.len() - available;
    format!(
        "{} total | {} available | {} checked out | {} members",
        catalog.books.len(),
        available,
        checked_out,
        catalog.members.len(),
    )
}

/// Find a book by exact title.
/// Takes &str — accepts both literals and &String (Section 7).
/// Returns Option<&Book> — a borrowed reference into the catalog.
/// The lifetime of the returned &Book cannot outlive the &Catalog borrow.
fn find_book<'a>(catalog: &'a Catalog, title: &str) -> Option<&'a Book> {
    catalog.books.iter().find(|b| b.title == title)
}

/// Find a member by name.
/// Returns Option<&Member> — borrowed, not owned.
fn find_member<'a>(catalog: &'a Catalog, name: &str) -> Option<&'a Member> {
    catalog.members.iter().find(|m| m.name == name)
}

/// Collect all books by a given author.
/// &str parameter (Section 7) — accepts literals and &String equally.
/// Returns Vec<&Book> — a collection of borrowed references; no book data is copied.
fn books_by_author<'a>(catalog: &'a Catalog, author: &str) -> Vec<&'a Book> {
    catalog.books.iter().filter(|b| b.author == author).collect()
}

/// Case-insensitive title search.
/// Both parameters &str — no allocation, no ownership transfer.
fn title_matches(title: &str, query: &str) -> bool {
    title.to_lowercase().contains(&query.to_lowercase())
}

/// Search catalog by partial title.
/// &str query works whether it comes from a literal or a String variable (Section 7).
fn search_by_title<'a>(catalog: &'a Catalog, query: &str) -> Vec<&'a Book> {
    catalog.books.iter().filter(|b| title_matches(&b.title, query)).collect()
}

/// Find the most-borrowed book.
/// Returns a borrowed reference — no data copied, no ownership moved.
fn most_borrowed(catalog: &Catalog) -> Option<&Book> {
    catalog
        .books
        .iter()
        .max_by_key(|b| b.checkouts)
        .filter(|b| b.checkouts > 0)
}

/// Generate a loan receipt string for a member.
/// Takes &Member — borrows to read, caller keeps the Member.
fn generate_loan_receipt(member: &Member) -> String {
    if member.checked_out.is_empty() {
        return format!("{} has no books checked out.", member.name);
    }
    let mut receipt = format!("Loan receipt — {}:\n", member.name);
    for (i, title) in member.checked_out.iter().enumerate() {
        receipt.push_str(&format!("  {}. {}\n", i + 1, title));
    }
    receipt.push_str(&format!(
        "  Checked out: {} | All-time borrowed: {}",
        member.checked_out.len(),
        member.total_borrowed,
    ));
    receipt
}

// ── Section 7: &str utility functions ────────────────────────────────────────

/// Format a display label for a book.
/// Both parameters &str — works with literals and &String (Section 7).
fn format_book_label(title: &str, author: &str) -> String {
    format!("\"{}\" — {}", title, author)
}

/// Print a section header.
/// &str — flexible, zero allocation at the call site.
fn print_header(label: &str) {
    println!("\n╔══ {} ", label);
}

// ── Section 6: Mutable borrows — &mut T ──────────────────────────────────────

/// Check out a book to a member.
/// Takes &mut Catalog — exclusive mutable access.
/// While this call is running, no other borrow of catalog can exist.
fn checkout_book(catalog: &mut Catalog, member_name: &str, title: &str) -> Result<(), String> {
    let book_idx = catalog.books.iter().position(|b| b.title == title);
    let Some(book_idx) = book_idx else {
        return Err(format!("Book not found: \"{}\"", title));
    };

    if !catalog.books[book_idx].available {
        return Err(format!("\"{}\" is already checked out", title));
    }

    let member_idx = catalog.members.iter().position(|m| m.name == member_name);
    let Some(member_idx) = member_idx else {
        return Err(format!("Member not found: \"{}\"", member_name));
    };

    // Mutate book — exclusive mutable borrow in effect here
    catalog.books[book_idx].available   = false;
    catalog.books[book_idx].checkouts  += 1;

    // Clone the title string so we can store it in the member record
    let title_copy = catalog.books[book_idx].title.clone();

    // Mutate member record
    catalog.members[member_idx].checked_out.push(title_copy);
    catalog.members[member_idx].total_borrowed += 1;

    println!(
        "  ✓ \"{}\" → {}",
        catalog.books[book_idx].title,
        catalog.members[member_idx].name,
    );
    Ok(())
}

/// Return a book.
/// Takes &mut Catalog — needs to update both book and member record.
fn return_book(catalog: &mut Catalog, member_name: &str, title: &str) -> Result<(), String> {
    let book_idx = catalog.books.iter().position(|b| b.title == title);
    let Some(book_idx) = book_idx else {
        return Err(format!("Book not found: \"{}\"", title));
    };

    if catalog.books[book_idx].available {
        return Err(format!("\"{}\" is not checked out", title));
    }

    let member_idx = catalog.members.iter().position(|m| m.name == member_name);
    let Some(member_idx) = member_idx else {
        return Err(format!("Member not found: \"{}\"", member_name));
    };

    let has_it = catalog.members[member_idx].checked_out.iter().any(|t| t == title);
    if !has_it {
        return Err(format!("{} does not have \"{}\"", member_name, title));
    }

    // Mutate — exclusive &mut borrow
    catalog.books[book_idx].available = true;
    catalog.members[member_idx].checked_out.retain(|t| t != title);

    println!(
        "  ✓ \"{}\" returned by {}",
        title,
        catalog.members[member_idx].name,
    );
    Ok(())
}

/// Add a new book to the catalog.
/// Takes &mut Catalog and &str params (Section 7 — flexible, no owned String required).
fn add_book(catalog: &mut Catalog, title: &str, author: &str, year: u32) {
    let book = new_book(title, author, year);
    println!("  + Added: \"{}\" by {}", book.title, book.author);
    catalog.books.push(book);
}

/// Register a new member.
/// Takes &mut Catalog and &str for name (Section 7).
fn register_member(catalog: &mut Catalog, name: &str) {
    let member = new_member(name);
    println!("  + Member: {}", member.name);
    catalog.members.push(member);
}

/// Mark a single book unavailable (e.g. for repair).
/// Takes &mut Book — mutable borrow of one book, not the whole catalog.
/// While this borrow lives, nothing else can read or write that Book.
fn mark_unavailable(book: &mut Book, reason: &str) {
    book.available = false;
    println!("  ! \"{}\" marked unavailable: {}", book.title, reason);
}

// ── Catalog construction ──────────────────────────────────────────────────────

fn build_catalog() -> Catalog {
    Catalog {
        books: vec![
            new_book("The Rust Programming Language", "Steve Klabnik",      2019),
            new_book("Programming Rust",              "Jim Blandy",          2021),
            new_book("Rust in Action",                "Tim McNamara",        2021),
            new_book("The C Programming Language",    "Kernighan & Ritchie", 1988),
            new_book("Clean Code",                    "Robert Martin",       2008),
            new_book("The Pragmatic Programmer",      "Hunt & Thomas",       2019),
        ],
        members: vec![
            new_member("Alice"),
            new_member("Bob"),
            new_member("Carol"),
        ],
    }
}

// ── main — all functions called here ─────────────────────────────────────────

fn main() {
    // catalog is owned by main() for the entire program.
    // It is never moved — only borrowed (&) or mutably borrowed (&mut).
    let mut catalog = build_catalog();

    // ── Section 5: Immutable borrows ──────────────────────────────────────────
    print_header("Initial State");
    print_catalog(&catalog);          // &Catalog — read-only borrow
    print_members(&catalog.members);  // &[Member] slice borrow
    println!("\n  {}", catalog_summary(&catalog));

    // ── Section 7: &str vs &String ────────────────────────────────────────────
    print_header("&str accepts both literals and &String");

    // String literal — &str directly
    println!("  {}", format_book_label("The Rust Programming Language", "Steve Klabnik"));

    // &String — auto-deref coercion to &str (Section 7)
    let owned_title  = String::from("Programming Rust");
    let owned_author = String::from("Jim Blandy");
    println!("  {}", format_book_label(&owned_title, &owned_author));

    // ── find_book — returns &Book borrowed from catalog ───────────────────────
    print_header("find_book — borrowed reference");

    if let Some(book) = find_book(&catalog, "Clean Code") {
        print!("  Found: ");
        print_book(book);   // pass the &Book directly
    }

    if find_book(&catalog, "Missing Title").is_none() {
        println!("  \"Missing Title\" — not in catalog");
    }

    // ── books_by_author — Vec of borrowed &Book references ───────────────────
    print_header("books_by_author — &str param, Vec<&Book> result");

    let rust_books = books_by_author(&catalog, "Tim McNamara");
    println!("  Books by Tim McNamara:");
    for book in &rust_books {
        print_book(book);
    }

    // &String passed where &str expected — Section 7
    let author = String::from("Jim Blandy");
    let blandy_books = books_by_author(&catalog, &author);
    println!("  Books by {}:", author);
    for book in &blandy_books {
        print_book(book);
    }

    // ── search_by_title — &str query ──────────────────────────────────────────
    print_header("search_by_title — &str from literal and String");

    let results = search_by_title(&catalog, "rust");
    println!("  \"rust\" matches ({}):", results.len());
    for book in &results {
        print_book(book);
    }

    let owned_query  = String::from("programming");
    let results2     = search_by_title(&catalog, &owned_query);  // &String → &str
    println!("  \"{}\" matches ({}):", owned_query, results2.len());
    for book in &results2 {
        print_book(book);
    }

    // ── Section 6: Mutable borrows for checkout ───────────────────────────────
    print_header("checkout_book — &mut Catalog (exclusive access)");

    // Each call takes &mut catalog — exclusive while running, released after
    let ops = [
        ("Alice", "Clean Code"),
        ("Alice", "Rust in Action"),
        ("Bob",   "The Rust Programming Language"),
        ("Bob",   "Clean Code"),           // should fail — already out
        ("Carol", "Programming Rust"),
    ];

    for (member, title) in &ops {
        match checkout_book(&mut catalog, member, title) {
            Ok(())    => {}
            Err(msg) => println!("  ✗ {}", msg),
        }
    }

    // &mut borrow ended — catalog is readable again via & borrows
    print_catalog(&catalog);

    // ── mark_unavailable — &mut Book (single book, not whole catalog) ─────────
    print_header("mark_unavailable — &mut Book");

    mark_unavailable(&mut catalog.books[3], "water damage");
    println!("  Verified:");
    print_book(&catalog.books[3]);   // immutable borrow — fine now &mut is done

    // ── Loan receipts — &Member ───────────────────────────────────────────────
    print_header("generate_loan_receipt — &Member");

    // find_member returns &Member — borrowed from catalog
    for name in &["Alice", "Bob", "Carol"] {
        if let Some(member) = find_member(&catalog, name) {
            println!("\n{}", generate_loan_receipt(member));
        }
    }

    // ── Return books — &mut Catalog ───────────────────────────────────────────
    print_header("return_book — &mut Catalog");

    let returns = [
        ("Alice", "Clean Code"),
        ("Bob",   "The Rust Programming Language"),
        ("Alice", "Clean Code"),   // should fail — already returned
        ("Carol", "Clean Code"),   // should fail — Carol doesn't have it
    ];

    for (member, title) in &returns {
        match return_book(&mut catalog, member, title) {
            Ok(())    => {}
            Err(msg) => println!("  ✗ {}", msg),
        }
    }

    // ── Add books and members — &mut Catalog, &str params ─────────────────────
    print_header("add_book / register_member — &str params (Section 7)");

    add_book(&mut catalog, "Zero To Production In Rust", "Luca Palmieri", 2022);
    add_book(&mut catalog, "Rust for Rustaceans",        "Jon Gjengset",  2021);
    register_member(&mut catalog, "Dave");

    // ── most_borrowed — immutable borrow after all mutations ──────────────────
    print_header("most_borrowed — &Catalog after mutations");

    match most_borrowed(&catalog) {
        Some(book) => { print!("  Most borrowed: "); print_book(book); }
        None       => println!("  No books borrowed yet"),
    }

    // ── Final statistics — catalog still fully owned by main() ────────────────
    print_header("Final Statistics");

    println!("  Available:   {}", count_available(&catalog));
    println!("  Total books: {}", catalog.books.len());

    for member in &catalog.members {
        println!(
            "  {}: {} checked out | {} all-time",
            member.name,
            count_checked_out(member),
            member.total_borrowed,
        );
    }

    print_header("Final State");
    print_catalog(&catalog);
    print_members(&catalog.members);
    println!("\n  Summary: {}", catalog_summary(&catalog));

    println!("\n  catalog was owned by main() the entire time.");
    println!("  It was never moved — only lent via & and &mut.");
}
