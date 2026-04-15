# Multi-File Programs and Build Systems in C

So far you've been writing single-file programs. Real C projects are almost always split across multiple files for better organization, reusability, and maintainability.

## Why Split into Multiple Files?

- **Modularity** — Group related functions together
- **Reusability** — Share code between programs
- **Compilation speed** — Only recompile changed files
- **Teamwork** — Multiple people can work on different files

## The Three Main Pieces

1. **Header files** (`.h`) — Declarations (what the functions look like)
2. **Source files** (`.c`) — Definitions (the actual code)
3. **Main program** — Ties everything together

## Header Guards (Critical!)

```c
#ifndef UTILS_H
#define UTILS_H
// ... declarations ...
#endif // UTILS_H
```

## How to build Multi-File Programs


```bash
gcc -std=c23 -Wall -Wextra -Wpedantic main.c utils.c -o myprogram
```

## Better way, use a Makefile
```bash
# Simple Makefile for our multi-file project

CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -g

all: myprogram

myprogram: main.o utils.o
	$(CC) $(CFLAGS) main.o utils.o -o myprogram

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o myprogram

.PHONY: all clean
```

## To build
```bash
cd multi_file_example
make
./myprogram
```

## To clean
```bash
make clean
```
