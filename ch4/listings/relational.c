#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	int a = 10;
	int b = 20;
	
	printf("a = %d, b = %d\n\n", a, b);
	
	printf("a == b: %s\n", (a == b) ? "true" : "false");
	printf("a != b: %s\n", (a != b) ? "true" : "false");
	printf("a < b:  %s\n", (a < b) ? "true" : "false");
	printf("a <= b: %s\n", (a <= b) ? "true" : "false");
	printf("a > b:  %s\n", (a > b) ? "true" : "false");
	printf("a >= b: %s\n\n", (a >= b) ? "true" : "false");
	
	// Comparison in conditions
	if (a < b) {
		printf("%d is less than %d\n", a, b);
	}
	
	// Chained comparisons (be careful!)
	int x = 15;
	if (a < x && x < b) {
		printf("%d is between %d and %d\n", x, a, b);
	}
	
	return EXIT_SUCCESS;
}
