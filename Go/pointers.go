// Example of a pointer in Go
package main

import "fmt"

func main() {
	// Declare a variable and assign a value, and print its address
	var number int = 10
	fmt.Printf("Number: %d, Address: %p\n", number, &number)

	// Declare a pointer to an integer, and assign the address of the variable
	var ptr *int = &number
	fmt.Printf("Pointer: %p, Value: %d\n", ptr, *ptr)
	
  // Change the value through the pointer
	*ptr = 20
	fmt.Printf("Number after change: %d\n", number)
	
  // Dereference the pointer to get the original value
	fmt.Printf("Dereferenced pointer: %d\n", *ptr)
}
