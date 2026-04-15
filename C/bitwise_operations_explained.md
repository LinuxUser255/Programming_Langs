# Bitwise Operations Explained

Bitwise operators work directly on the bits of integer values. They are essential for flags, low-level hardware control, and optimization.

## Operators

| Operator | Meaning              | Example          |
|----------|----------------------|------------------|
| `&`      | AND                  | `a & b`          |
| `|`      | OR                   | `a | b`          |
| `^`      | XOR                  | `a ^ b`          |
| `~`      | NOT (complement)     | `~a`             |
| `<<`     | Left shift           | `a << n`         |
| `>>`     | Right shift          | `a >> n`         |

## Common Patterns

- **Setting a bit**: `flags |= (1 << bit_position)`
- **Clearing a bit**: `flags &= ~(1 << bit_position)`
- **Toggling a bit**: `flags ^= (1 << bit_position)`
- **Checking a bit**: `if (flags & (1 << bit_position))`

Use `uint8_t`, `uint32_t`, etc. from `<stdint.h>` for predictable sizes.

## Best Practices

- Use named constants for bit positions
- Comment your bit operations clearly
- Be careful with signed integers and right shifts (sign extension)
- Prefer bitwise for flags instead of multiple bool variables

## Exercises

1. Write a function that counts the number of set bits in a number.
2. Implement simple permission flags (read/write/execute) using bits.
3. Create a function that checks if a number is a power of 2 using bitwise ops.
4. Combine with your structs: add a bitfield for status flags in a struct.

---

**Compile**:
```bash
gcc -std=c23 -Wall -Wextra -Wpedantic bitwise_operations.c -o bitwise
```
