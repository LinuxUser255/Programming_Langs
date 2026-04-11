# Understanding Rust Ownership & Borrowing: A Beginner's Guide 🦀

**Step-by-step code walkthroughs using real-world analogies to make Rust's
ownership and borrowing system easy to understand.**

---

## Table of Contents

1. [What Is Ownership?](#1-what-is-ownership)
2. [Move Semantics — What Breaks and Why](#2-move-semantics--what-breaks-and-why)
3. [Clone vs Move](#3-clone-vs-move)
4. [Copy Types vs Non-Copy Types](#4-copy-types-vs-non-copy-types)
5. [Borrowing — Lending Without Giving Up Ownership](#5-borrowing--lending-without-giving-up-ownership)
6. [Mutable References and the Exclusivity Rule](#6-mutable-references-and-the-exclusivity-rule)
7. [&str vs &String — The Right Way to Borrow Strings](#7-str-vs-string--the-right-way-to-borrow-strings)
8. [Common Pitfalls](#8-common-pitfalls)
9. [Practical Exercise](#9-practical-exercise)
10. [Flow Chart — How Borrowing Works](#10-flow-chart--how-borrowing-works)
11. [Memory State Diagram](#11-memory-state-diagram)
12. [Ownership Timeline](#12-ownership-timeline)
13. [Code Review Checklist for Ownership & Borrowing](#13-code-review-checklist-for-ownership--borrowing)
14. [A Note on Lifetimes](#14-a-note-on-lifetimes)
15. [Summary](#15-summary)

---

## 1. What Is Ownership?

Ownership is Rust's answer to one of the hardest problems in systems
programming: **who is responsible for freeing memory, and when?**

In C, the programmer manually calls `malloc` and `free` — forget to free and
you have a memory leak; free too early and you have a use-after-free bug.
In Python or Java, a garbage collector tracks memory at runtime — safe but
adds overhead and unpredictability.

Rust takes a third path: **ownership rules enforced at compile time, with
zero runtime cost.**

### The Three Ownership Rules

These are the foundation of everything else in this document:

1. Every value in Rust has exactly one **owner**.
2. There can only be **one owner at a time**.
3. When the owner goes **out of scope**, the value is dropped (memory freed).

```rust
fn main() {
    // s1 comes into scope and owns the String on the heap
    let s1: String = String::from("hello");

    // s1 goes out of scope here — Rust calls drop() automatically
    // The memory holding "hello" is freed. No manual free() needed.
}
```

### Stack vs Heap — Why It Matters

Primitive types (`i32`, `bool`, `char`, `f64`) have a known, fixed size at
compile time. Rust stores them on the **stack** — fast allocation, fast
cleanup, automatically copied when assigned.

Types like `String` and `Vec` can grow at runtime. Rust stores their data
on the **heap** — the `String` variable on the stack holds a pointer, a
length, and a capacity. The actual characters live on the heap.

```
Stack                     Heap
┌──────────────────┐      ┌──────────────────┐
│ s1               │      │ h e l l o        │
│  ptr ────────────┼─────►│                  │
│  len: 5          │      └──────────────────┘
│  capacity: 5     │
└──────────────────┘
```

This distinction — stack vs heap — is why ownership rules apply to `String`
but not to `i32`. Stack values are cheap to copy. Heap values are not.

---

## 2. Move Semantics — What Breaks and Why

This is the most surprising thing about Rust for programmers coming from
Python, JavaScript, or C. When you assign a heap type to a new variable,
**the original variable becomes invalid.**

```rust
fn main() {
    let s1: String = String::from("hello");
    let s2: String = s1;   // s1 is MOVED into s2

    println!("{}", s1);    // ❌ compile error — s1 is no longer valid
    println!("{}", s2);    // ✅ s2 owns the String now
}
```

### What the compiler says

```
error[E0382]: borrow of moved value: `s1`
 --> src/main.rs:5:20
  |
2 |     let s1: String = String::from("hello");
  |         -- move occurs because `s1` has type `String`
3 |     let s2: String = s1;
  |                      -- value moved here
4 |
5 |     println!("{}", s1);
  |                    ^^ value borrowed here after move
```

The error message is readable and tells you exactly what happened and where.
This is one of Rust's strengths — the compiler is a teacher, not just a gatekeeper.

### Why Rust does this

If both `s1` and `s2` pointed to the same heap memory and both were
considered owners, Rust would try to free that memory twice when they both
went out of scope — a **double-free bug**, a serious security vulnerability
in C programs. Rust prevents this at compile time by making the move
explicit: after `let s2 = s1`, only `s2` owns the memory.

### 🏠 Real-World Analogy: House Deed

Think of it like transferring a house deed. When you sign the deed over to
someone else (`let s2 = s1`), you no longer own the house. You can't sell
it again (`println!("{}", s1)`) — you don't own it anymore. There is always
exactly one owner of the deed.

---

## 3. Clone vs Move

Sometimes you genuinely need two independent copies of heap data. Rust
provides `.clone()` for this — an explicit deep copy that allocates new
heap memory.

```rust
fn main() {
    let s1: String = String::from("hello");
    let s2: String = s1.clone();   // deep copy — new heap allocation

    // Both s1 and s2 are valid owners of separate "hello" strings
    println!("s1 = {}, s2 = {}", s1, s2);   // ✅ both work
}
```

### When to use clone

Use `.clone()` when you genuinely need two independent, modifiable copies
of the same data. It is explicit on purpose — Rust wants you to know that
heap allocation is happening. If you find yourself calling `.clone()`
frequently to satisfy the borrow checker, that is a signal to reach for
borrowing (`&`) instead, which avoids the allocation entirely.

```
Move:  one heap allocation, one owner        → fast, no copy
Clone: two heap allocations, two owners      → costs memory + time
Borrow: one heap allocation, temporary read  → fast, no copy, no ownership transfer
```

---

## 4. Copy Types vs Non-Copy Types

Integers, booleans, floats, and characters implement the `Copy` trait.
When you assign a `Copy` type to a new variable, Rust **copies the value**
on the stack instead of moving ownership. Both variables remain valid.

```rust
fn main() {
    let x: i32 = 5;
    let y: i32 = x;   // x is COPIED, not moved — i32 implements Copy

    // Both x and y are valid — no ownership transfer happened
    println!("x = {}, y = {}", x, y);   // ✅ both work

    let a: bool = true;
    let b: bool = a;   // also copied
    println!("a = {}, b = {}", a, b);   // ✅ both work
}
```

### Why does this not apply to String?

`String` does not implement `Copy` because copying it would require
allocating new heap memory — an operation that could be expensive and
should be explicit. The `Copy` trait is reserved for types where a bitwise
copy is cheap, safe, and has no side effects.

### The rule of thumb

| Type | Trait | Assignment behavior |
|---|---|---|
| `i32`, `f64`, `bool`, `char` | `Copy` | Copied — both variables valid |
| `String`, `Vec<T>`, `Box<T>` | Not `Copy` | Moved — original invalid |
| `&T` (references) | `Copy` | Copied — reference is cheap |

---

## 5. Borrowing — Lending Without Giving Up Ownership

Now that ownership is clear, borrowing makes sense: it lets you give a
function temporary access to your data **without giving up ownership.**

```rust
fn calculate_length(s: &String) -> usize {
    s.len()
}

fn main() {
    let s1: String = String::from("hello");
    let len: usize = calculate_length(&s1);   // lend s1 to the function

    // s1 is still valid — we only lent it, not gave it away
    println!("The length of '{}' is {}.", s1, len);   // ✅
}
```

### 🏠 Real-World Analogy: Lending a Book

- **You own the book** — like `s1` owns the String
- **Your friend borrows it** — like the function receives `&s1`
- **You still own it** while they're reading
- **They return it** when the function ends
- **You can lend it again** as many times as you want

### Step-by-step breakdown

**Step 1 — Function definition:**
```rust
fn calculate_length(s: &String) -> usize {
    s.len()
    // s is a reference — it can read but cannot take ownership
    // When this function ends, s disappears but the String data remains
}
```

**Step 2 — Creating the owner:**
```rust
let s1: String = String::from("hello");
// s1 owns the String "hello" on the heap
// s1 is responsible for freeing it when it goes out of scope
```

**Step 3 — Borrowing:**
```rust
let len: usize = calculate_length(&s1);
// &s1 creates a reference — a pointer to s1's data
// Ownership does NOT transfer — s1 still owns the String
```

**Step 4 — Using after borrowing:**
```rust
println!("The length of '{}' is {}.", s1, len);
// s1 is still valid — the borrow ended when calculate_length returned
```

### Multiple immutable borrows are always allowed

```rust
fn main() {
    let data: String = String::from("hello");

    let len1: usize = calculate_length(&data);   // ✅ first borrow
    let len2: usize = calculate_length(&data);   // ✅ second borrow
    let len3: usize = calculate_length(&data);   // ✅ third borrow

    println!("{} {} {}", len1, len2, len3);
    println!("Original: {}", data);              // ✅ still valid
}
```

---

## 6. Mutable References and the Exclusivity Rule

By default, Rust references are immutable — you can read through them but
not modify the data. To allow modification, you use `&mut`.

```rust
fn append_world(s: &mut String) {
    s.push_str(", world");   // ✅ allowed — mutable reference
}

fn main() {
    let mut s: String = String::from("hello");   // variable must be mut
    append_world(&mut s);                         // pass mutable reference
    println!("{}", s);                            // prints "hello, world"
}
```

### The Exclusivity Rule — the most important rule in Rust

**You can have either one mutable reference OR any number of immutable
references — never both at the same time.**

This is the rule that makes Rust safe for concurrent programming. It
eliminates **data races** at compile time — a data race requires two
simultaneous accesses to the same memory where at least one is a write.
Rust's borrow checker makes that impossible.

```rust
fn main() {
    let mut s: String = String::from("hello");

    let r1: &String = &s;      // immutable borrow
    let r2: &String = &s;      // ✅ second immutable borrow — fine
    let r3: &mut String = &mut s;   // ❌ compile error!

    println!("{}, {}, {}", r1, r2, r3);
}
```

### What the compiler says

```
error[E0502]: cannot borrow `s` as mutable because it is also borrowed as immutable
 --> src/main.rs:6:29
  |
4 |     let r1: &String = &s;
  |                        - immutable borrow occurs here
5 |     let r2: &String = &s;
6 |     let r3: &mut String = &mut s;
  |                             ^^^^^ mutable borrow occurs here
7 |
8 |     println!("{}, {}, {}", r1, r2, r3);
  |                            -- immutable borrow later used here
```

### Two mutable references to the same data — also forbidden

```rust
fn main() {
    let mut s: String = String::from("hello");

    let r1: &mut String = &mut s;
    let r2: &mut String = &mut s;   // ❌ compile error!

    println!("{}, {}", r1, r2);
}
```

```
error[E0499]: cannot borrow `s` as mutable more than once at a time
 --> src/main.rs:5:29
  |
4 |     let r1: &mut String = &mut s;
  |                             ------ first mutable borrow occurs here
5 |     let r2: &mut String = &mut s;
  |                             ^^^^^^ second mutable borrow occurs here
```

### Summary of the borrow rules

| Situation | Allowed? |
|---|---|
| Multiple `&T` (immutable) to same data | ✅ Yes |
| One `&mut T` (mutable) to same data | ✅ Yes |
| `&T` and `&mut T` to same data simultaneously | ❌ No |
| Two `&mut T` to same data simultaneously | ❌ No |

---

## 7. &str vs &String — The Right Way to Borrow Strings

This is one of the most practical improvements you can make to Rust
function signatures. Prefer `&str` over `&String` when a function only
needs to read string data.

```rust
// ❌ Less flexible — only accepts references to owned String
fn count_chars_limited(s: &String) -> usize {
    s.chars().count()
}

// ✅ More flexible — accepts both &String and &str literals
fn count_chars(s: &str) -> usize {
    s.chars().count()
}

fn main() {
    let owned: String = String::from("hello");
    let literal: &str = "world";

    // With &String parameter — must coerce or pass reference to String only
    count_chars_limited(&owned);            // ✅ works
    // count_chars_limited(literal);        // ❌ would not compile

    // With &str parameter — accepts everything
    count_chars(&owned);                    // ✅ auto-deref coercion
    count_chars(literal);                   // ✅ works directly
    count_chars("inline literal");          // ✅ works directly
}
```

### Why &str is more flexible

A `&String` is a reference to an owned heap-allocated string.
A `&str` is a string slice — it can point to a section of a `String`,
a string literal in the binary, or any contiguous sequence of UTF-8 bytes.
When you pass `&owned_string` to a function expecting `&str`, Rust
automatically coerces it via **deref coercion** — no extra cost, no
conversion.

### The rule

If a function only reads string data and does not need to know that it
came from an owned `String`, use `&str`. Reserve `&String` for when you
specifically need to call methods that only exist on `String`.

---

## 8. Common Pitfalls

### Pitfall 1: Trying to modify through an immutable reference

```rust
fn bad_function(s: &String) {
    s.push_str(" world");   // ❌ compile error — immutable reference
}

// Fix: use mutable reference
fn good_function(s: &mut String) {
    s.push_str(" world");   // ✅
}
```

### Pitfall 2: Confusing borrowing with moving

```rust
// ❌ Moves ownership — original becomes invalid after call
fn takes_ownership(s: String) -> usize {
    s.len()
}

// ✅ Borrows — original remains valid after call
fn borrows_reference(s: &String) -> usize {
    s.len()
}

fn main() {
    let s: String = String::from("hello");

    let len = takes_ownership(s);   // s is moved here
    // println!("{}", s);           // ❌ s is gone

    let s2: String = String::from("world");
    let len2 = borrows_reference(&s2);   // s2 is borrowed
    println!("{}", s2);                   // ✅ s2 still valid
}
```

### Pitfall 3: Dangling references

```rust
// ❌ This will not compile — returning a reference to local data
fn bad_example() -> &String {
    let s: String = String::from("hello");
    &s   // s will be dropped when function ends — reference would dangle
}
```

```
error[E0106]: missing lifetime specifier
 --> src/main.rs:2:25
  |
2 | fn bad_example() -> &String {
  |                     ^ expected named lifetime parameter
  |
  = help: this function's return type contains a borrowed value,
    but there is no value for it to be borrowed from
```

The fix is to return the owned `String` instead of a reference to it:

```rust
// ✅ Return ownership instead
fn good_example() -> String {
    let s: String = String::from("hello");
    s   // ownership moves to the caller
}
```

### Pitfall 4: Using a value after it has been moved

```rust
fn main() {
    let v1: Vec<i32> = vec![1, 2, 3];
    let v2: Vec<i32> = v1;   // v1 moved into v2

    println!("{:?}", v1);    // ❌ v1 is gone
    println!("{:?}", v2);    // ✅ v2 owns it now
}
```

Fix options: either use `v2` going forward, or clone if you need both:

```rust
let v2: Vec<i32> = v1.clone();   // now both are valid owners
```

---

## 9. Practical Exercise

```rust
//! borrowing_practice.rs
//!
//! Demonstrates multiple borrows to the same String
//! without transferring ownership.

fn count_words(text: &str) -> usize {
    text.split_whitespace().count()
}

fn count_chars(text: &str) -> usize {
    text.chars().count()
}

fn to_uppercase_copy(text: &str) -> String {
    text.to_uppercase()   // creates a new owned String — original unchanged
}

fn main() {
    let message: String = String::from("Rust is awesome!");

    // Borrow message multiple times — immutable borrows are always allowed
    let word_count: usize = count_words(&message);
    let char_count: usize = count_chars(&message);
    let upper: String = to_uppercase_copy(&message);   // returns new String

    // message is still valid — we only lent it, never gave it away
    println!("Message:    {}", message);
    println!("Words:      {}", word_count);
    println!("Characters: {}", char_count);
    println!("Uppercase:  {}", upper);
    println!("Original unchanged: {}", message);   // still "Rust is awesome!"
}
```

Compile and run:

```bash
rustc borrowing_practice.rs && ./borrowing_practice
```

Expected output:

```
Message:    Rust is awesome!
Words:      3
Characters: 16
Uppercase:  RUST IS AWESOME!
Original unchanged: Rust is awesome!
```

---

## 10. Flow Chart — How Borrowing Works

```
┌─────────────────────────────────────────────────────────────────┐
│                           PROGRAM START                         │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                    main() function                              │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ let message = String::from("Rust is awesome!");        │   │
│  │ 📚 OWNER: message owns "Rust is awesome!"              │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│              First Borrow                                       │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ let word_count = count_words(&message);                 │   │
│  │ 🤝 BORROW: &message creates immutable reference         │   │
│  │ 👀 READ-ONLY inside count_words — cannot modify         │   │
│  │ 📊 RESULT: Returns 3 (word count)                       │   │
│  │ 🔄 BORROW ENDS: reference dropped when function returns │   │
│  │ ✅ OWNER: message still owns the String                 │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│              Second Borrow                                      │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ let char_count = count_chars(&message);                 │   │
│  │ 🤝 BORROW: another immutable reference — always allowed │   │
│  │ 📊 RESULT: Returns 16 (character count)                 │   │
│  │ 🔄 BORROW ENDS: reference dropped when function returns │   │
│  │ ✅ OWNER: message still owns the String                 │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                    Print Results                                │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ println!("Message: {message}");                         │   │
│  │ ✅ VALID: message is still accessible                   │   │
│  │ 📤 OUTPUT: Message: Rust is awesome!                    │   │
│  │           Words: 3, Characters: 16                     │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                    End of main()                                │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ 🗑️  CLEANUP: message goes out of scope                  │   │
│  │ 💾 MEMORY: String "Rust is awesome!" is deallocated     │   │
│  │ No garbage collector. No manual free(). Automatic.      │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────┬───────────────────────────────────────────┘
                      │
                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                      PROGRAM END                                │
└─────────────────────────────────────────────────────────────────┘
```

---

## 11. Memory State Diagram

```
Stack Memory:                     Heap Memory:
┌───────────────────┐             ┌──────────────────────┐
│ main() frame      │             │                      │
│ ┌───────────────┐ │             │  R u s t   i s ...   │
│ │ message       │ │             │                      │
│ │  ptr ─────────┼─┼────────────►│  (String data)       │
│ │  len: 16      │ │             │                      │
│ │  cap: 16      │ │             └──────────────────────┘
│ │               │ │
│ │ word_count: 3 │ │   ← stack values (no heap involved)
│ │ char_count:16 │ │
│ └───────────────┘ │
└───────────────────┘

When count_words(&message) is called:
┌───────────────────┐
│ count_words frame │
│ ┌───────────────┐ │
│ │ text (ref)    │ │
│ │  ptr ─────────┼─┼────────────► same heap data as message
│ └───────────────┘ │              (no copy, no allocation)
└───────────────────┘

When count_words returns:
  - count_words frame is popped from stack
  - text reference is dropped
  - heap data is UNTOUCHED — message still owns it
```

---

## 12. Ownership Timeline

```
Time 0: message owns "Rust is awesome!" on the heap
Time 1: count_words borrows &message  (message still owns)
Time 2: count_words returns           (borrow ends, message still owns)
Time 3: count_chars borrows &message  (message still owns)
Time 4: count_chars returns           (borrow ends, message still owns)
Time 5: println! uses message         (message still owns)
Time 6: main() ends                   (message dropped, heap freed)
```

### Borrowing Rules Applied

- ✅ **Multiple immutable borrows**: Both functions borrowed simultaneously — allowed
- ✅ **No ownership transfer**: Original owner (`message`) retained control throughout
- ✅ **Scope safety**: References were valid only during each function call
- ✅ **Memory safety**: No dangling pointers, no double-free, no use-after-free
- ✅ **No runtime cost**: All checks happened at compile time — zero overhead

---

## 13. Code Review Checklist for Ownership & Borrowing

When reading or writing Rust code, work through these questions in order.
This is the mental model the borrow checker uses — learning to apply it
manually will help you write code that compiles first time.

### Step 1 — Who owns what?

Look at every `let` binding. If the type is a heap type (`String`, `Vec`,
`Box`, etc.), that binding owns memory on the heap. If it is a primitive
(`i32`, `bool`, `char`), it implements `Copy` and the ownership question
does not apply.

### Step 2 — Where does ownership transfer?

Look for function calls that take values **without** `&`. That is a move.
After a move, the original binding is invalid — any use of it after that
point will not compile. Spot moves before the compiler has to.

### Step 3 — What is borrowed and for how long?

Every `&` is an immutable borrow. Every `&mut` is an exclusive mutable
borrow. A borrow ends at the closing `}` of its scope, or earlier if the
reference is last used before then (Rust uses Non-Lexical Lifetimes — it
is smarter than just "end of block").

### Step 4 — Are there simultaneous conflicting borrows?

If you see both `&` and `&mut` to the same data in the same scope, the
code will not compile. If you see two `&mut` to the same data, same result.
The rule: one writer **or** many readers — never both.

### Step 5 — What gets dropped and when?

Every owned value is dropped at the end of its scope. If a struct owns a
`String`, when the struct is dropped, the `String` is dropped too. This is
deterministic — predictable, no GC pauses, no memory leaks.

### The checklist

```
□ Every String/Vec/Box has exactly one owner at any point in time
□ No value is used after it has been moved
□ No mutable reference exists while any immutable reference is alive
□ No two mutable references to the same data exist simultaneously
□ No reference outlives the data it points to (no dangling pointers)
□ .clone() is used intentionally — not as a workaround for borrow errors
□ Function signatures use &str not &String when the function only reads
□ Function signatures use &T not T when the caller should retain ownership
□ Variables declared mut are actually mutated somewhere
□ Every borrow is as short-lived as it needs to be
```

The first five items are **correctness** — enforced by the compiler.
The last five are **style and intent** — the compiler catches some of
these too (`unused_mut`, etc.) but they are worth checking manually.

If your code compiles and passes all ten, you have eliminated the entire
class of memory safety bugs — use-after-free, double-free, dangling
pointers, data races — that cause the majority of CVEs in C and C++ codebases.

---

## 14. A Note on Lifetimes

Everything in this document involves borrowing that the compiler can figure
out automatically. When code gets more complex — returning references from
functions, storing references inside structs — Rust needs more information
about **how long a reference is valid**. This is expressed with **lifetime
annotations** using the syntax `'a`:

```rust
// The lifetime annotation says: the returned reference lives
// at least as long as the input reference
fn longest<'a>(s1: &'a str, s2: &'a str) -> &'a str {
    if s1.len() > s2.len() { s1 } else { s2 }
}
```

Lifetimes are not a separate feature — they are an extension of the same
borrow checker rules covered in this document. If you understand ownership
and borrowing, lifetimes will make sense when you reach them.

The Rust Book covers lifetimes in Chapter 10:
`https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html`

---

## 15. Summary

Rust's ownership system is a **respectful lending library**:

- **One owner** at a time — no ambiguity about who frees memory
- **Borrow freely** — lend your data without giving it away
- **Multiple readers** are always safe — immutable borrows stack
- **One writer at a time** — exclusive access prevents data races
- **Automatic cleanup** — when the owner goes out of scope, memory is freed

The borrow checker enforces these rules at compile time. There is no
runtime overhead, no garbage collector, and no manual memory management.
The bugs that dominate C and C++ codebases — use-after-free, dangling
pointers, double-free, data races — cannot exist in safe Rust code.

That is not a claim about programmer skill. It is a guarantee from the
type system. 🦀

---

## See Also

- [The Rust Book — Understanding Ownership](https://doc.rust-lang.org/book/ch04-00-understanding-ownership.html)
- [The Rust Book — References and Borrowing](https://doc.rust-lang.org/book/ch04-02-references-and-borrowing.html)
- [The Rust Book — Lifetimes](https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html)
- [Rust by Example — Ownership and moves](https://doc.rust-lang.org/rust-by-example/scope/move.html)
- [Rustlings exercises](https://github.com/rust-lang/rustlings) — hands-on ownership practice
