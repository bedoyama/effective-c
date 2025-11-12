/*
 * Type-Generic Macros with _Generic (C11)
 *
 * Demonstrates C11's _Generic keyword for creating type-safe generic macros.
 * This allows writing code that works with multiple types without sacrificing type safety.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// ============================================================================
// Example 1: Basic _Generic usage
// ============================================================================

#if __STDC_VERSION__ >= 201112L

// Simple type identification
#define TYPE_NAME(x) _Generic((x),            \
    char: "char",                             \
    signed char: "signed char",               \
    unsigned char: "unsigned char",           \
    short: "short",                           \
    unsigned short: "unsigned short",         \
    int: "int",                               \
    unsigned int: "unsigned int",             \
    long: "long",                             \
    unsigned long: "unsigned long",           \
    long long: "long long",                   \
    unsigned long long: "unsigned long long", \
    float: "float",                           \
    double: "double",                         \
    long double: "long double",               \
    char *: "char *",                         \
    void *: "void *",                         \
    default: "unknown")

// ============================================================================
// Example 2: Generic print function
// ============================================================================

#define PRINT(x) _Generic((x),               \
    char: printf("%c", (x)),                 \
    signed char: printf("%hhd", (x)),        \
    unsigned char: printf("%hhu", (x)),      \
    short: printf("%hd", (x)),               \
    unsigned short: printf("%hu", (x)),      \
    int: printf("%d", (x)),                  \
    unsigned int: printf("%u", (x)),         \
    long: printf("%ld", (x)),                \
    unsigned long: printf("%lu", (x)),       \
    long long: printf("%lld", (x)),          \
    unsigned long long: printf("%llu", (x)), \
    float: printf("%f", (x)),                \
    double: printf("%f", (x)),               \
    long double: printf("%Lf", (x)),         \
    char *: printf("%s", (x)),               \
    default: printf("(unprintable)"))

// ============================================================================
// Example 3: Generic absolute value
// ============================================================================

#define ABS(x) _Generic((x), \
    int: abs(x),             \
    long: labs(x),           \
    long long: llabs(x),     \
    float: fabsf(x),         \
    double: fabs(x),         \
    long double: fabsl(x))

// ============================================================================
// Example 4: Generic comparison
// ============================================================================

#define MAX(a, b) _Generic((a),    \
    int: ((a) > (b) ? (a) : (b)),  \
    long: ((a) > (b) ? (a) : (b)), \
    float: fmaxf((a), (b)),        \
    double: fmax((a), (b)),        \
    long double: fmaxl((a), (b)))

#define MIN(a, b) _Generic((a),    \
    int: ((a) < (b) ? (a) : (b)),  \
    long: ((a) < (b) ? (a) : (b)), \
    float: fminf((a), (b)),        \
    double: fmin((a), (b)),        \
    long double: fminl((a), (b)))

// ============================================================================
// Example 5: Generic square root
// ============================================================================

#define SQRT(x) _Generic((x), \
    float: sqrtf(x),          \
    double: sqrt(x),          \
    long double: sqrtl(x),    \
    default: sqrt((double)(x)))

// ============================================================================
// Example 6: Generic size calculation
// ============================================================================

#define SIZE_OF_ARRAY(arr) _Generic((arr), \
    int *: sizeof(arr) / sizeof(int),      \
    char *: sizeof(arr) / sizeof(char),    \
    float *: sizeof(arr) / sizeof(float),  \
    double *: sizeof(arr) / sizeof(double))

// ============================================================================
// Example 7: Generic swap (with typeof - GCC extension)
// ============================================================================

#ifdef __GNUC__
#define SWAP(a, b)            \
    do                        \
    {                         \
        typeof(a) _tmp = (a); \
        (a) = (b);            \
        (b) = _tmp;           \
    } while (0)
#endif

#endif // __STDC_VERSION__ >= 201112L

int main(void)
{
    printf("=== Type-Generic Macros (C11) ===\n\n");

#if __STDC_VERSION__ >= 201112L

    printf("Test 1: Type identification with _Generic\n");
    {
        int i = 42;
        float f = 3.14f;
        double d = 2.71828;
        char c = 'A';
        char *s = "Hello";
        long l = 1234567890L;

        printf("  TYPE_NAME(i) = %s\n", TYPE_NAME(i));
        printf("  TYPE_NAME(f) = %s\n", TYPE_NAME(f));
        printf("  TYPE_NAME(d) = %s\n", TYPE_NAME(d));
        printf("  TYPE_NAME(c) = %s\n", TYPE_NAME(c));
        printf("  TYPE_NAME(s) = %s\n", TYPE_NAME(s));
        printf("  TYPE_NAME(l) = %s\n", TYPE_NAME(l));
        printf("  ✓ _Generic correctly identifies types\n");
    }
    printf("\n");

    printf("Test 2: Generic print macro\n");
    {
        int i = 42;
        float f = 3.14159f;
        double d = 2.71828;
        char c = 'X';
        char *s = "World";

        printf("  PRINT(i) = ");
        PRINT(i);
        printf("\n");
        printf("  PRINT(f) = ");
        PRINT(f);
        printf("\n");
        printf("  PRINT(d) = ");
        PRINT(d);
        printf("\n");
        printf("  PRINT(c) = ");
        PRINT(c);
        printf("\n");
        printf("  PRINT(s) = ");
        PRINT(s);
        printf("\n");
        printf("  ✓ Single macro works with multiple types\n");
    }
    printf("\n");

    printf("Test 3: Generic absolute value\n");
    {
        int i = -42;
        long l = -1234567890L;
        long long ll = -9876543210LL;
        float f = -3.14f;
        double d = -2.71828;

        printf("  ABS(%d) = %d\n", i, ABS(i));
        printf("  ABS(%ld) = %ld\n", l, ABS(l));
        printf("  ABS(%lld) = %lld\n", ll, ABS(ll));
        printf("  ABS(%.2f) = %.2f\n", f, ABS(f));
        printf("  ABS(%.5f) = %.5f\n", d, ABS(d));
        printf("  ✓ Calls correct abs function for each type\n");
    }
    printf("\n");

    printf("Test 4: Generic MAX and MIN\n");
    {
        int i1 = 10, i2 = 20;
        float f1 = 3.14f, f2 = 2.71f;
        double d1 = 1.414, d2 = 1.732;

        printf("  MAX(%d, %d) = %d\n", i1, i2, MAX(i1, i2));
        printf("  MIN(%d, %d) = %d\n", i1, i2, MIN(i1, i2));
        printf("  MAX(%.2f, %.2f) = %.2f\n", f1, f2, MAX(f1, f2));
        printf("  MIN(%.2f, %.2f) = %.2f\n", f1, f2, MIN(f1, f2));
        printf("  MAX(%.3f, %.3f) = %.3f\n", d1, d2, MAX(d1, d2));
        printf("  MIN(%.3f, %.3f) = %.3f\n", d1, d2, MIN(d1, d2));
        printf("  ✓ Type-appropriate comparisons\n");
    }
    printf("\n");

    printf("Test 5: Generic square root\n");
    {
        float f = 16.0f;
        double d = 25.0;
        int i = 36;

        printf("  SQRT(%.1f) [float]  = %.2f\n", f, SQRT(f));
        printf("  SQRT(%.1f) [double] = %.2f\n", d, SQRT(d));
        printf("  SQRT(%d) [int→double] = %.2f\n", i, SQRT(i));
        printf("  ✓ Calls appropriate sqrt variant\n");
    }
    printf("\n");

#ifdef __GNUC__
    printf("Test 6: Generic swap with typeof (GCC extension)\n");
    {
        int x = 10, y = 20;
        printf("  Before: x=%d, y=%d\n", x, y);
        SWAP(x, y);
        printf("  After:  x=%d, y=%d\n", x, y);

        float a = 3.14f, b = 2.71f;
        printf("  Before: a=%.2f, b=%.2f\n", a, b);
        SWAP(a, b);
        printf("  After:  a=%.2f, b=%.2f\n", a, b);

        printf("  ✓ Type-generic swap works with any type\n");
    }
    printf("\n");
#endif

    printf("Test 7: Nested _Generic selections\n");
    {
// You can nest _Generic for more complex logic
#define IS_SIGNED(x) _Generic((x), \
    signed char: 1,                \
    short: 1,                      \
    int: 1,                        \
    long: 1,                       \
    long long: 1,                  \
    default: 0)

        int i = -1;
        unsigned int u = 1;
        float f = 3.14f;

        printf("  IS_SIGNED(int) = %d\n", IS_SIGNED(i));
        printf("  IS_SIGNED(unsigned int) = %d\n", IS_SIGNED(u));
        printf("  IS_SIGNED(float) = %d\n", IS_SIGNED(f));
        printf("  ✓ Can create complex type checks\n");

#undef IS_SIGNED
    }
    printf("\n");

    printf("Test 8: _Generic with pointers\n");
    {
#define PTR_TYPE(p) _Generic((p), \
    int *: "int pointer",         \
    char *: "char pointer",       \
    float *: "float pointer",     \
    double *: "double pointer",   \
    void *: "void pointer",       \
    default: "other pointer")

        int i;
        char c;
        float f;
        void *v = NULL;

        printf("  PTR_TYPE(&i) = %s\n", PTR_TYPE(&i));
        printf("  PTR_TYPE(&c) = %s\n", PTR_TYPE(&c));
        printf("  PTR_TYPE(&f) = %s\n", PTR_TYPE(&f));
        printf("  PTR_TYPE(v)  = %s\n", PTR_TYPE(v));
        printf("  ✓ Works with pointer types\n");

#undef PTR_TYPE
    }
    printf("\n");

    printf("=== Advantages of Type-Generic Macros ===\n");
    printf("1. Single macro works with multiple types\n");
    printf("2. Type-safe at compile time\n");
    printf("3. No runtime overhead (macro expansion)\n");
    printf("4. Cleaner API than separate functions per type\n");
    printf("5. Compiler selects correct code based on type\n");
    printf("6. Catches type errors at compile time\n\n");

    printf("=== Limitations ===\n");
    printf("1. Requires C11 or later\n");
    printf("2. Only works with known types at compile time\n");
    printf("3. Cannot work with void or incomplete types\n");
    printf("4. More complex syntax than simple macros\n");
    printf("5. Limited type conversions\n\n");

    printf("=== Common Use Cases ===\n");
    printf("1. Math functions (sqrt, abs, max, min)\n");
    printf("2. Type identification and printing\n");
    printf("3. Generic containers (with typeof)\n");
    printf("4. Compile-time type checking\n");
    printf("5. Portable code across different numeric types\n\n");

    printf("=== Best Practices ===\n");
    printf("1. Always include a 'default' case\n");
    printf("2. Use meaningful names for type-generic macros\n");
    printf("3. Document supported types\n");
    printf("4. Test with all intended types\n");
    printf("5. Consider function overloading in C++ for better type safety\n");
    printf("6. Combine with typeof for more flexibility (GCC/Clang)\n\n");

#else
    printf("❌ This program requires C11 or later.\n");
    printf("Compile with: gcc -std=c11 %s\n", __FILE__);
    printf("          or: clang -std=c11 %s\n", __FILE__);
#endif

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. _Generic Keyword (C11):
 *    - Provides compile-time type selection
 *    - Syntax: _Generic(expression, type1: value1, type2: value2, ...)
 *    - The expression's type is checked at compile time
 *    - Corresponding value for matching type is selected
 *
 * 2. How It Works:
 *    _Generic(x,
 *        int: printf("int: %d", x),
 *        float: printf("float: %f", x))
 *
 *    If x is int → first printf is used
 *    If x is float → second printf is used
 *    Compile error if x is neither
 *
 * 3. Default Case:
 *    _Generic(x,
 *        int: handle_int(x),
 *        float: handle_float(x),
 *        default: handle_other(x))
 *
 *    The 'default' case catches all unmatched types
 *
 * 4. Advantages over Traditional Macros:
 *    Traditional: #define ABS(x) ((x) < 0 ? -(x) : (x))
 *    - Works with any type but no type checking
 *    - May have issues with unsigned types
 *    - Same code for all types
 *
 *    Type-Generic: #define ABS(x) _Generic((x), int: abs(x), ...)
 *    - Calls appropriate function per type
 *    - Type-safe
 *    - Can use optimized implementations per type
 *
 * 5. Common Patterns:
 *
 *    a) Type identification:
 *       #define TYPE_NAME(x) _Generic((x), int: "int", float: "float", ...)
 *
 *    b) Function selection:
 *       #define SQRT(x) _Generic((x), float: sqrtf(x), double: sqrt(x), ...)
 *
 *    c) Format specifier selection:
 *       #define FMT(x) _Generic((x), int: "%d", float: "%f", ...)
 *
 * 6. Combining with typeof (GCC/Clang):
 *    typeof allows capturing variable's type:
 *
 *    #define SWAP(a, b) do { \
 *        typeof(a) tmp = (a); \
 *        (a) = (b); \
 *        (b) = tmp; \
 *    } while(0)
 *
 *    Works with any type without specifying it!
 *
 * 7. Real-World Example - Generic Container:
 *
 *    #define ARRAY_INIT(arr, type) _Generic((arr), \
 *        int *: init_int_array(arr, sizeof(arr)/sizeof(int)), \
 *        float *: init_float_array(arr, sizeof(arr)/sizeof(float)))
 *
 * 8. Limitations:
 *    - Cannot use with void or incomplete types
 *    - All type cases must be compile-time constants
 *    - No implicit type conversions
 *    - Limited to types known at compile time
 *
 * 9. Comparison with C++ Templates:
 *    C11 _Generic:
 *    - Simpler, works in C
 *    - Explicit type list
 *    - No code generation per type
 *    - Compile-time selection only
 *
 *    C++ Templates:
 *    - More powerful
 *    - Automatic type deduction
 *    - Generates code for each instantiation
 *    - Can use template specialization
 *
 * 10. Portability:
 *     - Requires C11: gcc -std=c11, clang -std=c11
 *     - Well supported in modern compilers
 *     - MSVC supports since Visual Studio 2015
 *     - typeof is GCC/Clang extension (not standard C)
 */
