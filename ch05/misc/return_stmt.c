#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Return Statement ===\n\n");

    // Early return pattern
    printf("Early return prevents unnecessary processing\n");

    // Simulating function with main
    int value = 0;
    printf("Checking value: %d\n", value);
    if (value == 0)
    {
        printf("Value is zero, returning early\n");
        return EXIT_SUCCESS; // Early return
    }

    // This code won't execute because of early return
    printf("This won't print\n");
    printf("Processing continues...\n");

    return EXIT_SUCCESS;
}

// Additional demonstration functions
void process_data(int *data, int size)
{
    if (data == NULL || size <= 0)
    {
        printf("Invalid input, returning early\n");
        return; // Early return from void function
    }

    printf("Processing data...\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int find_max(int *array, int size)
{
    if (array == NULL || size <= 0)
    {
        printf("Invalid array\n");
        return -1; // Error code
    }

    int max = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    return max; // Return computed value
}

int divide(int a, int b)
{
    if (b == 0)
    {
        printf("Division by zero!\n");
        return 0; // Error handling with return
    }

    return a / b;
}
