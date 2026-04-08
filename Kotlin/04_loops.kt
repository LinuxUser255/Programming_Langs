fun main() {
    // For loop
    for (i in 0..4) {
        print("For: $i ")
    }
    println()

    // ForEach
    listOf(10, 20, 30).forEach { print("$it ") }
    println()

    // While
    var count = 0
    while (count < 3) {
        println("While: ${count++}")
    }
}
