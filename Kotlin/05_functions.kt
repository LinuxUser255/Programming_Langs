fun add(a: Int, b: Int): Int = a + b

fun greet(name: String, age: Int = 25) {
    println("Hello $name, you are $age")
}

fun main() {
    greet("Bob")
    greet("Alice", 32)
    println("Sum: ${add(5, 7)}")
}
