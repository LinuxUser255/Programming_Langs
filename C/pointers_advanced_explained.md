# Advanced Pointers Explained

## 1. Function Pointers

A pointer that points to a function instead of data.

```c
typedef int (*MathOperation)(int, int);
```


## Uses of Function Pointers

- Callbacks
- Plugin systems
- State machines
- Sorting with custom comparators (`qsort`)

## 2. Void Pointers (`void*`)

Generic pointers that can point to any data type. You **must** cast them before dereferencing.

**Common in:**

- `malloc()` / `free()`
- Generic data structures
- Library APIs

## 3. Const Correctness with Pointers

- `const int *p` → pointer to const int (cannot change the value through this pointer)
- `int *const p` → const pointer (cannot change where the pointer points)
- `const int *const p` → const pointer to const int (neither the pointer nor the value can be changed)

**Rule**: Use `const` everywhere you can — it prevents bugs and clearly documents intent.

## Best Practices

- Use `typedef` to make function pointer types readable
- Always document what a function pointer expects
- Be extremely careful with `void*` casts
- Prefer arrays of function pointers over large `switch` statements

## Exercises

1. Write a calculator that uses an array of function pointers for `+`, `-`, `*`, `/`.
2. Implement a simple callback system (e.g., a button press handler).
3. Create a generic `swap` function using `void*` and `memcpy`.
4. Add function pointers to one of your earlier multi-file examples.



