package main

import "fmt"

// Basic example of an arrary in Go
func main() {
	// Declare an array of integers
	var numbers [5]int

	// Initialize the array elements
	numbers[0] = 10
	numbers[1] = 20
	numbers[2] = 30
	numbers[3] = 40
	numbers[4] = 50

	// Print the array elements
	fmt.Println(numbers)

	// Accessing array elements
	fmt.Println(numbers[0]) // Output: 10
	fmt.Println(numbers[4]) // Output: 50

	// Modifying array elements
	numbers[1] = 25
	fmt.Println(numbers[1]) // Output: 25

	// Length of an array
	fmt.Println(len(numbers)) // Output: 5
}
