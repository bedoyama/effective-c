#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	printf("=== Floating-Point Precision Issues ===\n\n");
	
	// Precision loss
	float f1 = 0.1f;
	float f2 = 0.2f;
	float f3 = f1 + f2;
	
	printf("float precision:\n");
	printf("0.1f + 0.2f = %.20f\n", f3);
	printf("Expected:     0.30000000000000000000\n");
	printf("Not exactly 0.3!\n\n");
	
	// Double vs float
	printf("double vs float:\n");
	double d = 0.1 + 0.2;
	float  f = 0.1f + 0.2f;
	printf("double: %.20f\n", d);
	printf("float:  %.20f\n\n", (double)f);
	
	// Comparing floating-point numbers
	printf("=== Comparing Floating-Point Numbers ===\n");
	float a = 0.1f + 0.2f;
	float b = 0.3f;
	
	printf("a = 0.1f + 0.2f = %.10f\n", a);
	printf("b = 0.3f        = %.10f\n", b);
	printf("a == b? %s (WRONG way to compare!)\n\n", (a == b) ? "true" : "false");
	
	// Correct way to compare
	float epsilon = 1e-6f;
	printf("Correct comparison using epsilon:\n");
	printf("fabsf(a - b) < epsilon? %s\n", 
	       (fabsf(a - b) < epsilon) ? "true" : "false");
	printf("fabsf(a - b) = %.10e\n\n", fabsf(a - b));
	
	// Very small and very large numbers
	printf("=== Range Issues ===\n");
	float tiny = 1e-40f;
	float huge = 1e40f;
	printf("tiny = %e\n", tiny);
	printf("huge = %e\n", huge);
	printf("tiny + 1.0f = %.10f (1 dominates)\n", tiny + 1.0f);
	printf("huge + 1.0f = %e (1 gets lost)\n", huge + 1.0f);
	
	return EXIT_SUCCESS;
}
