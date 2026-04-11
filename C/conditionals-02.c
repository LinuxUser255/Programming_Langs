#include <stdio.h>

int main(void) {
    int score;
    printf("Enter your test score (0-100): ");

    /* Read the user's input and check if it's a valid integer. */
    if (scanf("%d", &score) != 1) {
        printf("Invalid input. Please enter a number between 0 and 100.\n");
        return 1;
    }

    /* Check if the score is within the valid range. */
    if (score < 0 || score > 100) {
        printf("Invalid input. Please enter a number between 0 and 100.\n");
        return 1;
    }

    /* Main grade logic. */
    char grade;
    if (score >= 90) {
        grade = 'A';
    } else if (score >= 80) {
        grade = 'B';
    } else if (score >= 70) {
        grade = 'C';
    } else if (score >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }

    /* Check if the score is 100 */
    if (score == 100) {
        printf("Congratulations! You got a perfect score of 100.\n");
    }
    else if (score < 60) {
        printf("Don't give up! Keep going.\n");
    }

    /* Print the letter score. */
    printf("Your letter score is: %c\n", grade);

    return 0;
}
