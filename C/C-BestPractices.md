## C-programming Best Practices 2026

**C23** is the current standard — officially ISO/IEC 9899:2024, published February 2024. GCC 15 now uses C23 as its default mode, selectable explicitly with `-std=c23`.

For most projects right now the practical recommendation is:

| Situation | Use |
|---|---|
| New project, GCC 15+ / Clang 18+ | **C23** |
| Need broad compiler compatibility | **C17** (safe, widely supported) |
| Embedded / legacy systems | **C11** (minimum modern baseline) |
| Never use | C99 or older for new code |

---

## What C23 gives you — the practical additions

**`bool`, `true`, `false` are now keywords** — no more `#include <stdbool.h>`:
```c
// C17 — needed the header
#include <stdbool.h>
bool done = false;

// C23 — builtins, no include needed
bool done = false;
```

**`nullptr` instead of `NULL`** — type-safe null pointer, avoids ambiguities in pointer comparisons that `NULL` (defined as `0` or `((void*)0)`) had.
```c
int *ptr = nullptr;    // C23 — type safe
int *ptr = NULL;       // C17 — macro, can cause subtle type issues
```

**Binary literals and digit separators:**
```c
// C23
int mask  = 0b11001010;
int big   = 1'000'000;    // apostrophe as separator, easier to read
```

**`typeof` operator:**
```c
int x = 42;
typeof(x) y = 100;    // y is deduced as int — similar to C++ auto
```

**`auto` for type inference** (C23 only, object definitions):
```c
auto x = 42;        // deduced as int
auto y = 3.14;      // deduced as double
```

**Zero initialization with `{}`:**
```c
int arr[10] = {};       // all zeros — cleaner than = {0}
struct Point p = {};    // all fields zeroed
```

**Checked integer arithmetic** — catches overflow silently killing programs:
```c
#include <stdckdint.h>

int result;
if (ckd_add(&result, a, b)) {
    // overflow occurred — handle it
}
```

---

## Compile flags in 2026

```bash
# C23 — current standard
gcc -std=c23 -Wall -Wextra -Wpedantic -g file.c -o file

# C17 — if you need wider compatibility
gcc -std=c17 -Wall -Wextra -Wpedantic -g file.c -o file
```

`-Wall -Wextra -Wpedantic` together catch the most issues. Never skip `-Wall` on new code.

---

## Best practices that haven't changed

```c
// 1. Always void in main signature
int main(void) { }

// 2. Declare variables close to where they're used (C99+)
for (int i = 0; i < n; i++) { }    // not at top of function

// 3. Use stdint.h types when size matters
#include <stdint.h>
uint32_t flags = 0;     // explicit 32-bit, not "unsigned int"
int64_t  count = 0;     // explicit 64-bit, not "long"

// 4. const everything that shouldn't change
const char *name = "Alice";
void print_array(const int *arr, size_t len);

// 5. Check return values — always
FILE *f = fopen("file.txt", "r");
if (f == NULL) {
    perror("fopen");
    return 1;
}

// 6. Prefer isspace(), isdigit() etc. over manual char checks
#include <ctype.h>
if (isspace(c)) { }     // not: c == ' ' || c == '\t' || c == '\n'

// 7. Use size_t for sizes and counts
size_t len = strlen(str);
for (size_t i = 0; i < len; i++) { }
```

The word counter from your earlier question updated to C23 would look like:

```c
#include <stdio.h>
#include <ctype.h>       // isspace()

int main(void) {
    int c;
    int nl = 0, nw = 0, nc = 0;
    bool in_word = false;    // bool is now a keyword in C23, no include needed

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') ++nl;
        if (isspace(c))      in_word = false;
        else if (!in_word) { in_word = true; ++nw; }
    }

    printf("lines: %d  words: %d  chars: %d\n", nl, nw, nc);
    return 0;
}
```

```bash
gcc -std=c23 -Wall -Wextra file.c -o wc
```
