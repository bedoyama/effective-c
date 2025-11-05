#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== Comparison: Iteration Statements ===\n\n");
	
	// While loop
	printf("While loop (condition checked first):\n");
	int i = 1;
	while (i <= 3) {
		printf("  i = %d\n", i);
		i++;
	}
	printf("\n");
	
	// While with false initial condition
	printf("While with false condition (never executes):\n");
	int j = 10;
	while (j <= 3) {
		printf("  This won't print\n");
		j++;
	}
	printf("  Loop body skipped\n\n");
	
	// Do-while loop
	printf("Do-while loop (executes at least once):\n");
	int k = 1;
	do {
		printf("  k = %d\n", k);
		k++;
	} while (k <= 3);
	printf("\n");
	
	// Do-while with false condition
	printf("Do-while with false condition (still executes once):\n");
	int m = 10;
	do {
		printf("  This prints once even though m > 3\n");
		m++;
	} while (m <= 3);
	printf("\n");
	
	// For loop
	printf("For loop (compact syntax):\n");
	for (int n = 1; n <= 3; n++) {
		printf("  n = %d\n", n);
	}
	printf("\n");
	
	// Equivalent while loop
	printf("Equivalent while loop:\n");
	int p = 1;  // Initialization
	while (p <= 3) {  // Condition
		printf("  p = %d\n", p);
		p++;  // Update
	}
	printf("\n");
	
	// When to use each
	printf("=== When to Use Each ===\n");
	printf("While:    Use when iterations unknown, condition checked first\n");
	printf("Do-while: Use when body must execute at least once\n");
	printf("For:      Use when iterations known or have clear init/update\n");
	
	return EXIT_SUCCESS;
}
