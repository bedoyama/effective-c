#include <stdio.h>
#include <stdlib.h>

int main() {
	int a, b, c;
	
	// Comma operator: evaluates left to right, returns rightmost value
	a = (b = 3, c = 5, b + c);
	printf("After a = (b = 3, c = 5, b + c):\n");
	printf("a = %d, b = %d, c = %d\n\n", a, b, c);
	
	// Common use in for loops
	int i, j;
	printf("For loop with comma operator:\n");
	for (i = 0, j = 10; i < 5; i++, j--) {
		printf("i = %d, j = %d\n", i, j);
	}
	
	// Multiple expressions
	int x = 1, y = 2, z = 3;
	printf("\nMultiple assignments: x = %d, y = %d, z = %d\n", x, y, z);
	
	// Result of comma expression
	int result = (x++, y++, z++);
	printf("Result of (x++, y++, z++): %d\n", result);
	printf("After: x = %d, y = %d, z = %d\n", x, y, z);
	
	return EXIT_SUCCESS;
}
