#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 10;
	int b = 20;
	
	// Ternary operator: condition ? true_value : false_value
	int max = (a > b) ? a : b;
	printf("Maximum of %d and %d is: %d\n", a, b, max);
	
	int min = (a < b) ? a : b;
	printf("Minimum of %d and %d is: %d\n\n", a, b, min);
	
	// Nested conditional operators
	int x = 5;
	char *result = (x > 0) ? "positive" : (x < 0) ? "negative" : "zero";
	printf("x = %d is %s\n\n", x, result);
	
	// Using conditional in assignment
	int age = 17;
	char *status = (age >= 18) ? "adult" : "minor";
	printf("Age %d: %s\n", age, status);
	
	// Conditional operator for absolute value
	int n = -42;
	int abs_n = (n < 0) ? -n : n;
	printf("Absolute value of %d is %d\n", n, abs_n);
	
	return EXIT_SUCCESS;
}
