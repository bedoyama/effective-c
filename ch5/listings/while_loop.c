#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== While Loop ===\n\n");

    // Basic while loop
    printf("Basic while loop:\n");
    int count = 1;
    while (count <= 5)
    {
        printf("Count: %d\n", count);
        count++;
    }
    printf("\n");

    // While loop with condition that's initially false
    printf("While loop that never executes:\n");
    int i = 10;
    while (i < 5)
    {
        printf("This will never print\n");
        i++;
    }
    printf("Loop condition was false from the start\n\n");

    // While loop for input validation
    printf("While loop for processing:\n");
    int sum = 0;
    int n = 1;
    while (n <= 10)
    {
        sum += n;
        n++;
    }
    printf("Sum of 1 to 10: %d\n\n", sum);

    // Infinite while loop with break
    printf("Infinite while with break:\n");
    int counter = 0;
    while (1)
    { // Infinite loop
        printf("Iteration %d\n", counter);
        counter++;
        if (counter >= 3)
        {
            printf("Breaking out of loop\n");
            break;
        }
    }
    printf("\n");

    // While loop with continue
    printf("While loop with continue:\n");
    int num = 0;
    while (num < 5)
    {
        num++;
        if (num == 3)
        {
            printf("Skipping %d\n", num);
            continue;
        }
        printf("Processing %d\n", num);
    }

    return EXIT_SUCCESS;
}
