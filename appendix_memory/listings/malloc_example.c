#include <stdio.h>
#include <stdlib.h>

int main() {
	int *ptr;
	int n = 5;
	
	// Allocate memory for n integers
	ptr = (int *)malloc(n * sizeof(int));
	
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return EXIT_FAILURE;
	}
	
	// Initialize and display values
	for (int i = 0; i < n; i++) {
		ptr[i] = i * 10;
		printf("ptr[%d] = %d\n", i, ptr[i]);
	}
	
	// Free allocated memory
	free(ptr);
	
	return EXIT_SUCCESS;
}
