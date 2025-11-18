#include <stdio.h>
#include <stdlib.h>

int main() {
	int *ptr = (int *)malloc(sizeof(int));
	
	if (ptr == NULL) {
		return EXIT_FAILURE;
	}
	
	*ptr = 42;
	printf("Value: %d\n", *ptr);
	
	// Free the memory
	free(ptr);
	
	// ptr is now a dangling pointer
	// Accessing it causes undefined behavior
	// printf("Value after free: %d\n", *ptr); // DANGEROUS!
	
	// Good practice: set to NULL after free
	ptr = NULL;
	
	// Now we can safely check
	if (ptr == NULL) {
		printf("Pointer is NULL, safe to use in conditionals\n");
	}
	
	return EXIT_SUCCESS;
}
