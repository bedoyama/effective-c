#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *str;
	const char *message = "Hello, Dynamic Memory!";
	
	// Allocate memory for string
	str = (char *)malloc((strlen(message) + 1) * sizeof(char));
	
	if (str == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return EXIT_FAILURE;
	}
	
	// Copy string
	strcpy(str, message);
	
	printf("String: %s\n", str);
	printf("Length: %zu\n", strlen(str));
	
	free(str);
	
	return EXIT_SUCCESS;
}
