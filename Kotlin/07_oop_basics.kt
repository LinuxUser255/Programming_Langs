data class Person(val name: String, val age: Int) {
    fun introduce() {
        println("Hi, I'm $name and I'm $age years old.")
    }
}

fun main() {
    val p = Person("Emma", 27)
    p.introduce()
}
