# include <stdio.h>
# include <stdlib.h>

void func(int arr[5]);

int main() {
	unsigned int i = 0;
	unsigned int j = 0;
	int arr[3][5];
	func(arr[i]);
	int x = arr[i][j];

	printf("x = %d\n", x);

	return EXIT_SUCCESS;
}

void func(int arr[5]) {
	arr[0] = 3;
}