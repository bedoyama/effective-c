#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 10;
	double d = 3.14159;
	char c = 'A';
	
	printf("Original values:\n");
	printf("i = %d, d = %.5f, c = %c\n\n", i, d, c);
	
	// Implicit casts
	printf("Implicit casts:\n");
	printf("i + d = %.5f (int promoted to double)\n", i + d);
	printf("c + 1 = %d (char promoted to int)\n\n", c + 1);
	
	// Explicit casts
	printf("Explicit casts:\n");
	printf("(int)d = %d\n", (int)d);
	printf("(double)i = %.1f\n", (double)i);
	printf("(char)(c + 32) = %c\n", (char)(c + 32));
	
	// Pointer casts
	int *ptr = &i;
	void *void_ptr = (void *)ptr;
	int *back_to_int = (int *)void_ptr;
	printf("\nPointer value through void*: %d\n", *back_to_int);
	
	return EXIT_SUCCESS;
}
