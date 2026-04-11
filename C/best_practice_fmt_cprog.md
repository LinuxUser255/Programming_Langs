```c
/*
 * sum_until_zero.c
 *
 * Repeatedly prompts the user for integers, accumulates a running sum,
 * and terminates when the user enters 0.
 * Includes input validation via scanf return-value checking.
 */

#include <stdio.h>

int main(void) {
    /* TODO: Implement the program logic here. */

    printf("Hello, World!\n");
    return 0;
}
```

**What changed and why:**

**Block comment moved above `#include`** — in C, the file-level documentation header belongs at the very top of the file, before any includes. This is the standard convention in C projects (K&R style, Linux kernel style, MISRA C).

**Block comment reformatted** — the canonical C block comment style uses ` * ` aligned on each line with the opening `/*` on its own line and ` */` closing on its own line. Your original used inconsistent indentation inside the block.

**Added filename to the header** — `sum_until_zero.c` (or whatever you name it) belongs in the file header so the file is self-identifying when viewed in isolation, printed, or diffed.

**`//TODO` converted to `/* TODO */`** — `//` single-line comments are valid in C99 and later, but `/* */` is the traditional C style and works in all standards including C89. For a TODO marker inside a function body, a single-line block comment is the conventional form. Also removed the extra blank lines around it — two blank lines inside a short function body is excessive.

**Trailing blank line inside `main` removed** — the extra blank lines between the TODO and `printf` served no purpose and are noise.
