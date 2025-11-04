#include <stdio.h>
#include <stdlib.h>

// Example demonstrating double free error
void bad_example() {
	int *ptr = (int *)malloc(sizeof(int));
	if (ptr != NULL) {
		*ptr = 10;
		free(ptr);
		// free(ptr); // DOUBLE FREE - Undefined behavior!
		printf("Avoided double free by commenting it out\n");
	}
}

// Correct pattern
void good_example() {
	int *ptr = (int *)malloc(sizeof(int));
	if (ptr != NULL) {
		*ptr = 20;
		free(ptr);
		ptr = NULL; // Set to NULL after free
		
		// Safe to call free on NULL pointer
		free(ptr);
		printf("Safe: free(NULL) is allowed\n");
	}
}

int main() {
	printf("=== Avoiding Double Free ===\n");
	bad_example();
	
	printf("\n=== Correct Pattern ===\n");
	good_example();
	
	return EXIT_SUCCESS;
}
