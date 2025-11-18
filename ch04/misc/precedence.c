#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 10, b = 5, c = 2;
	
	printf("a = %d, b = %d, c = %d\n\n", a, b, c);
	
	// Multiplication has higher precedence than addition
	int result1 = a + b * c;
	printf("a + b * c = %d (not %d)\n", result1, (a + b) * c);
	
	// Use parentheses to override precedence
	int result2 = (a + b) * c;
	printf("(a + b) * c = %d\n\n", result2);
	
	// Mixed operators
	int result3 = a + b / c - 1;
	printf("a + b / c - 1 = %d\n", result3);
	printf("Evaluated as: %d + (%d / %d) - 1\n\n", a, b, c);
	
	// Associativity: left-to-right for same precedence
	int result4 = a - b - c;
	printf("a - b - c = %d (left-to-right)\n", result4);
	printf("Evaluated as: (%d - %d) - %d = %d\n\n", a, b, c, result4);
	
	// Right-to-left associativity for assignment
	int x, y, z;
	x = y = z = 5;
	printf("x = y = z = 5: x = %d, y = %d, z = %d\n", x, y, z);
	
	return EXIT_SUCCESS;
}
