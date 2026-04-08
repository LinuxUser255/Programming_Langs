#!/usr/bin/env python3

def add(a: int, b: int) -> int:
    """Helper function (defined outside)"""
    return a + b

def greet(name: str, age: int = 25) -> None:
    """Default parameters"""
    print(f"Hello {name}, you are {age} years old.")

def functions():
    """05_functions.py - Functions, args, *args, **kwargs"""
    greet("Bob")
    greet("Alice", 32)
    print(f"Sum: {add(5, 7)}")

    # Variable arguments
    def sum_all(*args):
        return sum(args)
    print(f"Sum of many numbers: {sum_all(1, 2, 3, 4, 5)}")

    # Keyword arguments
    def print_info(**kwargs):
        for key, value in kwargs.items():
            print(f"  {key}: {value}")
    print_info(name="Emma", age=27, city="NYC")

def main():
    functions()

if __name__ == '__main__':
    main()
