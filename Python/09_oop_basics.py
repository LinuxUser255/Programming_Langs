#!/usr/bin/env python3

class Person:
    """Simple class for OOP demo"""
    def __init__(self, name: str, age: int):
        self.name = name
        self.age = age

    def introduce(self) -> None:
        print(f"Hi, I'm {self.name} and I'm {self.age} years old.")

    def have_birthday(self) -> None:
        self.age += 1
        print(f"Happy birthday {self.name}! Now {self.age} years old.")

def oop_basics():
    """07_oop_basics.py - Classes, objects, methods, inheritance"""
    p = Person("Emma", 27)
    p.introduce()
    p.have_birthday()

    # Inheritance demo
    class Employee(Person):
        def __init__(self, name: str, age: int, job: str):
            super().__init__(name, age)
            self.job = job

        def introduce(self) -> None:
            print(f"Hi, I'm {self.name}, a {self.job}, {self.age} years old.")

    # Create an employee object and call the introduce method
    emp = Employee("Bob", 35, "Software Engineer")
    emp.introduce()

def main():
    oop_basics()

if __name__ == '__main__':
    main()
