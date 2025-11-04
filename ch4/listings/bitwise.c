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
	
	printf("a << 2 (left shift):  %u (binary: ", a << 2);
	print_binary(a << 2);
	
	printf("a >> 2 (right shift): %u (binary: ", a >> 2);
	print_binary(a >> 2);
	
	return EXIT_SUCCESS;
}
