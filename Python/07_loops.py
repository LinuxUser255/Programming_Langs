#!/usr/bin/env python3

def loops():
    """04_loops.py - for, while, list comprehensions"""
    # For loop
    print("For loop:")
    for i in range(5):
        print(f"  For: {i}", end=" ")
    print()

    # For-each style
    numbers = [10, 20, 30]
    print("For-each:")
    for num in numbers:
        print(f"  {num}", end=" ")
    print()

    # While loop
    print("While loop:")
    count = 0
    while count < 3:
        print(f"  While: {count}")
        count += 1

    # List comprehension (Pythonic)
    squares = [x * x for x in range(6)]
    print(f"List comprehension (squares): {squares}")

def main():
    loops()

if __name__ == '__main__':
    main()
