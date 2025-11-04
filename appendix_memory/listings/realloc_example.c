#include <stdio.h>
#include <stdlib.h>

int main() {
	int *arr;
	size_t size = 3;
	
	// Initial allocation
	arr = (int *)malloc(size * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "Initial allocation failed\n");
		return EXIT_FAILURE;
	}
	
	// Initialize values
	for (size_t i = 0; i < size; i++) {
		arr[i] = i + 1;
	}
	
	printf("Initial array:\n");
	for (size_t i = 0; i < size; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]);
	}
	
	// Resize array
	size = 6;
	int *temp = (int *)realloc(arr, size * sizeof(int));
	if (temp == NULL) {
		fprintf(stderr, "Reallocation failed\n");
		free(arr);
		return EXIT_FAILURE;
	}
	arr = temp;
	
	// Initialize new elements
	for (size_t i = 3; i < size; i++) {
		arr[i] = i + 1;
	}
	
	printf("\nResized array:\n");
	for (size_t i = 0; i < size; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]);
	}
	
	free(arr);
	
	return EXIT_SUCCESS;
}
