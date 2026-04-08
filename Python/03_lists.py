#!/usr/bin/env python3

def lists():
    """09_lists.py - Lists examples"""
    print("=== LISTS ===")
    # Basic list operations
    fruits = ["apple", "banana", "cherry"]
    fruits.append("orange")
    fruits.insert(1, "mango")
    print("After append/insert:", fruits)

    # List slicing
    print("First two:          ", fruits[:2])
    print("Last two:           ", fruits[-2:])
    print("Every other item:   ", fruits[::2])

    # Common list methods
    numbers = [5, 2, 8, 1, 9]
    numbers.sort()
    print("Sorted:             ", numbers)
    numbers.reverse()
    print("Reversed:           ", numbers)
    numbers.remove(8)
    print("After remove(8):    ", numbers)
    print("Count of 2:         ", numbers.count(2))

    # List comprehension (very Pythonic)
    squares = [x ** 2 for x in range(1, 6)]
    print("Squares (comp):     ", squares)

def main():
    lists()

if __name__ == '__main__':
    main()
