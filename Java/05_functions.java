public class Functions {
    static int add(int a, int b) {
        return a + b;
    }

    static void greet(String name, int age) {
        System.out.println("Hello " + name + ", you are " + age);
    }

    public static void main(String[] args) {
        greet("Bob", 25);
        greet("Alice", 32);
        System.out.println("Sum: " + add(5, 7));
    }
}
