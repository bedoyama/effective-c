#include <stdio.h>
#include <limits.h> // For integer limits
#include <float.h>  // For floating-point limits
#include <stdlib.h> // For EXIT_SUCCESS

int main() {

    printf("--- Integer Types (from <limits.h>) ---\n");
    printf("Bits in a char: %d\n\n", CHAR_BIT);

    // Using %zu for sizeof, as it returns a size_t
    printf("  %-12s: %zu bytes | %d to %d\n", 
           "char", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("  %-12s: %zu bytes | %d to %d\n", 
           "signed char", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("  %-12s: %zu bytes | 0 to %u\n\n", 
           "unsigned char", sizeof(unsigned char), UCHAR_MAX);

    printf("  %-12s: %zu bytes | %d to %d\n", 
           "short", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("  %-12s: %zu bytes | 0 to %u\n\n", 
           "unsigned short", sizeof(unsigned short), USHRT_MAX);

    printf("  %-12s: %zu bytes | %d to %d\n", 
           "int", sizeof(int), INT_MIN, INT_MAX);
    printf("  %-12s: %zu bytes | 0 to %u\n\n", 
           "unsigned int", sizeof(unsigned int), UINT_MAX);

    printf("  %-12s: %zu bytes | %ld to %ld\n", 
           "long", sizeof(long), LONG_MIN, LONG_MAX);
    printf("  %-12s: %zu bytes | 0 to %lu\n\n", 
           "unsigned long", sizeof(unsigned long), ULONG_MAX);

    printf("  %-12s: %zu bytes | %lld to %lld\n", 
           "long long", sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("  %-12s: %zu bytes | 0 to %llu\n\n", 
           "unsigned long long", sizeof(unsigned long long), ULLONG_MAX);


    printf("--- Floating-Point Types (from <float.h>) ---\n");
    // Using %e for scientific notation, which is best for min/max
    
    printf("  %-12s: %zu bytes | %d decimal digits of precision\n", 
           "float", sizeof(float), FLT_DIG);
    printf("    Min: %e | Max: %e\n\n", FLT_MIN, FLT_MAX);

    printf("  %-12s: %zu bytes | %d decimal digits of precision\n", 
           "double", sizeof(double), DBL_DIG);
    printf("    Min: %e | Max: %e\n\n", DBL_MIN, DBL_MAX);

    printf("  %-12s: %zu bytes | %d decimal digits of precision\n", 
           "long double", sizeof(long double), LDBL_DIG);
    printf("    Min: %Le | Max: %Le\n\n", LDBL_MIN, LDBL_MAX); // Use %Le for long double

    return EXIT_SUCCESS;
}