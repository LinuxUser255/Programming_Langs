using System;

class Program
{
    // Helper methods (can be called from inside functions())
    static int add(int a, int b)
    {
        return a + b;
    }

    static void greet(string name, int age = 25)
    {
        Console.WriteLine($"Hello {name}, you are {age} years old.");
    }

    static void functions()
    {
        Console.WriteLine("=== FUNCTIONS ===");

        greet("Bob");
        greet("Alice", 32);
        Console.WriteLine($"Sum: {add(5, 7)}");

        // Variable arguments (params)
        static int sumAll(params int[] numbers)
        {
            int total = 0;
            foreach (int n in numbers) total += n;
            return total;
        }
        Console.WriteLine($"Sum of many numbers: {sumAll(1, 2, 3, 4, 5)}");

        // Action / lambda example
        Action<string> printMessage = msg => Console.WriteLine($"Message: {msg}");
        printMessage("This is a lambda!");
    }

    static void Main(string[] args)
    {
        functions();
    }
}
