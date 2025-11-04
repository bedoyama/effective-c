#include <stdio.h>
#include <stdlib.h>

int main() {
	// Allocate memory aligned to 16-byte boundary
	size_t alignment = 16;
	size_t size = 64;
	
	void *ptr = aligned_alloc(alignment, size);
	
	if (ptr == NULL) {
		fprintf(stderr, "Aligned allocation failed\n");
		return EXIT_FAILURE;
	}
	
	printf("Allocated %zu bytes aligned to %zu-byte boundary\n", 
	       size, alignment);
	printf("Address: %p\n", ptr);
	
	// Check alignment
	if ((size_t)ptr % alignment == 0) {
		printf("Memory is properly aligned!\n");
	}
	
	free(ptr);
	
	return EXIT_SUCCESS;
}
