#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	bool a = true;
	bool b = false;
	
	printf("a = %s, b = %s\n\n", a ? "true" : "false", b ? "true" : "false");
	
	printf("a && b (AND): %s\n", (a && b) ? "true" : "false");
	printf("a || b (OR):  %s\n", (a || b) ? "true" : "false");
	printf("!a (NOT):     %s\n", !a ? "true" : "false");
	printf("!b (NOT):     %s\n\n", !b ? "true" : "false");
	
	// Short-circuit evaluation
	int x = 0;
	printf("Short-circuit AND: ");
	if (b && (++x > 0)) {
		printf("evaluated\n");
	} else {
		printf("not evaluated, x = %d\n", x);
	}
	
	int y = 0;
	printf("Short-circuit OR: ");
	if (a || (++y > 0)) {
		printf("second operand not evaluated, y = %d\n", y);
	}
	
	return EXIT_SUCCESS;
}
