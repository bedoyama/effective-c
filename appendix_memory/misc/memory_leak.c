#include <stdio.h>
#include <stdlib.h>

// Example demonstrating a memory leak
void leak_example() {
	int *ptr = (int *)malloc(sizeof(int) * 100);
	// Memory allocated but never freed - MEMORY LEAK!
	printf("Allocated memory but did not free it\n");
}

// Correct version
void correct_example() {
	int *ptr = (int *)malloc(sizeof(int) * 100);
	if (ptr != NULL) {
		printf("Allocated and will free memory correctly\n");
		free(ptr);
	}
}

int main() {
	printf("=== Memory Leak Example ===\n");
	leak_example();
	
	printf("\n=== Correct Example ===\n");
	correct_example();
	
	return EXIT_SUCCESS;
}
