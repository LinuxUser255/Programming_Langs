#!/usr/bin/env python3

def vars_consts():
    """02_variables_constants.py - Variables and Constants"""
    # Variables (dynamically typed with type hints)
    name: str = "Alice"
    age: int = 30
    height: float = 5.9
    is_active: bool = True

    # Constants (Python convention: UPPER_CASE)
    MAX_USERS: int = 100
    PI: float = 3.14159

    print(f"Name: {name}, Age: {age}, Height: {height}, Active: {is_active}")
    print(f"Max users: {MAX_USERS}, PI: {PI}")

def main():
    vars_consts()

if __name__ == '__main__':
    main()
