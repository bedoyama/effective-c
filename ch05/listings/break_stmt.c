#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Break Statement ===\n\n");

    // Break in for loop
    printf("Break in for loop:\n");
    for (int i = 1; i <= 10; i++)
    {
        if (i == 5)
        {
            printf("Breaking at i = %d\n", i);
            break;
        }
        printf("i = %d\n", i);
    }
    printf("Loop exited\n\n");

    // Break in while loop
    printf("Break in while loop:\n");
    int count = 0;
    while (1)
    { // Infinite loop
        count++;
        printf("count = %d\n", count);
        if (count >= 3)
        {
            printf("Breaking out\n");
            break;
        }
    }
    printf("\n");

    // Break in switch
    printf("Break in switch:\n");
    int value = 2;
    switch (value)
    {
    case 1:
        printf("Case 1\n");
        break;
    case 2:
        printf("Case 2\n");
        break; // Prevents fall-through
    case 3:
        printf("Case 3\n");
        break;
    default:
        printf("Default\n");
    }
    printf("\n");

    // Break in nested loops (only exits innermost)
    printf("Break in nested loops:\n");
    for (int i = 1; i <= 3; i++)
    {
        printf("Outer loop: i = %d\n", i);
        for (int j = 1; j <= 3; j++)
        {
            if (j == 2)
            {
                printf("  Breaking inner loop at j = %d\n", j);
                break;
            }
            printf("  Inner loop: j = %d\n", j);
        }
    }
    printf("\n");

    // Finding element in array
    printf("Finding element in array:\n");
    int numbers[] = {10, 20, 30, 40, 50};
    int target = 30;
    int found_index = -1;

    for (int i = 0; i < 5; i++)
    {
        if (numbers[i] == target)
        {
            found_index = i;
            break; // Stop searching once found
        }
    }

    if (found_index != -1)
    {
        printf("Found %d at index %d\n", target, found_index);
    }

    return EXIT_SUCCESS;
}
