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
	printf("=== Signed Number Bit Operations ===\n\n");
	printf("WARNING: Left shift of negative numbers is UNDEFINED BEHAVIOR!\n\n");
	
	// Signed negative number shifts
	signed char neg = -16;  // Binary: 11110000 (in two's complement)
	printf("Signed char neg = %d (0x%02X)\n", neg, (unsigned char)neg);
	printf("Binary representation: ");
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((unsigned char)neg >> i) & 1);
	}
	printf("\n\n");
	
	// Right shift on signed (arithmetic shift - sign extension)
	printf("Right shift (arithmetic - preserves sign):\n");
	printf("neg >> 1 = %d (0x%02X) - sign bit extended\n", neg >> 1, (unsigned char)(neg >> 1));
	printf("neg >> 2 = %d (0x%02X) - sign bit extended\n", neg >> 2, (unsigned char)(neg >> 2));
	printf("neg >> 3 = %d (0x%02X) - sign bit extended\n", neg >> 3, (unsigned char)(neg >> 3));
	printf("neg >> 4 = %d (0x%02X) - sign bit extended\n\n", neg >> 4, (unsigned char)(neg >> 4));
	
	// Unsigned vs signed right shift
	signed char signed_neg = -8;  // 11111000
	unsigned char unsigned_val = (unsigned char)signed_neg;
	
	printf("=== Comparison: Signed vs Unsigned Right Shift ===\n");
	printf("signed_neg = %d (0x%02X, binary: 11111000)\n", signed_neg, (unsigned char)signed_neg);
	printf("signed_neg >> 2 = %d (sign extended, fills with 1s)\n", signed_neg >> 2);
	printf("  Result binary: ");
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((unsigned char)(signed_neg >> 2) >> i) & 1);
	}
	printf("\n\n");
	
	printf("unsigned_val = %u (0x%02X, binary: 11111000)\n", unsigned_val, unsigned_val);
	printf("unsigned_val >> 2 = %u (logical shift, fills with 0s)\n", unsigned_val >> 2);
	printf("  Result binary: ");
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((unsigned_val >> 2) >> i) & 1);
	}
	printf("\n\n");
	
	// Large value truncation
	printf("=== Truncation with Large Values ===\n");
	int large = 0x80000000;  // High bit set
	printf("large = 0x%08X %d (binary: ", large, large);
	print_binary(large);
	printf("large << 1 = 0x%08X %d (high bit truncated)\n\n", large << 1, large << 1);
	
	int val = 0xFFFFFFFF;  // All bits set
	printf("val = 0x%08X %d (all bits set)\n", val, val);
	printf("val << 4 = 0x%08X %d (4 high bits truncated)\n", val << 4, val << 4);
	printf("val >> 4 = 0x%08X %d (4 low bits truncated)\n", val >> 4, val >> 4);

	return EXIT_SUCCESS;
}
