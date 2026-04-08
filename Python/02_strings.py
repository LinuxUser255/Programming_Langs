#!/usr/bin/env python3

def strings():
    """08_strings.py - Strings examples"""
    print("=== STRINGS ===")
    # Basic string creation and concatenation
    name = "Alice"
    greeting = "Hello, " + name + "!"
    print(greeting)

    # Modern f-strings (recommended)
    age = 30
    print(f"My name is {name} and I am {age} years old.")

    # Common string methods
    text = "   Python Programming   "
    print("Uppercase:          ", text.upper())
    print("Lowercase:          ", text.lower())
    print("Stripped:           ", text.strip())
    print("Split into words:   ", text.strip().split())
    print("Replace:            ", text.replace("Python", "Rust"))
    print("Starts with 'Py':   ", text.strip().startswith("Python"))

    # String slicing
    lang = "Python"
    print("First 3 chars:      ", lang[:3])
    print("Last 3 chars:       ", lang[-3:])
    print("Reversed:           ", lang[::-1])
    print("Every other char:   ", lang[::2])

def main():
    strings()

if __name__ == '__main__':
    main()
