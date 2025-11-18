#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 5;
	int b = 5;
	
	printf("Initial values: a = %d, b = %d\n\n", a, b);
	
	// Pre-increment: increment first, then use value
	printf("Pre-increment (++a): %d\n", ++a);
	printf("After pre-increment, a = %d\n\n", a);
	
	// Post-increment: use value first, then increment
	printf("Post-increment (b++): %d\n", b++);
	printf("After post-increment, b = %d\n\n", b);
	
	// Same with decrement
	printf("Pre-decrement (--a): %d\n", --a);
	printf("Post-decrement (b--): %d\n", b--);
	printf("Final values: a = %d, b = %d\n", a, b);
	
	return EXIT_SUCCESS;
}
