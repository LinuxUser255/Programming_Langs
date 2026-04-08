#!/usr/bin/env node

function dictionaries() {
    console.log("=== OBJECTS (Dictionaries) ===");

    const person = {
        name: "Bob",
        age: 28,
        city: "New York",
        skills: ["JavaScript", "Node.js"]
    };

    console.log("Name:", person.name);
    console.log("Age (safe):", person.age ?? "Not found");

    person.age = 29;
    person.job = "Developer";
    console.log("After update:", person);

    console.log("\nAll keys:");
    Object.keys(person).forEach(key => console.log("  -", key));

    console.log("\nKey-Value pairs:");
    Object.entries(person).forEach(([key, value]) => {
        console.log(`  ${key}: ${value}`);
    });
}

function main() {
    dictionaries();
}

main();
