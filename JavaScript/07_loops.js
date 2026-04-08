#!/usr/bin/env node

function loops() {
    console.log("=== LOOPS ===");

    // For loop
    console.log("For loop:");
    for (let i = 0; i < 5; i++) {
        process.stdout.write(`  For: ${i} `);
    }
    console.log();

    // For-of (range-based)
    const numbers = [10, 20, 30];
    console.log("For-of:");
    for (const num of numbers) {
        process.stdout.write(`  ${num} `);
    }
    console.log();

    // While
    console.log("While loop:");
    let count = 0;
    while (count < 3) {
        console.log(`  While: ${count}`);
        count++;
    }

    // Array methods (very JS-idiomatic)
    console.log("Array map:");
    const squares = [1, 2, 3, 4, 5].map(x => x * x);
    console.log(squares);
}

function main() {
    loops();
}

main();
