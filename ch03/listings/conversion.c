#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("=== Arithmetic Conversions ===\n\n");
	
	// Integer to float
	printf("Integer to Floating-Point:\n");
	int i = 42;
	float f = i;
	double d = i;
	printf("int i = %d\n", i);
	printf("float f = (float)i = %f\n", f);
	printf("double d = (double)i = %f\n\n", d);
	
	// Float to integer (truncation)
	printf("Floating-Point to Integer (truncation):\n");
	float f1 = 3.14f;
	float f2 = 3.99f;
	float f3 = -2.7f;
	printf("(int)3.14 = %d\n", (int)f1);
	printf("(int)3.99 = %d (not rounded!)\n", (int)f2);
	printf("(int)-2.7 = %d\n\n", (int)f3);
	
	// Mixed arithmetic - implicit conversion
	printf("Mixed Arithmetic (implicit conversion):\n");
	int int_val = 5;
	float float_val = 2.5f;
	printf("int(5) + float(2.5) = %f (result is float)\n", int_val + float_val);
	printf("int(5) / float(2.0) = %f (result is float)\n", int_val / 2.0f);
	printf("int(5) / int(2) = %d (integer division)\n\n", 5 / 2);
	
	// Integer promotion
	printf("Integer Promotion:\n");
	char c1 = 100;
	char c2 = 3;
	int result = c1 + c2;  // chars promoted to int
	printf("char(100) + char(3) = %d (promoted to int)\n\n", result);
	
	// Usual arithmetic conversions
	printf("Usual Arithmetic Conversions:\n");
	int i_val = 10;
	long l_val = 20L;
	float f_val = 1.5f;
	double d_val = 2.5;
	
	printf("int + long = %ld (result is long)\n", i_val + l_val);
	printf("int + float = %f (result is float)\n", i_val + f_val);
	printf("float + double = %f (result is double)\n", f_val + d_val);
	printf("int + double = %f (result is double)\n", i_val + d_val);
	
	return EXIT_SUCCESS;
}
