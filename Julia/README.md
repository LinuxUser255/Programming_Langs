# Julia Basics

Beginner Julia programming lessons. Each file is self-contained and runnable.

## Requirements

Install Julia from [julialang.org](https://julialang.org/downloads/) or via your package manager:

```bash
# macOS
brew install julia

# Arch Linux
sudo pacman -S julia

# Ubuntu / Debian
sudo snap install julia --classic
```

## Running a file

```bash
julia 01_hello.jl
```

## Lessons

| File | Topic |
|------|-------|
| `01_hello.jl` | println, print, string interpolation |
| `02_strings.jl` | string operations, slicing, formatting |
| `03_lists.jl` | arrays, push!, pop!, comprehensions |
| `04_variables_constants.jl` | types, const, type conversion |
| `05_dictionaries.jl` | Dict, keys, values, iteration |
| `06_conditionals.jl` | if/elseif/else, ternary, chained comparisons |
| `07_loops.jl` | for, while, break, continue, zip, enumerate |
| `08_functions.jl` | functions, dispatch, lambdas, map/filter/reduce |
| `09_oop_basics.jl` | structs, multiple dispatch, abstract types |
| `10_data_structures.jl` | Array, Tuple, Dict, Set, Range, Stack, Queue |

## Key differences from Python

| Python | Julia |
|--------|-------|
| 0-based indexing | 1-based indexing |
| `list` | `Array` |
| `dict` | `Dict` |
| `def f(x):` | `function f(x) ... end` |
| `class` | `struct` + multiple dispatch |
| `None` | `nothing` |
| `True / False` | `true / false` |
| `and / or / not` | `&& / \|\| / !` |
| `len(x)` | `length(x)` |
| `print()` | `println()` / `print()` |
| `f"hello {name}"` | `"hello $name"` |

## Julia-specific things to know

- **1-based indexing** — arrays start at index 1, not 0. `arr[end]` gives the last element.
- **Multiple dispatch** — functions are specialised on the types of all their arguments, not just the first. This replaces class methods.
- **Immutable by default** — `struct` fields cannot be changed after creation. Use `mutable struct` when you need mutation.
- **No semicolons** — statements end at newlines. Semicolons suppress output in the REPL.
- **`!` in function names** — by convention, functions ending in `!` modify their arguments in place (`push!`, `pop!`, `sort!`).
- **Unicode** — Julia supports Unicode identifiers natively. `π`, `ℯ`, `α`, `Δx` are all valid variable names.
