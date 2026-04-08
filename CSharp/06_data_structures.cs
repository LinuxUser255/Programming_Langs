using System;
using System.Collections.Generic;

class Program
{
    static void dataStructures()
    {
        Console.WriteLine("=== DATA STRUCTURES ===");

        // List<T> (dynamic array)
        List<int> nums = new List<int> { 1, 2, 3, 4, 5 };
        nums.Add(6);
        Console.WriteLine($"List: [{string.Join(", ", nums)}] (length: {nums.Count})");

        // Dictionary<TKey, TValue>
        Dictionary<string, object> person = new Dictionary<string, object>
        {
            { "name", "Alice" },
            { "age", 30 },
            { "active", true }
        };
        Console.WriteLine($"Dict - Name: {person["name"]}, Age: {person["age"]}");

        // Adding / updating
        person["age"] = 31;
        person["job"] = "Developer";
        Console.WriteLine($"After update - Age: {person["age"]}, Job: {person["job"]}");

        // Set equivalent (HashSet<T>)
        HashSet<int> unique = new HashSet<int> { 1, 2, 2, 3, 3, 4 };
        Console.WriteLine($"HashSet (unique): [{string.Join(", ", unique)}]");

        // Looping through dictionary
        Console.WriteLine("\nDictionary items:");
        foreach (var kvp in person)
        {
            Console.WriteLine($"  {kvp.Key}: {kvp.Value}");
        }
    }

    static void Main(string[] args)
    {
        dataStructures();
    }
}
