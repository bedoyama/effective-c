#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== Bit Shift Operations ===\n\n");
	
	unsigned int a = 60;  // 0011 1100
	printf("a = %u (binary: 00111100)\n\n", a);
	
	printf("a << 1 (left shift by 1):  %u (binary: 01111000)\n", a << 1);
	printf("a << 2 (left shift by 2):  %u (binary: 11110000)\n", a << 2);
	printf("a >> 1 (right shift by 1): %u (binary: 00011110)\n", a >> 1);
	printf("a >> 2 (right shift by 2): %u (binary: 00001111)\n\n", a >> 2);
	
	// Bit truncation examples
	printf("=== Shift Truncation Examples ===\n");
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
	
	// Shift as multiplication/division
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
	
	// Multi-bit shift demonstration
	printf("\n=== Multi-bit Shift (more than 1 bit) ===\n");
	unsigned char data = 0b10110100;  // 180 in decimal
	printf("data = 0x%02X %u (binary: 10110100)\n", data, data);
	printf("data << 3 = 0x%02X %u (shift left by 3)\n", data << 3, data << 3);
	printf("data >> 3 = 0x%02X %u (shift right by 3)\n", data >> 3, data >> 3);
	printf("data << 5 = 0x%02X %u (shift left by 5)\n", data << 5, data << 5);
	printf("data >> 5 = 0x%02X %u (shift right by 5)\n", data >> 5, data >> 5);
	
	return EXIT_SUCCESS;
}
