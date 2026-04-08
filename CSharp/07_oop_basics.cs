using System;

class Program
{
    class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }

        public Person(string name, int age)
        {
            Name = name;
            Age = age;
        }

        public void Introduce()
        {
            Console.WriteLine($"Hi, I'm {Name} and I'm {Age} years old.");
        }

        public void HaveBirthday()
        {
            Age++;
            Console.WriteLine($"Happy birthday {Name}! Now {Age} years old.");
        }
    }

    // Inheritance
    class Employee : Person
    {
        public string Job { get; set; }

        public Employee(string name, int age, string job) : base(name, age)
        {
            Job = job;
        }

        public new void Introduce()  // method hiding (or use virtual/override for polymorphism)
        {
            Console.WriteLine($"Hi, I'm {Name}, a {Job}, {Age} years old.");
        }
    }

    static void oopBasics()
    {
        Console.WriteLine("=== OOP BASICS ===");

        Person p = new Person("Emma", 27);
        p.Introduce();
        p.HaveBirthday();

        Employee emp = new Employee("Bob", 35, "Software Engineer");
        emp.Introduce();
    }

    static void Main(string[] args)
    {
        oopBasics();
    }
}
