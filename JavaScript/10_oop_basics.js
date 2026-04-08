#!/usr/bin/env node

class Person {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    introduce() {
        console.log(`Hi, I'm ${this.name} and I'm ${this.age} years old.`);
    }

    haveBirthday() {
        this.age++;
        console.log(`Happy birthday ${this.name}! Now ${this.age} years old.`);
    }
}

class Employee extends Person {
    constructor(name, age, job) {
        super(name, age);
        this.job = job;
    }

    introduce() {
        console.log(`Hi, I'm ${this.name}, a ${this.job}, ${this.age} years old.`);
    }
}

function oopBasics() {
    const p = new Person("Emma", 27);
    p.introduce();
    p.haveBirthday();

    const emp = new Employee("Bob", 35, "Software Engineer");
    emp.introduce();
}

function main() {
    oopBasics();
}

main();
