#include <stdio.h>
#include <stdlib.h>

// Function with different parameter types
int add(int a, int b) {
	return a + b;
}

double multiply(double x, double y) {
	return x * y;
}

// Function returning pointer
int* create_array(int size, int init_val) {
	int *arr = (int *)malloc(size * sizeof(int));
	if (arr != NULL) {
		for (int i = 0; i < size; i++) {
			arr[i] = init_val + i;
		}
	}
	return arr;
}

// Function with side effects
int counter = 0;
int increment_counter() {
	return ++counter;
}

int main() {
	// Simple function calls
	printf("=== Basic function calls ===\n");
	int sum = add(5, 3);
	printf("add(5, 3) = %d\n", sum);
	
	double product = multiply(2.5, 4.0);
	printf("multiply(2.5, 4.0) = %.1f\n\n", product);
	
	// Function call in expression
	printf("=== Function calls in expressions ===\n");
	int result = add(10, 20) + add(5, 15);
	printf("add(10, 20) + add(5, 15) = %d\n\n", result);
	
	// Function returning pointer
	printf("=== Function returning pointer ===\n");
	int *arr = create_array(5, 10);
	if (arr != NULL) {
		printf("Array: ");
		for (int i = 0; i < 5; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		free(arr);
	}
	
	// Side effects in function calls
	printf("\n=== Functions with side effects ===\n");
	printf("Call 1: %d\n", increment_counter());
	printf("Call 2: %d\n", increment_counter());
	printf("Call 3: %d\n", increment_counter());
	
	return EXIT_SUCCESS;
}
