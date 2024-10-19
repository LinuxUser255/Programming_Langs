// Basic example of a conditional statement in Go
package main

import "fmt"

func main() {
	// Declare a variable
	var number int = 10

	// Conditional statement
	if number > 5 {
		fmt.Println("Number is greater than 5")
	} else if number < 5 {
		fmt.Println("Number is less than 5")
	} else {
		fmt.Println("Number is equal to 5")
	}
}
