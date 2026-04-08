using System;

class Program
{
    static void loops()
    {
        Console.WriteLine("=== LOOPS ===");

        // For loop
        Console.Write("For loop: ");
        for (int i = 0; i < 5; i++)
        {
            Console.Write($"{i} ");
        }
        Console.WriteLine();

        // For-each (foreach)
        int[] numbers = { 10, 20, 30 };
        Console.Write("For-each: ");
        foreach (int num in numbers)
        {
            Console.Write($"{num} ");
        }
        Console.WriteLine();

        // While loop
        Console.WriteLine("While loop:");
        int count = 0;
        while (count < 3)
        {
            Console.WriteLine($"  While: {count}");
            count++;
        }

        // Modern for-each with LINQ style (range)
        Console.WriteLine("Range-based (0..4):");
        for (int i = 0; i < 5; i++)
        {
            Console.Write($"  {i}");
        }
        Console.WriteLine();
    }

    static void Main(string[] args)
    {
        loops();
    }
}
