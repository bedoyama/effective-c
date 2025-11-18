#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 17;
	int b = 5;
	
	printf("a = %d, b = %d\n\n", a, b);
	
	printf("Addition (a + b): %d\n", a + b);
	printf("Subtraction (a - b): %d\n", a - b);
	printf("Multiplication (a * b): %d\n", a * b);
	printf("Division (a / b): %d\n", a / b);
	printf("Modulo (a %% b): %d\n\n", a % b);
	
	// Floating point division
	double x = 17.0;
	double y = 5.0;
	printf("Floating point division: %.2f / %.2f = %.2f\n", x, y, x / y);
	
	// Unary operators
	printf("\nUnary plus (+a): %d\n", +a);
	printf("Unary minus (-a): %d\n", -a);
	
	return EXIT_SUCCESS;
}
