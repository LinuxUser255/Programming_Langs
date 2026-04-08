#!/usr/bin/env node

function varsConsts() {
    // Variables
    let name = "Alice";
    let age = 30;
    const height = 5.9;
    let isActive = true;

    // Constants (const)
    const MAX_USERS = 100;
    const PI = 3.14159;

    console.log(`Name: ${name}, Age: ${age}, Height: ${height}, Active: ${isActive}`);
    console.log(`Max users: ${MAX_USERS}, PI: ${PI}`);
}

function main() {
    varsConsts();
}

main();
