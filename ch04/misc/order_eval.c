#include <stdio.h>
#include <stdlib.h>

int get_value(int val) {
	printf("get_value(%d) called\n", val);
	return val;
}

int main() {
	int a = 5;
	
	// Undefined behavior: modifying and reading same variable
	// int result = a++ + a++;  // UNDEFINED BEHAVIOR!
	
	// Well-defined: sequence points guarantee order
	printf("=== Safe evaluation ===\n");
	int b = a++;
	int c = a++;
	int result = b + c;
	printf("Result: %d + %d = %d\n\n", b, c, result);
	
	// Function arguments: order of evaluation is unspecified
	printf("=== Function call evaluation order ===\n");
	printf("Values: %d, %d, %d\n", get_value(1), get_value(2), get_value(3));
	printf("(Order may vary)\n\n");
	
	// Sequence points: full expression, &&, ||, ?:, comma
	printf("=== Sequence points ===\n");
	int x = 0;
	x = (x = 3) + (x = 5);  // Still problematic
	printf("After complex assignment: x = %d\n", x);
	
	// Safe with sequence point
	int y = 0;
	y = 3;  // Sequence point at semicolon
	y = y + 5;
	printf("Safe version: y = %d\n", y);
	
	return EXIT_SUCCESS;
}
