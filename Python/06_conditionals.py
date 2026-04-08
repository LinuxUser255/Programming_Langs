#!/usr/bin/env python3

def conditionals():
    """03_conditionals.py - If/elif/else + match (Python 3.10+)"""
    age = 20

    if age < 18:
        print("Minor")
    elif 18 <= age < 65:
        print("Adult")
    else:
        print("Senior")

    # Modern match statement (Python 3.10+)
    status = "active"
    match status:
        case "active":
            print("User is active")
        case "inactive":
            print("User is inactive")
        case _:
            print("Unknown status")

def main():
    conditionals()

if __name__ == '__main__':
    main()
