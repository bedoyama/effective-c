#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	printf("=== Fixed-Width Integer Types (stdint.h) ===\n\n");
	
	// Exact-width integer types
	printf("Exact-width types:\n");
	printf("int8_t:   %zu bytes, range: %d to %d\n", 
	       sizeof(int8_t), INT8_MIN, INT8_MAX);
	printf("uint8_t:  %zu bytes, range: 0 to %u\n", 
	       sizeof(uint8_t), UINT8_MAX);
	
	printf("int16_t:  %zu bytes, range: %d to %d\n", 
	       sizeof(int16_t), INT16_MIN, INT16_MAX);
	printf("uint16_t: %zu bytes, range: 0 to %u\n", 
	       sizeof(uint16_t), UINT16_MAX);
	
	printf("int32_t:  %zu bytes, range: %d to %d\n", 
	       sizeof(int32_t), INT32_MIN, INT32_MAX);
	printf("uint32_t: %zu bytes, range: 0 to %u\n", 
	       sizeof(uint32_t), UINT32_MAX);
	
	printf("int64_t:  %zu bytes, range: %lld to %lld\n", 
	       sizeof(int64_t), (long long)INT64_MIN, (long long)INT64_MAX);
	printf("uint64_t: %zu bytes, range: 0 to %llu\n\n", 
	       sizeof(uint64_t), (unsigned long long)UINT64_MAX);
	
	// Examples
	printf("=== Using Fixed-Width Types ===\n");
	int8_t  small = 127;
	int16_t medium = 32767;
	int32_t large = 2147483647;
	int64_t huge = 9223372036854775807LL;
	
	printf("int8_t:  %d\n", small);
	printf("int16_t: %d\n", medium);
	printf("int32_t: %d\n", large);
	printf("int64_t: %lld\n", (long long)huge);
	
	return EXIT_SUCCESS;
}
