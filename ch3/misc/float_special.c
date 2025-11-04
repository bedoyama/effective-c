#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	printf("=== Special Floating-Point Values ===\n\n");
	
	// Infinity
	float inf = 1.0f / 0.0f;
	float neg_inf = -1.0f / 0.0f;
	
	printf("Infinity:\n");
	printf("1.0 / 0.0 = %f\n", inf);
	printf("-1.0 / 0.0 = %f\n", neg_inf);
	printf("isinf(inf) = %d\n\n", isinf(inf));
	
	// NaN (Not a Number)
	float nan_val = 0.0f / 0.0f;
	float sqrt_neg = sqrtf(-1.0f);
	
	printf("NaN (Not a Number):\n");
	printf("0.0 / 0.0 = %f\n", nan_val);
	printf("sqrt(-1.0) = %f\n", sqrt_neg);
	printf("isnan(nan_val) = %d\n\n", isnan(nan_val));
	
	// NaN properties
	printf("NaN properties:\n");
	printf("nan == nan? %s (NaN is not equal to anything!)\n", 
	       (nan_val == nan_val) ? "true" : "false");
	printf("nan != nan? %s\n\n", 
	       (nan_val != nan_val) ? "true" : "false");
	
	// Operations with infinity
	printf("Operations with infinity:\n");
	printf("inf + 1.0 = %f\n", inf + 1.0f);
	printf("inf * 2.0 = %f\n", inf * 2.0f);
	printf("inf - inf = %f (NaN!)\n", inf - inf);
	printf("inf / inf = %f (NaN!)\n\n", inf / inf);
	
	// Checking for special values
	printf("=== Checking for Special Values ===\n");
	float values[] = {1.0f, inf, neg_inf, nan_val, 0.0f};
	const char *names[] = {"1.0", "inf", "-inf", "NaN", "0.0"};
	
	for (int i = 0; i < 5; i++) {
		printf("%6s: finite=%d, inf=%d, nan=%d\n", 
		       names[i],
		       isfinite(values[i]),
		       isinf(values[i]),
		       isnan(values[i]));
	}
	
	return EXIT_SUCCESS;
}
