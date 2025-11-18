#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 10;
	
	printf("Initial value: x = %d\n\n", x);
	
	x += 5;
	printf("After x += 5:  x = %d\n", x);
	
	x -= 3;
	printf("After x -= 3:  x = %d\n", x);
	
	x *= 2;
	printf("After x *= 2:  x = %d\n", x);
	
	x /= 4;
	printf("After x /= 4:  x = %d\n", x);
	
	x %= 5;
	printf("After x %%= 5:  x = %d\n\n", x);
	
	// Bitwise compound assignments
	unsigned int y = 60;
	printf("Initial value: y = %u\n", y);
	
	y &= 13;
	printf("After y &= 13: y = %u\n", y);
	
	y = 60;
	y |= 13;
	printf("After y |= 13: y = %u\n", y);
	
	y ^= 13;
	printf("After y ^= 13: y = %u\n", y);
	
	y <<= 2;
	printf("After y <<= 2: y = %u\n", y);
	
	y >>= 1;
	printf("After y >>= 1: y = %u\n", y);
	
	return EXIT_SUCCESS;
}
