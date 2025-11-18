#include <stdio.h>
#include <stdlib.h>

void print_binary(unsigned int n) {
	for (int i = 31; i >= 0; i--) {
		printf("%d", (n >> i) & 1);
		if (i % 4 == 0) printf(" ");
	}
	printf("\n");
}

int main() {
	unsigned int a = 60;  // 0011 1100
	unsigned int b = 13;  // 0000 1101
	
	printf("=== Basic Bitwise Operations ===\n\n");
	printf("a = %u (binary: ", a);
	print_binary(a);
	printf("b = %u (binary: ", b);
	print_binary(b);
	printf("\n");
	
	printf("a & b (AND):  %u (binary: ", a & b);
	print_binary(a & b);
	
	printf("a | b (OR):   %u (binary: ", a | b);
	print_binary(a | b);
	
	printf("a ^ b (XOR):  %u (binary: ", a ^ b);
	print_binary(a ^ b);
	
	printf("~a (NOT):     %u (binary: ", ~a);
	print_binary(~a);
	
	printf("~b (NOT):     %u (binary: ", ~b);
	print_binary(~b);
	
	// Practical examples
	printf("\n=== Practical Uses ===\n\n");
	
	// Setting a bit
	unsigned int flags = 0;
	printf("flags = %u\n", flags);
	flags |= (1 << 3);  // Set bit 3
	printf("After setting bit 3: flags = %u\n", flags);
	
	// Clearing a bit
	flags &= ~(1 << 3);  // Clear bit 3
	printf("After clearing bit 3: flags = %u\n\n", flags);
	
	// Toggling a bit
	flags = 5;  // Binary: 0101
	printf("flags = %u (binary: 0101)\n", flags);
	flags ^= (1 << 0);  // Toggle bit 0
	printf("After toggling bit 0: flags = %u (binary: 0100)\n", flags);
	
	// Testing a bit
	unsigned int mask = 0x08;  // Bit 3
	unsigned int value = 0x0F; // Binary: 1111
	printf("\nTesting if bit 3 is set in 0x%02X: %s\n", 
	       value, (value & mask) ? "YES" : "NO");
	
	return EXIT_SUCCESS;
}
