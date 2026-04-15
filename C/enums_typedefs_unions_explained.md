# Enums, Typedefs, and Unions Explained

These three features help make your C code more readable, safer, and memory-efficient.

## 1. Enums (`enum`)

Enums give meaningful names to integer constants.

```c
enum Color { RED, GREEN, BLUE };
enum Color shirt = BLUE;
```

**C23 improvement: You can specify the underlying type:**
```c
enum Status : int { SUCCESS = 0, ERROR = -1 };
```
**Best practice:** Use enums for states, options, and flags instead of magic numbers.

## 2. Typedefs
`typedef` creates an alias for an existing type. It improves readability dramatically.
```c
typedef struct {
    char name[50];
    int age;
} Person;
```

Common uses:

- Shortening complex types
- Creating portable size-specific types (with stdint.h)
- Hiding struct keyword


## 3. Unions
A union is like a struct, but all members share the same memory location. The size of the union is the size of its largest member.

Use cases:

- Saving memory when only one value is needed at a time
- Type punning (advanced, use with caution)
- Implementing tagged unions (with an enum to track active member)

**Warning:** Only one member should be active at any time. Reading the wrong member causes undefined behavior.

### How This Connects to Previous Lessons

Works great with structs and malloc
Enums pair perfectly with switch statements
Typedefs make function pointers and complex declarations cleaner
Unions are useful in embedded systems and memory-constrained code
