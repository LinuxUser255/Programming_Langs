# Borrowing Library

Here's how the file is structured and what each section demonstrates:

**The scenario** is a library catalog — `Catalog` owns a `Vec<Book>` and a `Vec<Member>`. `main()` owns the `Catalog` for the entire program and never moves it — only lends it.

**Section 5 (immutable borrows)** — every read-only function takes `&Catalog`, `&Book`, or `&Member`. Functions like `print_book`, `find_book`, `books_by_author`, `search_by_title`, `most_borrowed`, and `generate_loan_receipt` all borrow without touching ownership. `find_book` and `books_by_author` return `Option<&Book>` and `Vec<&Book>` — borrowed references back into the catalog, with explicit lifetime annotations so the compiler knows those references can't outlive the catalog.

**Section 6 (mutable borrows)** — `checkout_book` and `return_book` take `&mut Catalog`. While either call is running, the catalog is exclusively locked — no other borrow can exist. After each call returns, the `&mut` ends and the catalog is immediately readable again via `&`. `mark_unavailable` demonstrates `&mut Book` — a mutable borrow of a single book, not the whole catalog.

**Section 7 (`&str` vs `&String`)** — every function that takes string input uses `&str`: `new_book`, `new_member`, `find_book`, `find_member`, `books_by_author`, `search_by_title`, `format_book_label`, `add_book`, `register_member`, `mark_unavailable`. In `main()` you can see both string literals and `&String` (via `&owned_title`) passed to the same functions without any conversion — the auto-deref coercion from `&String` to `&str` just works.
