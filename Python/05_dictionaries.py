#!/usr/bin/env python3

def dictionaries():
    """10_dictionaries.py - Dictionaries examples"""
    print("=== DICTIONARIES ===")
    # Dictionary creation and access
    person = {
        "name": "Bob",
        "age": 28,
        "city": "New York",
        "skills": ["Python", "JavaScript"]
    }

    print("Name:               ", person["name"])
    print("Age (safe get):     ", person.get("age"))
    print("Country (safe):     ", person.get("country", "Not found"))

    # Adding / updating keys
    person["age"] = 29
    person["job"] = "Developer"
    print("After update:       ", person)

    # Looping through dictionary
    print("\nAll keys:")
    for key in person.keys():
        print("  -", key)

    print("\nKey-Value pairs:")
    for key, value in person.items():
        print(f"  {key}: {value}")

    # Dictionary comprehension
    squares_dict = {x: x * x for x in range(6)}
    print("\nDict comprehension: ", squares_dict)

def main():
    dictionaries()

if __name__ == '__main__':
    main()
