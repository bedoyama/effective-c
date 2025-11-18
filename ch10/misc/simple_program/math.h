/*
 * Simple Calculator - math.h
 * 
 * Public interface for calculator math operations.
 * Demonstrates proper header structure for a component.
 */

#ifndef CALC_MATH_H
#define CALC_MATH_H

// Mathematical operations
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b, int *error);  // Returns 0 and sets error on division by zero

// Advanced operations
int power(int base, int exponent);
int factorial(int n);

#endif /* CALC_MATH_H */
