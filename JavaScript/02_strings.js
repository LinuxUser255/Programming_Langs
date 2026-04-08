#!/usr/bin/env node

function strings() {
    console.log("=== STRINGS ===");
    const name = "Alice";
    console.log("Hello, " + name + "!");

    const age = 30;
    console.log(`My name is ${name} and I am ${age} years old.`);

    let text = "   JavaScript Programming   ";
    console.log("Uppercase:", text.toUpperCase());
    console.log("Lowercase:", text.toLowerCase());
    console.log("Stripped:", text.trim());
    console.log("Split:", text.trim().split(" "));
    console.log("Replace:", text.replace("JavaScript", "TypeScript"));

    const lang = "JavaScript";
    console.log("First 4 chars:", lang.slice(0, 4));
    console.log("Reversed:", lang.split("").reverse().join(""));
}

function main() {
    strings();
}

main();
