#include <stdio.h>
#include <stdlib.h>

int main() {
	int *arr;
	size_t n = 5;
	
	// Allocate and zero-initialize memory
	arr = (int *)calloc(n, sizeof(int));
	
	if (arr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return EXIT_FAILURE;
	}
	
	printf("Values after calloc (should be 0):\n");
	for (size_t i = 0; i < n; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]);
	}
	
	free(arr);
	
	return EXIT_SUCCESS;
}
