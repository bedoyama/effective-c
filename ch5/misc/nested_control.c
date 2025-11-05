#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== Nested Loop Control ===\n\n");
	
	// Breaking out of nested loops with flag
	printf("Breaking nested loops with flag:\n");
	int found = 0;
	for (int i = 1; i <= 3 && !found; i++) {
		for (int j = 1; j <= 3; j++) {
			printf("i=%d, j=%d\n", i, j);
			if (i == 2 && j == 2) {
				printf("Found target, setting flag\n");
				found = 1;
				break;  // Breaks inner loop
			}
		}
		if (found) {
			break;  // Breaks outer loop
		}
	}
	printf("\n");
	
	// Using goto to break out of nested loops
	printf("Breaking nested loops with goto:\n");
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			printf("i=%d, j=%d\n", i, j);
			if (i == 2 && j == 2) {
				printf("Breaking both loops with goto\n");
				goto end_loops;
			}
		}
	}
end_loops:
	printf("Both loops exited\n\n");
	
	// Continue in nested loops
	printf("Continue in nested loops:\n");
	for (int i = 1; i <= 3; i++) {
		printf("Outer loop: i=%d\n", i);
		for (int j = 1; j <= 4; j++) {
			if (j == 2) {
				printf("  Skipping j=%d\n", j);
				continue;  // Only affects inner loop
			}
			printf("  Inner loop: j=%d\n", j);
		}
	}
	
	return EXIT_SUCCESS;
}
