#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main() {
	printf("=== Floating-Point Types ===\n\n");
	
	// Float
	printf("float:\n");
	printf("  Size: %zu bytes\n", sizeof(float));
	printf("  Precision: %d decimal digits\n", FLT_DIG);
	printf("  Min: %e\n", FLT_MIN);
	printf("  Max: %e\n", FLT_MAX);
	printf("  Epsilon: %e\n\n", FLT_EPSILON);
	
	// Double
	printf("double:\n");
	printf("  Size: %zu bytes\n", sizeof(double));
	printf("  Precision: %d decimal digits\n", DBL_DIG);
	printf("  Min: %e\n", DBL_MIN);
	printf("  Max: %e\n", DBL_MAX);
	printf("  Epsilon: %e\n\n", DBL_EPSILON);
	
	// Long double
	printf("long double:\n");
	printf("  Size: %zu bytes\n", sizeof(long double));
	printf("  Precision: %d decimal digits\n", LDBL_DIG);
	printf("  Min: %Le\n", LDBL_MIN);
	printf("  Max: %Le\n", LDBL_MAX);
	printf("  Epsilon: %Le\n\n", LDBL_EPSILON);
	
	return EXIT_SUCCESS;
}
