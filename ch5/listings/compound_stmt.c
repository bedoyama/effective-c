#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Compound Statements (Blocks) ===\n\n");

    // Simple compound statement
    printf("Simple compound statement:\n");
    {
        int x = 10;
        int y = 20;
        printf("Inside block: x = %d, y = %d\n", x, y);
        printf("Sum = %d\n", x + y);
    }
    // x and y are out of scope here
    printf("Outside block: x and y are no longer accessible\n\n");

    // Nested compound statements
    printf("Nested compound statements:\n");
    {
        int outer = 1;
        printf("Outer block: outer = %d\n", outer);

        {
            int inner = 2;
            printf("Inner block: outer = %d, inner = %d\n", outer, inner);

            {
                int innermost = 3;
                printf("Innermost: outer = %d, inner = %d, innermost = %d\n",
                       outer, inner, innermost);
            }
            // innermost is out of scope
        }
        // inner is out of scope
        printf("Back to outer block: outer = %d\n", outer);
    }
    printf("\n");

    // Variable shadowing
    printf("Variable shadowing:\n");
    int value = 100;
    printf("Outer value = %d\n", value);
    {
        int value = 200; // Shadows outer value
        printf("Inner value = %d (shadows outer)\n", value);
        {
            int value = 300; // Shadows both
            printf("Innermost value = %d (shadows both)\n", value);
        }
        printf("Back to inner value = %d\n", value);
    }
    printf("Back to outer value = %d\n\n", value);

    // Compound statement after control structure
    printf("Compound statement after if:\n");
    int score = 85;
    if (score >= 80)
    {
        printf("Great job!\n");
        printf("You passed with a high score.\n");
        int bonus = 10;
        printf("Bonus points: %d\n", bonus);
    }

    return EXIT_SUCCESS;
}
