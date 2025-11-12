#include <stdio.h>
#include <stdlib.h>

// Object-like macros
#define PI 3.14159
#define MAX_SIZE 100
#define BUFFER_SIZE 1024

// Function-like macros
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

// Multi-line macros (use backslash for continuation)
#define SWAP(a, b, type) \
    do                   \
    {                    \
        type temp = (a); \
        (a) = (b);       \
        (b) = temp;      \
    } while (0)

// Stringification operator (#)
#define TO_STRING(x) #x
#define STRINGIFY(x) TO_STRING(x)

// Token pasting operator (##)
#define CONCAT(a, b) a##b

// Variadic macros
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

int main(void)
{
    printf("=== Macro Definitions ===\n\n");

    printf("Test 1: Object-like macros\n");
    {
        printf("  PI = %f\n", PI);
        printf("  MAX_SIZE = %d\n", MAX_SIZE);
        printf("  BUFFER_SIZE = %d\n", BUFFER_SIZE);
    }
    printf("\n");

    printf("Test 2: Function-like macros\n");
    {
        int x = 5;
        printf("  SQUARE(%d) = %d\n", x, SQUARE(x));
        printf("  MAX(10, 20) = %d\n", MAX(10, 20));
        printf("  MIN(10, 20) = %d\n", MIN(10, 20));
        printf("  ABS(-15) = %d\n", ABS(-15));
    }
    printf("\n");

    printf("Test 3: Macro pitfall - missing parentheses\n");
    {
// This demonstrates why parentheses are important
#define BAD_SQUARE(x) x *x
        int a = 2 + 3;
        // BAD_SQUARE(2 + 3) expands to: 2 + 3 * 2 + 3 = 11 (WRONG!)
        // SQUARE(2 + 3) expands to: ((2 + 3) * (2 + 3)) = 25 (CORRECT!)
        printf("  SQUARE(2 + 3) = %d (correct)\n", SQUARE(a));
        printf("  Without proper parentheses, could be 11 instead of 25!\n");
#undef BAD_SQUARE
    }
    printf("\n");

    printf("Test 4: Multi-statement macros with do-while\n");
    {
        int x = 10, y = 20;
        printf("  Before swap: x=%d, y=%d\n", x, y);
        SWAP(x, y, int);
        printf("  After swap:  x=%d, y=%d\n", x, y);
        printf("  Note: do-while(0) allows macro to be used like a function\n");
    }
    printf("\n");

    printf("Test 5: Stringification operator (#)\n");
    {
        int value = 42;
        printf("  TO_STRING(value) = \"%s\"\n", TO_STRING(value));
        printf("  TO_STRING(123 + 456) = \"%s\"\n", TO_STRING(123 + 456));
        printf("  STRINGIFY(MAX_SIZE) = \"%s\"\n", STRINGIFY(MAX_SIZE));
    }
    printf("\n");

    printf("Test 6: Token pasting operator (##)\n");
    {
        int var1 = 10;
        int var2 = 20;
        // CONCAT(var, 1) becomes var1
        printf("  CONCAT(var, 1) accesses var1 = %d\n", CONCAT(var, 1));
        printf("  CONCAT(var, 2) accesses var2 = %d\n", CONCAT(var, 2));
    }
    printf("\n");

    printf("Test 7: Variadic macros\n");
    {
        DEBUG_PRINT("Simple message");
        DEBUG_PRINT("Value: %d", 42);
        DEBUG_PRINT("Multiple values: %d, %s, %f", 100, "test", 3.14);
    }
    printf("\n");

    printf("Test 8: Predefined macros\n");
    {
        printf("  __FILE__ = %s\n", __FILE__);
        printf("  __LINE__ = %d\n", __LINE__);
        printf("  __DATE__ = %s\n", __DATE__);
        printf("  __TIME__ = %s\n", __TIME__);
        printf("  __func__ = %s (C99)\n", __func__);
    }
    printf("\n");

    printf("Test 9: #undef - undefining macros\n");
    {
#define TEMP 100
        printf("  TEMP defined as: %d\n", TEMP);
#undef TEMP
// TEMP is no longer defined
#define TEMP 200
        printf("  TEMP redefined as: %d\n", TEMP);
#undef TEMP
    }
    printf("\n");

    printf("Test 10: Macro vs Function comparison\n");
    {
        printf("  Macros:\n");
        printf("    • Expanded at preprocessing time\n");
        printf("    • No type checking\n");
        printf("    • No function call overhead\n");
        printf("    • Code can be duplicated (larger binary)\n");
        printf("    • Can evaluate arguments multiple times (side effects!)\n");
        printf("\n");
        printf("  Functions:\n");
        printf("    • Called at runtime\n");
        printf("    • Type-safe\n");
        printf("    • Function call overhead\n");
        printf("    • Code appears once in binary\n");
        printf("    • Arguments evaluated once\n");
    }
    printf("\n");

    printf("Test 11: Side effect danger with macros\n");
    {
        int i = 5;
        // This is dangerous! SQUARE(i++) expands to: ((i++) * (i++))
        // i gets incremented twice!
        printf("  WARNING: SQUARE(i++) causes double increment\n");
        printf("  Original i = %d\n", i);
        int result = SQUARE(i); // Safe: uses i without side effects
        printf("  SQUARE(i) = %d, i = %d\n", result, i);

        // To show the problem (commented to avoid undefined behavior):
        // int bad_result = SQUARE(i++);  // NEVER DO THIS!
        printf("  Never use SQUARE(i++) - causes undefined behavior!\n");
    }
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. Macros are text replacement, not code\n");
    printf("2. Always use parentheses around macro parameters\n");
    printf("3. Always use parentheses around entire macro expression\n");
    printf("4. Use do-while(0) for multi-statement macros\n");
    printf("5. Beware of side effects (don't use ++ or -- with macros)\n");
    printf("6. # operator converts parameter to string\n");
    printf("7. ## operator concatenates tokens\n");
    printf("8. __VA_ARGS__ for variadic macros (C99)\n");
    printf("9. Prefer inline functions over macros when possible\n");
    printf("10. Use #undef to undefine macros\n");

    return EXIT_SUCCESS;
}
