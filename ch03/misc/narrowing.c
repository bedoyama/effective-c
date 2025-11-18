#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
	printf("=== Narrowing Conversions (Data Loss) ===\n\n");
	
	// Large int to smaller type
	printf("Converting large values to smaller types:\n");
	int large_int = 300;
	char small_char = large_int;
	
	printf("int value: %d\n", large_int);
	printf("Converted to char: %d (value truncated!)\n\n", small_char);
	
	// Long to int
	long long big = LLONG_MAX;
	int not_so_big = (int)big;
	
	printf("long long: %lld\n", big);
	printf("Converted to int: %d (truncated!)\n\n", not_so_big);
	
	// Double to float (precision loss)
	printf("Double to float (precision loss):\n");
	double precise = 1.23456789012345;
	float less_precise = (float)precise;
	
	printf("double: %.15f\n", precise);
	printf("float:  %.15f (precision lost)\n\n", (double)less_precise);
	
	// Float to int (decimal part lost)
	printf("Float to int (decimal part lost):\n");
	float pi = 3.14159f;
	int pi_int = (int)pi;
	
	printf("float: %f\n", pi);
	printf("int: %d (decimal part truncated)\n\n", pi_int);
	
	// Explicit vs implicit conversion
	printf("Explicit vs Implicit:\n");
	double d = 9.99;
	int explicit_conv = (int)d;  // Explicit cast
	// int implicit_conv = d;     // Implicit (may generate warning)
	
	printf("Explicit: (int)9.99 = %d\n", explicit_conv);
	printf("Always use explicit casts for clarity!\n");
	
	return EXIT_SUCCESS;
}
