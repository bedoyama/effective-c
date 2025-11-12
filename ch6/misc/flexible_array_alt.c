#include <stdio.h>
#include <stdlib.h>

// Struct with flexible array member
struct vector {
	size_t length;
	int data[];  // Flexible array member
};

int main() {
	size_t n = 5;
	
	// Allocate struct with space for n integers
	struct vector *vec = malloc(sizeof(struct vector) + n * sizeof(int));
	
	if (vec == NULL) {
		fprintf(stderr, "Allocation failed\n");
		return EXIT_FAILURE;
	}
	
	vec->length = n;
	
	// Initialize array
	for (size_t i = 0; i < vec->length; i++) {
		vec->data[i] = i * i;
	}
	
	// Display values
	printf("Vector length: %zu\n", vec->length);
	for (size_t i = 0; i < vec->length; i++) {
		printf("vec->data[%zu] = %d\n", i, vec->data[i]);
	}
	
	free(vec);
	
	return EXIT_SUCCESS;
}
