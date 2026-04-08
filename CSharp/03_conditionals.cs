using System;

class Program {
    static void Main() {
        int age = 20;
        string result = age switch {
            < 18 => "Minor",
            >= 18 and < 65 => "Adult",
            _ => "Senior"
        };
        Console.WriteLine(result);
    }
}
