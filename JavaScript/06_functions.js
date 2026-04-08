#!/usr/bin/env node

function add(a, b) {
    return a + b;
}

function greet(name, age = 25) {
    console.log(`Hello ${name}, you are ${age} years old.`);
}

function functions() {
    greet("Bob");
    greet("Alice", 32);
    console.log(`Sum: ${add(5, 7)}`);

    // Rest parameters
    function sumAll(...numbers) {
        return numbers.reduce((acc, n) => acc + n, 0);
    }
    console.log(`Sum of many numbers: ${sumAll(1, 2, 3, 4, 5)}`);

    // Arrow function
    const printInfo = (name, age) => console.log(`Name: ${name}, Age: ${age}`);
    printInfo("Emma", 27);
}

function main() {
    functions();
}

main();
