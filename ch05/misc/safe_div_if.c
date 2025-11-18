#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Safe division function that handles edge cases
bool safediv(int dividend, int divisor, int *quotient)
{
    if (!quotient)
        return false; // Check for NULL pointer
    if ((divisor == 0) || ((dividend == INT_MIN) && (divisor == -1)))
        return false; // Prevent division by zero and overflow
    *quotient = dividend / divisor;
    return true;
}

int main()
{
    printf("=== Safe Division Function ===\n\n");

    // Test case 1: Normal division
    printf("Test 1: Normal division\n");
    int result;
    if (safediv(10, 2, &result))
    {
        printf("10 / 2 = %d\n", result);
    }
    else
    {
        printf("Division failed\n");
    }
    printf("\n");

    // Test case 2: Division by zero
    printf("Test 2: Division by zero\n");
    if (safediv(10, 0, &result))
    {
        printf("10 / 0 = %d\n", result);
    }
    else
    {
        printf("Division failed: Cannot divide by zero\n");
    }
    printf("\n");

    // Test case 3: NULL pointer
    printf("Test 3: NULL pointer\n");
    if (safediv(10, 2, NULL))
    {
        printf("Division succeeded\n");
    }
    else
    {
        printf("Division failed: NULL quotient pointer\n");
    }
    printf("\n");

    // Test case 4: Overflow case (INT_MIN / -1)
    printf("Test 4: Overflow case (INT_MIN / -1)\n");
    printf("INT_MIN = %d\n", INT_MIN);
    if (safediv(INT_MIN, -1, &result))
    {
        printf("INT_MIN / -1 = %d\n", result);
    }
    else
    {
        printf("Division failed: Would cause overflow\n");
        printf("Explanation: INT_MIN / -1 would be %d + 1, which overflows\n", INT_MAX);
    }
    printf("\n");

    // Test case 5: Negative numbers
    printf("Test 5: Negative numbers\n");
    if (safediv(-20, 4, &result))
    {
        printf("-20 / 4 = %d\n", result);
    }
    else
    {
        printf("Division failed\n");
    }
    if (safediv(20, -4, &result))
    {
        printf("20 / -4 = %d\n", result);
    }
    else
    {
        printf("Division failed\n");
    }
    if (safediv(-20, -4, &result))
    {
        printf("-20 / -4 = %d\n", result);
    }
    else
    {
        printf("Division failed\n");
    }
    printf("\n");

    // Test case 6: Integer truncation
    printf("Test 6: Integer truncation\n");
    if (safediv(7, 2, &result))
    {
        printf("7 / 2 = %d (truncated, not rounded)\n", result);
    }
    else
    {
        printf("Division failed\n");
    }
    if (safediv(7, 3, &result))
    {
        printf("7 / 3 = %d (remainder lost)\n", result);
    }
    else
    {
        printf("Division failed\n");
    }
    printf("\n");

    // Test case 7: Using in a loop
    printf("Test 7: Processing array of divisions\n");
    int dividends[] = {100, 50, 25, 10, 5};
    int divisors[] = {10, 0, 5, -2, 0};

    for (int i = 0; i < 5; i++)
    {
        if (safediv(dividends[i], divisors[i], &result))
        {
            printf("%d / %d = %d\n", dividends[i], divisors[i], result);
        }
        else
        {
            printf("%d / %d = ERROR (division failed)\n", dividends[i], divisors[i]);
        }
    }
    printf("\n");

    // Test case 8: Checking return value vs result
    printf("Test 8: Demonstrating return value importance\n");
    int quotient;
    bool success;

    quotient = 999; // Initialize with sentinel value
    success = safediv(20, 0, &quotient);
    printf("Division 20 / 0:\n");
    printf("  Success: %s\n", success ? "true" : "false");
    printf("  Quotient: %d (unchanged because division failed)\n\n", quotient);

    quotient = 999; // Initialize with sentinel value
    success = safediv(20, 4, &quotient);
    printf("Division 20 / 4:\n");
    printf("  Success: %s\n", success ? "true" : "false");
    printf("  Quotient: %d (updated by successful division)\n", quotient);

    return EXIT_SUCCESS;
}
