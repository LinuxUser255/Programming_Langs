fun main() {
    val age = 20

    val result = when {
        age < 18 -> "Minor"
        age in 18..64 -> "Adult"
        else -> "Senior"
    }
    println(result)

    val status = "active"
    println(when (status) {
        "active" -> "User is active"
        else -> "Unknown"
    })
}
