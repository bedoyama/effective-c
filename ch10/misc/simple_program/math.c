/*
 * Simple Calculator - math.c
 *
 * Implementation of calculator math operations.
 */

#include "math.h"

// Basic arithmetic
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b, int *error)
{
    if (b == 0)
    {
        *error = 1;
        return 0;
    }
    *error = 0;
    return a / b;
}

// Helper function (private to this file)
static int multiply_recursive(int a, int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return a;
    return a + multiply_recursive(a, n - 1);
}

// Advanced operations
int power(int base, int exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent < 0)
        return 0; // Simplified: only handle non-negative

    int result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result = multiply(result, base);
    }
    return result;
}

int factorial(int n)
{
    if (n < 0)
        return 0;
    if (n == 0 || n == 1)
        return 1;

    int result = 1;
    for (int i = 2; i <= n; i++)
    {
        result = multiply(result, i);
    }
    return result;
}
