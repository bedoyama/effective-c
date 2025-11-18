#include <stdio.h>
#include <stdlib.h>

int main() {
	int arr[] = {10, 20, 30, 40, 50};
	int *ptr = arr;
	
	printf("Array: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
	
	// Pointer arithmetic
	printf("*ptr = %d\n", *ptr);
	printf("*(ptr + 1) = %d\n", *(ptr + 1));
	printf("*(ptr + 2) = %d\n\n", *(ptr + 2));
	
	// Incrementing pointer
	ptr++;
	printf("After ptr++, *ptr = %d\n", *ptr);
	
	ptr += 2;
	printf("After ptr += 2, *ptr = %d\n\n", *ptr);
	
	// Pointer subtraction
	int *start = arr;
	int *end = &arr[4];
	printf("Difference between end and start: %ld elements\n", end - start);
	
	// Pointer comparison
	if (start < end) {
		printf("start pointer comes before end pointer\n");
	}
	
	return EXIT_SUCCESS;
}
