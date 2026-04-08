#!/usr/bin/env node

function dataStructures() {
    console.log("=== DATA STRUCTURES ===");

    // Array (dynamic list)
    let nums = [1, 2, 3, 4, 5];
    nums.push(6);
    console.log(`Array: ${nums} (length: ${nums.length})`);

    // Object (dictionary / hash map)
    const person = {
        name: "Alice",
        age: 30,
        active: true
    };
    console.log(`Object - Name: ${person.name}, Age: ${person.age}`);

    // Set (unique values)
    const unique = new Set([1, 2, 2, 3, 3, 4]);
    console.log(`Set (unique): ${[...unique]}`);
}

function main() {
    dataStructures();
}

main();
