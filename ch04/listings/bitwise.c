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
	
	// Bit truncation examples
	printf("\n=== Shift Truncation Examples ===\n");
	printf("NOTE: Bits are TRUNCATED (lost), not wrapped around!\n\n");
	
	unsigned char byte = 0xFF;  // 11111111
	printf("Original byte: 0x%02X %d (binary: ", byte, byte);
	for (int i = 7; i >= 0; i--) {
		printf("%d", (byte >> i) & 1);
	}
	printf(")\n");
	
	printf("Left shift by 1:  0x%02X %d (binary: ", byte << 1, byte << 1);
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((byte << 1) >> i) & 1);
	}
	printf(") - high bit TRUNCATED!\n");
	
	printf("Left shift by 4:  0x%02X %d (binary: ", byte << 4, byte << 4);
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((byte << 4) >> i) & 1);
	}
	printf(") - 4 high bits TRUNCATED!\n");
	
	printf("Left shift by 8:  0x%02X %d (all bits truncated = 0)\n", byte << 8, byte << 8);
	
	// Right shift examples
	printf("\nRight shift by 1: 0x%02X %d (binary: ", byte >> 1, byte >> 1);
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((byte >> 1) >> i) & 1);
	}
	printf(")\n");
	
	printf("Right shift by 4: 0x%02X %d (binary: ", byte >> 4, byte >> 4);
	for (int i = 7; i >= 0; i--) {
		printf("%d", ((byte >> 4) >> i) & 1);
	}
	printf(")\n");
	
	printf("Right shift by 8: 0x%02X %d (all bits truncated)\n", byte >> 8, byte >> 8);
	
	// Demonstration that bits don't wrap
	printf("\n=== Proof: Bits Don't Wrap ===\n");
	unsigned char test = 0x81;  // 10000001
	printf("test = 0x%02X %d (binary: 10000001)\n", test, test);
	printf("test << 1 = 0x%02X %d (binary: 00000010)\n", test << 1, test << 1);
	printf("If bits wrapped, we'd see the high bit on the right. We don't!\n");
	
	// Overflow multiplication using shifts
	printf("\n=== Shift as Multiplication/Division ===\n");
	unsigned int num = 5;
	printf("num = %u\n", num);
	printf("num << 1 = %u (multiply by 2)\n", num << 1);
	printf("num << 2 = %u (multiply by 4)\n", num << 2);
	printf("num << 3 = %u (multiply by 8)\n", num << 3);
	
	num = 80;
	printf("\nnum = %u\n", num);
	printf("num >> 1 = %u (divide by 2)\n", num >> 1);
	printf("num >> 2 = %u (divide by 4)\n", num >> 2);
	printf("num >> 3 = %u (divide by 8)\n", num >> 3);
	
	// Large shift causing truncation
	printf("\n=== Truncation with Large Values ===\n");
	unsigned int large = 0x80000000;  // High bit set
	printf("large = 0x%08X %u (binary: ", large, large);
	print_binary(large);
	printf("large << 1 = 0x%08X %u (high bit truncated, result is 0)\n", large << 1, large << 1);
	
	unsigned int val = 0xFFFFFFFF;  // All bits set
	printf("\nval = 0x%08X %u (all bits set)\n", val, val);
	printf("val << 4 = 0x%08X %u (4 high bits truncated)\n", val << 4, val << 4);
	printf("val >> 4 = 0x%08X %u (4 low bits truncated)\n", val >> 4, val >> 4);
	
	// Signed negative number shifts
	printf("\n=== Signed Negative Number Shifts ===\n");
	printf("WARNING: Left shift of negative numbers is UNDEFINED BEHAVIOR!\n\n");
	
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
	
	printf("Comparison: signed vs unsigned right shift by 2:\n");
	printf("signed_neg = %d (0x%02X)\n", signed_neg, (unsigned char)signed_neg);
	printf("signed_neg >> 2 = %d (sign extended, fills with 1s)\n", signed_neg >> 2);
	printf("unsigned_val >> 2 = %u (logical shift, fills with 0s)\n\n", unsigned_val >> 2);
	
	// Multi-bit shift demonstration
	printf("=== Multi-bit Shift (more than 1 bit) ===\n");
	unsigned char data = 0b10110100;  // 180 in decimal
	printf("data = 0x%02X %u (binary: 10110100)\n", data, data);
	printf("data << 3 = 0x%02X %u (shift left by 3)\n", data << 3, data << 3);
	printf("data >> 3 = 0x%02X %u (shift right by 3)\n", data >> 3, data >> 3);
	printf("data << 5 = 0x%02X %u (shift left by 5)\n", data << 5, data << 5);
	printf("data >> 5 = 0x%02X %u (shift right by 5)\n", data >> 5, data >> 5);
	
	return EXIT_SUCCESS;
}
