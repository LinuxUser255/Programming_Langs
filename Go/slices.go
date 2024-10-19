package main

// Basic example of Slices in Go
import "fmt"

func main() {
	// Declare a slice of integers
	var numbers []int

	// Initialize the slice with some elements
	numbers = append(numbers, 10, 20, 30)

	// Print the slice elements
	fmt.Println(numbers)

	// Accessing slice elements
	fmt.Println(numbers[0]) // Output: 10
	fmt.Println(numbers[2]) // Output: 30

	// Modifying slice elements
	numbers[1] = 25
	fmt.Println(numbers[1]) // Output: 25

	// Length of a slice
	fmt.Println(len(numbers)) // Output: 3

	// Append new elements to the slice
	numbers = append(numbers, 40, 50)
	fmt.Println(numbers) // Output: [10 25 30 40 50]

	// Remove elements from the slice
	numbers = append(numbers[:2], numbers[3:]...)
	fmt.Println(numbers) // Output: [10 25 40]

	// Create a new slice from a slice
	newNumbers := make([]int, len(numbers))
	copy(newNumbers, numbers)
	fmt.Println(newNumbers) // Output: [10 25 40]
}
