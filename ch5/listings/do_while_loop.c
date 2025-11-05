#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== Do-While Loop ===\n\n");
	
	// Basic do-while
	printf("Basic do-while:\n");
	int count = 1;
	do {
		printf("Count: %d\n", count);
		count++;
	} while (count <= 5);
	printf("\n");
	
	// Do-while vs while (executes at least once)
	printf("Do-while executes at least once:\n");
	int i = 10;
	do {
		printf("This prints even though i >= 5\n");
		i++;
	} while (i < 5);
	printf("i = %d\n\n", i);
	
	// Compare with while
	printf("Compare with while loop:\n");
	int j = 10;
	while (j < 5) {
		printf("This never prints\n");
		j++;
	}
	printf("While loop body was skipped\n\n");
	
	// Menu-driven program pattern
	printf("Menu pattern with do-while:\n");
	int choice = 0;
	int iteration = 0;
	do {
		iteration++;
		printf("\n--- Menu (iteration %d) ---\n", iteration);
		printf("1. Option 1\n");
		printf("2. Option 2\n");
		printf("3. Exit\n");
		
		// Simulate user choice
		if (iteration == 1) choice = 1;
		else if (iteration == 2) choice = 2;
		else choice = 3;
		
		printf("Choice: %d\n", choice);
		
		switch (choice) {
			case 1:
				printf("Executing option 1\n");
				break;
			case 2:
				printf("Executing option 2\n");
				break;
			case 3:
				printf("Exiting...\n");
				break;
			default:
				printf("Invalid choice\n");
		}
	} while (choice != 3);
	
	return EXIT_SUCCESS;
}
