#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Continue Statement ===\n\n");

    // Continue in for loop
    printf("Continue in for loop (skip even numbers):\n");
    for (int i = 1; i <= 10; i++)
    {
        if (i % 2 == 0)
        {
            continue; // Skip rest of loop body
        }
        printf("Odd number: %d\n", i);
    }
    printf("\n");

    // Continue in while loop
    printf("Continue in while loop:\n");
    int count = 0;
    while (count < 5)
    {
        count++;
        if (count == 3)
        {
            printf("Skipping count = %d\n", count);
            continue;
        }
        printf("Processing count = %d\n", count);
    }
    printf("\n");

    // Continue in do-while
    printf("Continue in do-while:\n");
    int i = 0;
    do
    {
        i++;
        if (i == 2 || i == 4)
        {
            continue; // Skip printing
        }
        printf("i = %d\n", i);
    } while (i < 5);
    printf("\n");

    // Continue vs break
    printf("Continue vs break:\n");
    printf("With continue (skips 3):\n");
    for (int j = 1; j <= 5; j++)
    {
        if (j == 3)
            continue;
        printf("%d ", j);
    }
    printf("\n");

    printf("With break (stops at 3):\n");
    for (int j = 1; j <= 5; j++)
    {
        if (j == 3)
            break;
        printf("%d ", j);
    }
    printf("\n\n");

    // Processing array, skipping invalid values
    printf("Processing array, skipping negative values:\n");
    int values[] = {10, -5, 20, -3, 30, 40, -1, 50};
    int sum = 0;
    int valid_count = 0;

    for (int k = 0; k < 8; k++)
    {
        if (values[k] < 0)
        {
            printf("Skipping negative value: %d\n", values[k]);
            continue;
        }
        sum += values[k];
        valid_count++;
    }
    printf("Sum of positive values: %d\n", sum);
    printf("Count of positive values: %d\n", valid_count);

    return EXIT_SUCCESS;
}
