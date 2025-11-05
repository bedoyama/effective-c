#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== If Statement ===\n\n");
	
	// Simple if
	int age = 18;
	printf("Age: %d\n", age);
	if (age >= 18) {
		printf("You are an adult\n");
	}
	printf("\n");
	
	// If-else
	printf("If-else:\n");
	int temperature = 25;
	printf("Temperature: %d°C\n", temperature);
	if (temperature > 30) {
		printf("It's hot!\n");
	} else {
		printf("It's comfortable\n");
	}
	printf("\n");
	
	// If-else if-else chain
	printf("If-else if-else chain:\n");
	int score = 75;
	printf("Score: %d\n", score);
	if (score >= 90) {
		printf("Grade: A\n");
	} else if (score >= 80) {
		printf("Grade: B\n");
	} else if (score >= 70) {
		printf("Grade: C\n");
	} else if (score >= 60) {
		printf("Grade: D\n");
	} else {
		printf("Grade: F\n");
	}
	printf("\n");
	
	// Nested if statements
	printf("Nested if statements:\n");
	int x = 10, y = 20;
	printf("x = %d, y = %d\n", x, y);
	if (x > 0) {
		printf("x is positive\n");
		if (y > x) {
			printf("y is greater than x\n");
		}
	}
	printf("\n");
	
	// Dangling else problem
	printf("Dangling else (else belongs to nearest if):\n");
	int a = 5, b = 10;
	if (a > 0)
		if (b > 0)
			printf("Both positive\n");
		else
			printf("This else belongs to 'if (b > 0)'\n");
	
	return EXIT_SUCCESS;
}
