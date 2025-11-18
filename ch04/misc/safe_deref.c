#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Safe function that checks pointer before dereferencing
bool isN(int* ptr, int n) {
	return ptr && *ptr == n;  // don't dereference a null pointer
}

int main() {
	printf("=== Safe Pointer Dereferencing ===\n\n");
	
	int value = 42;
	int *valid_ptr = &value;
	int *null_ptr = NULL;
	
	// Test with valid pointer
	printf("Testing with valid pointer:\n");
	printf("value = %d\n", value);
	printf("isN(valid_ptr, 42): %s\n", isN(valid_ptr, 42) ? "true" : "false");
	printf("isN(valid_ptr, 10): %s\n\n", isN(valid_ptr, 10) ? "true" : "false");
	
	// Test with NULL pointer - safe due to short-circuit evaluation
	printf("Testing with NULL pointer:\n");
	printf("isN(null_ptr, 42): %s\n", isN(null_ptr, 42) ? "true" : "false");
	printf("No crash! The && operator short-circuits when ptr is NULL\n\n");
	
	// Demonstration of short-circuit behavior
	printf("=== How Short-Circuit Evaluation Works ===\n");
	printf("In expression: ptr && *ptr == n\n");
	printf("1. First, 'ptr' is evaluated (checks if NULL)\n");
	printf("2. If ptr is NULL (false), entire expression is false\n");
	printf("3. '*ptr == n' is NEVER evaluated, so no crash!\n");
	printf("4. If ptr is valid, then '*ptr == n' is evaluated\n\n");
	
	// Compare with unsafe version (commented out to avoid crash)
	printf("=== Unsafe Version (DO NOT USE) ===\n");
	printf("bool isN_unsafe(int* ptr, int n) {\n");
	printf("    return *ptr == n;  // DANGEROUS! Will crash if ptr is NULL\n");
	printf("}\n\n");
	
	// Multiple examples
	int numbers[] = {10, 20, 30, 40, 50};
	printf("=== Testing with Array Elements ===\n");
	for (int i = 0; i < 5; i++) {
		printf("isN(&numbers[%d], 30): %s\n", i, 
		       isN(&numbers[i], 30) ? "true" : "false");
	}
	
	return EXIT_SUCCESS;
}
