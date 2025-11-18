#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
	printf("=== Integer Overflow ===\n\n");
	
	// Unsigned overflow (well-defined, wraps around)
	printf("Unsigned overflow (wraps around):\n");
	unsigned int u_max = UINT_MAX;
	printf("UINT_MAX = %u\n", u_max);
	printf("UINT_MAX + 1 = %u (wraps to 0)\n", u_max + 1);
	printf("UINT_MAX + 2 = %u\n\n", u_max + 2);
	
	unsigned char byte = 255;
	printf("unsigned char = 255\n");
	printf("255 + 1 = %u (wraps to 0)\n", byte + 1);
	printf("255 + 10 = %u (wraps to 9)\n\n", byte + 10);
	
	// Signed overflow (undefined behavior!)
	printf("Signed overflow (UNDEFINED BEHAVIOR!):\n");
	printf("WARNING: The following demonstrates undefined behavior\n");
	printf("INT_MAX = %d\n", INT_MAX);
	// Don't actually demonstrate signed overflow as it's UB
	printf("INT_MAX + 1 would cause undefined behavior\n\n");
	
	// Underflow
	printf("Unsigned underflow (wraps around):\n");
	unsigned int u_zero = 0;
	printf("0 - 1 = %u (wraps to UINT_MAX)\n", u_zero - 1);
	printf("0 - 10 = %u\n\n", u_zero - 10);
	
	// Multiplication overflow
	printf("Multiplication overflow:\n");
	unsigned char a = 200;
	unsigned char b = 200;
	printf("200 * 200 as unsigned char result:\n");
	unsigned char result = a * b;
	printf("Result (wrapped): %u\n", result);
	printf("Actual value: %u (truncated to 8 bits)\n", a * b);
	
	return EXIT_SUCCESS;
}
