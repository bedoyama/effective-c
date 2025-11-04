#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 10;
	double y = 3.14;
	char str[] = "Hello";
	int arr[10];
	
	printf("sizeof(char): %zu bytes\n", sizeof(char));
	printf("sizeof(int): %zu bytes\n", sizeof(int));
	printf("sizeof(double): %zu bytes\n", sizeof(double));
	printf("sizeof(long): %zu bytes\n", sizeof(long));
	printf("sizeof(x): %zu bytes\n", sizeof(x));
	printf("sizeof(y): %zu bytes\n", sizeof(y));
	printf("sizeof(str): %zu bytes\n", sizeof(str));
	printf("sizeof(arr): %zu bytes\n", sizeof(arr));
	printf("Number of elements in arr: %zu\n", sizeof(arr) / sizeof(arr[0]));
	
	return EXIT_SUCCESS;
}
