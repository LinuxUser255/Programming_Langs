// enums_typedefs_unions.c
// Enums, typedefs, and unions - making code more readable and powerful

#include <stdio.h>

// 1. Enum - named integer constants
enum Color {
    RED,      // 0
    GREEN,    // 1
    BLUE,     // 2
    YELLOW    // 3
};

// C23 allows you to specify the underlying type
enum Status : int {
    SUCCESS = 0,
    ERROR = -1,
    WARNING = 1
};

// 2. Typedef - create new type names (huge for readability)
typedef unsigned long size_t;   // (already in stddef.h, but example)

// Better: typedef for structs (common pattern)
typedef struct {
    char name[50];
    int age;
    enum Color favorite_color;
} Person;

// 3. Union - all members share the same memory (size = largest member)
typedef union {
    int i;          // 4 bytes
    float f;        // 4 bytes
    char str[20];   // 20 bytes
} Data;

int main(void) {
    printf("=== Enums, Typedefs & Unions ===\n\n");

    // Enum usage
    enum Color shirt = BLUE;
    printf("My shirt color is %d (BLUE)\n", shirt);

    // Typedef struct
    Person p = {"Alice", 28, GREEN};
    printf("Person: %s, age %d, favorite color %d\n", p.name, p.age, p.favorite_color);

    // Union demonstration
    Data d;
    d.i = 42;
    printf("Union as int: %d\n", d.i);

    d.f = 3.14f;
    printf("Union as float: %.2f\n", d.f);

    // Warning: only one member is valid at a time
    printf("Size of union Data: %zu bytes\n", sizeof(d));

    return 0;
}
