# Array Operations in C - Pseudo Code

This document presents a pseudo code version of the `arrary.c` file, along with explanations for each section.

## Pseudo Code

```c
FUNCTION main:
    // Array Declaration
    DECLARE integer array my_array with size 5
    DECLARE and INITIALIZE integer array my_array_b with values [1, 2, 3, 4, 5]
```
```c
// Calculate Array Length
SET length TO size of my_array DIVIDED BY size of one element of my_array

// Populate Array
FOR each index i FROM 0 TO length - 1:
    SET my_array[i] TO i

// Access and Print Array Element
PRINT the value at index 2 of my_array

RETURN 0
```

## Explanation

1. **Array Declaration**
   - We declare two arrays:
     - `my_array`: An uninitialized integer array with a size of 5.
     - `my_array_b`: An initialized integer array with values [1, 2, 3, 4, 5].
   - This demonstrates two ways to create arrays in C.

2. **Calculate Array Length**
   - We calculate the length of `my_array` by dividing its total size by the size of one element.
   - This is a common technique in C to determine the number of elements in an array.

3. **Populate Array**
   - We use a loop to assign values to `my_array`.
   - The loop runs from 0 to `length - 1`, covering all indices of the array.
   - Each element is set to its own index value (i.e., `my_array[0] = 0`, `my_array[1] = 1`, etc.).

4. **Access and Print Array Element**
   - We access the element at index 2 of `my_array` and print its value.
   - This demonstrates how to access individual elements of an array using their index.

5. **Function Return**
   - The function returns 0, indicating successful execution.
   - This is a convention in C programs to signify that the program ran without errors.

## Key Concepts

- Array declaration and initialization
- Calculating array length
- Iterating over array elements
- Accessing array elements by index
- Basic program structure in C

This pseudo code and explanation provide an overview of fundamental array operations in C, showcasing declaration, initialization, population, and access of array elements.
