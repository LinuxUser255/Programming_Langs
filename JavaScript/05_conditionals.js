#!/usr/bin/env node

function conditionals() {
    const age = 20;

    if (age < 18) {
        console.log("Minor");
    } else if (age >= 18 && age < 65) {
        console.log("Adult");
    } else {
        console.log("Senior");
    }

    // Modern switch (or ternary)
    const status = "active";
    switch (status) {
        case "active":
            console.log("User is active");
            break;
        case "inactive":
            console.log("User is inactive");
            break;
        default:
            console.log("Unknown status");
    }
}

function main() {
    conditionals();
}

main();
