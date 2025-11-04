#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int main() {
	printf("=== Integer Types and Ranges ===\n\n");
	
	// Character types
	printf("char:\n");
	printf("  Size: %zu bytes\n", sizeof(char));
	printf("  Range: %d to %d\n\n", CHAR_MIN, CHAR_MAX);
	
	printf("unsigned char:\n");
	printf("  Size: %zu bytes\n", sizeof(unsigned char));
	printf("  Range: 0 to %u\n\n", UCHAR_MAX);
	
	// Short integer
	printf("short:\n");
	printf("  Size: %zu bytes\n", sizeof(short));
	printf("  Range: %d to %d\n\n", SHRT_MIN, SHRT_MAX);
	
	printf("unsigned short:\n");
	printf("  Size: %zu bytes\n", sizeof(unsigned short));
	printf("  Range: 0 to %u\n\n", USHRT_MAX);
	
	// Integer
	printf("int:\n");
	printf("  Size: %zu bytes\n", sizeof(int));
	printf("  Range: %d to %d\n\n", INT_MIN, INT_MAX);
	
	printf("unsigned int:\n");
	printf("  Size: %zu bytes\n", sizeof(unsigned int));
	printf("  Range: 0 to %u\n\n", UINT_MAX);
	
	// Long integer
	printf("long:\n");
	printf("  Size: %zu bytes\n", sizeof(long));
	printf("  Range: %ld to %ld\n\n", LONG_MIN, LONG_MAX);
	
	printf("unsigned long:\n");
	printf("  Size: %zu bytes\n", sizeof(unsigned long));
	printf("  Range: 0 to %lu\n\n", ULONG_MAX);
	
	// Long long integer
	printf("long long:\n");
	printf("  Size: %zu bytes\n", sizeof(long long));
	printf("  Range: %lld to %lld\n\n", LLONG_MIN, LLONG_MAX);
	
	printf("unsigned long long:\n");
	printf("  Size: %zu bytes\n", sizeof(unsigned long long));
	printf("  Range: 0 to %llu\n\n", ULLONG_MAX);
	
	return EXIT_SUCCESS;
}
