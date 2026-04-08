#!/usr/bin/env node

function lists() {
    console.log("=== ARRAYS (Lists) ===");
    let fruits = ["apple", "banana", "cherry"];
    fruits.push("orange");
    fruits.splice(1, 0, "mango");
    console.log("After push/splice:", fruits);

    console.log("First two:", fruits.slice(0, 2));
    console.log("Last two:", fruits.slice(-2));

    let numbers = [5, 2, 8, 1, 9];
    numbers.sort((a, b) => a - b);
    console.log("Sorted:", numbers);

    const squares = Array.from({ length: 5 }, (_, i) => (i + 1) ** 2);
    console.log("Squares:", squares);
}

function main() {
    lists();
}

main();
