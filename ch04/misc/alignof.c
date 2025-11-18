#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>

struct example1 {
	char c;
	int i;
	double d;
};

struct example2 {
	char c1;
	char c2;
	int i;
};

int main() {
	printf("=== Basic type alignments ===\n");
	printf("alignof(char):   %zu\n", alignof(char));
	printf("alignof(short):  %zu\n", alignof(short));
	printf("alignof(int):    %zu\n", alignof(int));
	printf("alignof(long):   %zu\n", alignof(long));
	printf("alignof(float):  %zu\n", alignof(float));
	printf("alignof(double): %zu\n\n", alignof(double));
	
	printf("=== Struct alignments ===\n");
	printf("alignof(struct example1): %zu\n", alignof(struct example1));
	printf("sizeof(struct example1):  %zu\n\n", sizeof(struct example1));
	
	printf("alignof(struct example2): %zu\n", alignof(struct example2));
	printf("sizeof(struct example2):  %zu\n\n", sizeof(struct example2));
	
	// Using _Alignas specifier (C11)
	_Alignas(16) char buffer[72];
	printf("Alignment of buffer: %zu\n", alignof(buffer));
	printf("Size of buffer: %zu\n", sizeof(buffer));
	
	return EXIT_SUCCESS;
}
