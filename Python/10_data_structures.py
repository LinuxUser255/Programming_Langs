#!/usr/bin/env python3

def data_structures():
    """06_data_structures.py - Lists, Dicts, Sets, Tuples"""
    # List (dynamic array)
    nums = [1, 2, 3, 4, 5]
    nums.append(6)
    print(f"List: {nums} (length: {len(nums)})")

    # Tuple (immutable)
    point = (10, 20)
    print(f"Tuple: {point}")

    # Dictionary (hash map)
    person = {"name": "Alice", "age": 30, "active": True}
    print(f"Dict: {person}")
    print(f"Age: {person['age']}")

    # Set (unique elements)
    unique = {1, 2, 2, 3, 3, 4}
    print(f"Set (unique): {unique}")

    # Dict comprehension
    squares_dict = {x: x*x for x in range(6)}
    print(f"Dict comprehension: {squares_dict}")

def main():
    data_structures()

if __name__ == '__main__':
    main()
