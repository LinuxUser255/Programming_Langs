/*
 * whileloop-01.c
 *
 * Repeatedly prompts the user for integers, accumulates a running sum,
 * and terminates when the user enters 0.
 * Includes input validation via scanf return-value checking.
 */

#include <stdio.h>

int main(void) {
    int number;
    int total = 0;

    printf("Enter integers to be summed.\n ");
    printf("Enter 0 to stop.\n\n ");

    while (1) {
        printf("Enter a number: ");

        // Check that input is a valid integer
        if (scanf("%d", &number) != 1) {
            printf("Invalid input. Please enter a number.\n");

            // Clear the bad input buffer - avoid infinite loop
            while (getchar() != '\n');
            continue;
        }

        // If user enters 0, break the loop
        if (number == 0) {
            break;
        }

        // Update the running sum
        total += number;

        printf("Total so far: %d\n\n", total);
    }

    // Display the final total when loop ends
    printf("Final total: %d\n", total);

    return 0;
}
