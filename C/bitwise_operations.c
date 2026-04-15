// bitwise_operations.c
// Bitwise operations - flags, masks, and low-level control

#include <stdio.h>
#include <stdint.h>   // for fixed-width types

int main(void) {
    printf("=== Bitwise Operations ===\n\n");

    uint8_t flags = 0;        // 8-bit flags (C23 style)

    // Setting bits
    flags |= (1 << 0);        // Set bit 0 (value 1)
    flags |= (1 << 2);        // Set bit 2 (value 4)

    printf("Flags after setting bits 0 and 2: 0b%02b\n", flags);

    // Checking bits
    if (flags & (1 << 2)) {
        printf("Bit 2 is set!\n");
    }

    // Clearing a bit
    flags &= ~(1 << 0);       // Clear bit 0
    printf("After clearing bit 0: 0b%02b\n", flags);

    // Toggling a bit
    flags ^= (1 << 3);        // Toggle bit 3
    printf("After toggling bit 3: 0b%02b\n", flags);

    // Common bitmask example - permissions
    const uint8_t READ  = 1 << 0;  // 00000001
    const uint8_t WRITE = 1 << 1;  // 00000010
    const uint8_t EXEC  = 1 << 2;  // 00000100

    uint8_t permissions = READ | WRITE;
    printf("Permissions (READ|WRITE): 0b%03b\n", permissions);

    if (permissions & WRITE) {
        printf("Write permission granted\n");
    }

    // Shift operators
    uint32_t value = 1;
    printf("1 << 3 = %u\n", value << 3);
    printf("8 >> 1 = %u\n", 8 >> 1);

    return 0;
}
