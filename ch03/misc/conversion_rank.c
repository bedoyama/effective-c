#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== Conversion Rank and Type Promotion ===\n\n");
	
	// Integer conversion rank
	printf("Integer Conversion Rank (lowest to highest):\n");
	printf("_Bool < char < short < int < long < long long\n\n");
	
	// Integer promotions
	printf("Integer Promotions:\n");
	char c = 100;
	short s = 200;
	
	printf("sizeof(char) = %zu\n", sizeof(c));
	printf("sizeof(char + char) = %zu (promoted to int)\n", sizeof(c + c));
	printf("sizeof(short) = %zu\n", sizeof(s));
	printf("sizeof(short + short) = %zu (promoted to int)\n\n", sizeof(s + s));
	
	// Signed vs unsigned conversion
	printf("Signed vs Unsigned:\n");
	int signed_val = -1;
	unsigned int unsigned_val = 1;
	
	printf("signed int: %d\n", signed_val);
	printf("unsigned int: %u\n", unsigned_val);
	
	if (signed_val < unsigned_val) {
		printf("signed < unsigned\n");
	} else {
		printf("signed >= unsigned (WRONG! signed converted to unsigned)\n");
	}
	printf("signed as unsigned: %u\n\n", signed_val);
	
	// Demonstration of problem
	printf("Problem with mixing signed and unsigned:\n");
	unsigned int u = 10;
	int s_neg = -1;
	
	printf("unsigned(10) < signed(-1)?\n");
	if (u < s_neg) {
		printf("  false (WRONG!)\n");
	} else {
		printf("  true\n");
	}
	printf("  Reason: -1 converted to unsigned = %u\n\n", (unsigned int)s_neg);
	
	// Safe comparison
	printf("Safe comparison:\n");
	if (s_neg < 0 || u < (unsigned int)s_neg) {
		printf("  Correct comparison: unsigned(10) > signed(-1)\n");
	}
	
	return EXIT_SUCCESS;
}
