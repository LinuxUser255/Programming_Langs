// Example of a struct in Go
package main

import "fmt"

type Person struct {
	Name string
	Age  int
}

func main() {
	// Create a new person object
	person := Person{Name: "John Doe", Age: 30}

	// Print the person's name and age
	fmt.Printf("Name: %s, Age: %d\n", person.Name, person.Age)
}
