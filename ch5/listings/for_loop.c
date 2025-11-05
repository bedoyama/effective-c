#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== For Loop ===\n\n");

    // Basic for loop
    printf("Basic for loop:\n");
    for (int i = 1; i <= 5; i++)
    {
        printf("i = %d\n", i);
    }
    printf("\n");

    // Counting backwards
    printf("Counting backwards:\n");
    for (int i = 5; i >= 1; i--)
    {
        printf("i = %d\n", i);
    }
    printf("\n");

    // Different increments
    printf("Increment by 2:\n");
    for (int i = 0; i < 10; i += 2)
    {
        printf("i = %d\n", i);
    }
    printf("\n");

    // Multiple variables
    printf("Multiple variables:\n");
    for (int i = 0, j = 10; i < 5; i++, j--)
    {
        printf("i = %d, j = %d\n", i, j);
    }
    printf("\n");

    // Nested for loops
    printf("Nested for loops (multiplication table):\n");
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            printf("%d x %d = %2d  ", i, j, i * j);
        }
        printf("\n");
    }
    printf("\n");

    // Empty parts (infinite loop)
    printf("For loop with empty parts:\n");
    int count = 0;
    for (;;)
    { // Infinite loop
        printf("Iteration %d\n", count);
        count++;
        if (count >= 3)
        {
            break;
        }
    }
    printf("\n");

    // Complex conditions
    printf("Complex condition:\n");
    for (int i = 0; i < 20 && i * i < 50; i++)
    {
        printf("i = %d, i² = %d\n", i, i * i);
    }

    return EXIT_SUCCESS;
}
