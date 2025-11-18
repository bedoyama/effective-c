/*
 * Assertions in C
 *
 * Demonstrates the use of assertions for debugging and verifying program invariants.
 * Assertions help catch bugs early during development and document assumptions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// ============================================================================
// Example 1: Basic Assertions
// ============================================================================

int divide(int a, int b)
{
    assert(b != 0); // Precondition: divisor must not be zero
    return a / b;
}

int factorial(int n)
{
    assert(n >= 0); // Precondition: n must be non-negative

    if (n == 0 || n == 1)
    {
        return 1;
    }

    int result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }

    assert(result > 0); // Postcondition: factorial is always positive
    return result;
}

// ============================================================================
// Example 2: Assertions for Data Structure Invariants
// ============================================================================

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Vector;

Vector *vector_create(size_t initial_capacity)
{
    assert(initial_capacity > 0); // Precondition

    Vector *v = malloc(sizeof(Vector));
    assert(v != NULL); // Check allocation

    v->data = malloc(initial_capacity * sizeof(int));
    assert(v->data != NULL);

    v->size = 0;
    v->capacity = initial_capacity;

    // Postcondition: check invariants
    assert(v->size == 0);
    assert(v->capacity == initial_capacity);
    assert(v->size <= v->capacity);

    return v;
}

void vector_push(Vector *v, int value)
{
    assert(v != NULL); // Precondition
    assert(v->data != NULL);
    assert(v->size <= v->capacity); // Invariant check

    if (v->size >= v->capacity)
    {
        size_t new_capacity = v->capacity * 2;
        int *new_data = realloc(v->data, new_capacity * sizeof(int));
        assert(new_data != NULL); // Check reallocation

        v->data = new_data;
        v->capacity = new_capacity;
    }

    v->data[v->size++] = value;

    // Postcondition: check invariants
    assert(v->size <= v->capacity);
    assert(v->size > 0);
}

int vector_get(const Vector *v, size_t index)
{
    assert(v != NULL); // Precondition
    assert(v->data != NULL);
    assert(index < v->size); // Bounds check

    return v->data[index];
}

void vector_destroy(Vector *v)
{
    if (v != NULL)
    {
        free(v->data);
        free(v);
    }
}

// ============================================================================
// Example 3: Static Assertions (C11)
// ============================================================================

#if __STDC_VERSION__ >= 201112L

// Compile-time assertions
_Static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
_Static_assert(sizeof(char) == 1, "char must be 1 byte");

typedef struct
{
    char header[16];
    int data[32];
} Protocol;

// Verify structure size at compile time
_Static_assert(sizeof(Protocol) == 16 + 32 * sizeof(int),
               "Protocol structure has unexpected padding");

#endif

// ============================================================================
// Example 4: Custom Assertion Macros
// ============================================================================

// Custom assertion with message
#define ASSERT_MSG(expr, msg)                                              \
    do                                                                     \
    {                                                                      \
        if (!(expr))                                                       \
        {                                                                  \
            fprintf(stderr, "Assertion failed: %s\n", msg);                \
            fprintf(stderr, "  File: %s, Line: %d\n", __FILE__, __LINE__); \
            fprintf(stderr, "  Expression: %s\n", #expr);                  \
            abort();                                                       \
        }                                                                  \
    } while (0)

// Assertion that works even in release builds
#define VERIFY(expr)                                                       \
    do                                                                     \
    {                                                                      \
        if (!(expr))                                                       \
        {                                                                  \
            fprintf(stderr, "Verification failed: %s\n", #expr);           \
            fprintf(stderr, "  File: %s, Line: %d\n", __FILE__, __LINE__); \
            abort();                                                       \
        }                                                                  \
    } while (0)

// Range checking assertion
#define ASSERT_RANGE(val, min, max) \
    assert((val) >= (min) && (val) <= (max))

// Pointer validation
#define ASSERT_NOT_NULL(ptr) \
    assert((ptr) != NULL)

void process_array(int *arr, size_t size)
{
    ASSERT_NOT_NULL(arr);
    ASSERT_MSG(size > 0, "Array size must be positive");

    for (size_t i = 0; i < size; i++)
    {
        ASSERT_RANGE(arr[i], 0, 100);
        arr[i] *= 2;
    }
}

// ============================================================================
// Main Function
// ============================================================================

int main(void)
{
    printf("=== Assertions in C ===\n\n");

    printf("Test 1: Basic Assertions\n");
    printf("  divide(10, 2) = %d\n", divide(10, 2));
    printf("  factorial(5) = %d\n", factorial(5));
    printf("  ✓ Assertions passed\n\n");

    // This would fail: divide(10, 0);
    // This would fail: factorial(-1);

    printf("Test 2: Vector with Invariant Assertions\n");
    Vector *v = vector_create(2);
    printf("  Created vector with capacity 2\n");

    vector_push(v, 10);
    vector_push(v, 20);
    vector_push(v, 30); // Triggers reallocation
    printf("  Pushed 3 values (triggered reallocation)\n");

    printf("  vector[0] = %d\n", vector_get(v, 0));
    printf("  vector[1] = %d\n", vector_get(v, 1));
    printf("  vector[2] = %d\n", vector_get(v, 2));
    printf("  ✓ All invariants maintained\n");

    // This would fail: vector_get(v, 10);

    vector_destroy(v);
    printf("\n");

#if __STDC_VERSION__ >= 201112L
    printf("Test 3: Static Assertions (C11)\n");
    printf("  ✓ Static assertions verified at compile time\n");
    printf("  sizeof(int) = %zu bytes\n", sizeof(int));
    printf("  sizeof(Protocol) = %zu bytes\n", sizeof(Protocol));
    printf("\n");
#endif

    printf("Test 4: Custom Assertion Macros\n");
    int arr[] = {10, 20, 30, 40, 50};
    process_array(arr, 5);
    printf("  Processed array: ");
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n  ✓ Custom assertions passed\n\n");

    // This would fail: process_array(NULL, 5);
    // This would fail: process_array(arr, 0);

    printf("=== Assertion Best Practices ===\n\n");

    printf("When to Use Assertions:\n");
    printf("  ✓ Check preconditions (function arguments)\n");
    printf("  ✓ Check postconditions (function results)\n");
    printf("  ✓ Check invariants (data structure consistency)\n");
    printf("  ✓ Document assumptions in code\n");
    printf("  ✓ Detect programmer errors early\n\n");

    printf("When NOT to Use Assertions:\n");
    printf("  ✗ Error handling (use proper error codes)\n");
    printf("  ✗ Input validation from external sources\n");
    printf("  ✗ Side effects (assertions can be disabled)\n");
    printf("  ✗ Performance-critical paths in production\n\n");

    printf("Assertion Types:\n");
    printf("  assert()        - Standard, disabled with -DNDEBUG\n");
    printf("  _Static_assert() - Compile-time (C11)\n");
    printf("  Custom macros   - Application-specific needs\n\n");

    printf("Disabling Assertions:\n");
    printf("  Development: Compile normally (assertions enabled)\n");
    printf("    gcc -Wall -g file.c\n");
    printf("  \n");
    printf("  Production: Compile with -DNDEBUG (assertions disabled)\n");
    printf("    gcc -Wall -O2 -DNDEBUG file.c\n\n");

    printf("=== Common Assertion Patterns ===\n\n");

    printf("Precondition Check:\n");
    printf("  void process(int *data, size_t len) {\n");
    printf("      assert(data != NULL);\n");
    printf("      assert(len > 0);\n");
    printf("      // ...\n");
    printf("  }\n\n");

    printf("Postcondition Check:\n");
    printf("  int *allocate(size_t n) {\n");
    printf("      int *p = malloc(n * sizeof(int));\n");
    printf("      assert(p != NULL);\n");
    printf("      return p;\n");
    printf("  }\n\n");

    printf("Invariant Check:\n");
    printf("  typedef struct {\n");
    printf("      int *data;\n");
    printf("      size_t size, capacity;\n");
    printf("  } Buffer;\n");
    printf("  \n");
    printf("  void check_invariants(Buffer *b) {\n");
    printf("      assert(b != NULL);\n");
    printf("      assert(b->size <= b->capacity);\n");
    printf("      assert(b->data != NULL || b->capacity == 0);\n");
    printf("  }\n\n");

    printf("Unreachable Code:\n");
    printf("  switch(state) {\n");
    printf("      case STATE_A: /* ... */ break;\n");
    printf("      case STATE_B: /* ... */ break;\n");
    printf("      default:\n");
    printf("          assert(0 && \"Invalid state\");\n");
    printf("  }\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. assert() Macro:
 *    - Defined in <assert.h>
 *    - If expression is false, prints error and calls abort()
 *    - Disabled when NDEBUG is defined
 *    - Used for debugging, not error handling
 *
 * 2. When Assertions Fire:
 *    - Prints: "Assertion failed: expression, file, line"
 *    - Calls abort() which terminates the program
 *    - Generates core dump for debugging
 *
 * 3. _Static_assert (C11):
 *    - Compile-time assertion
 *    - Checked during compilation, not runtime
 *    - Cannot be disabled
 *    - Useful for checking type sizes, constants, etc.
 *
 * 4. NDEBUG Macro:
 *    - When defined, assert() becomes ((void)0)
 *    - Compile with: gcc -DNDEBUG file.c
 *    - Use in production builds for performance
 *    - Development builds should NOT define NDEBUG
 *
 * 5. Assertions vs Error Handling:
 *
 *    Assertions (programmer errors):
 *    - Internal bugs
 *    - Function preconditions
 *    - Data structure invariants
 *    - Unreachable code
 *
 *    Error Handling (external errors):
 *    - User input validation
 *    - File I/O errors
 *    - Network failures
 *    - Resource exhaustion
 *
 * 6. Assertion Guidelines:
 *    - Use for conditions that should NEVER happen
 *    - Don't put side effects in assertions
 *    - Keep expressions simple and fast
 *    - Document what you're checking
 *    - Use meaningful messages in custom macros
 *
 * 7. Side Effect Warning:
 *
 *    BAD (side effect):
 *      assert(++count > 0);  // count not incremented if NDEBUG
 *
 *    GOOD (no side effect):
 *      count++;
 *      assert(count > 0);
 *
 * 8. Custom Assertion Macros:
 *    - Can provide more information than standard assert()
 *    - Can be controlled independently
 *    - Useful for different assertion levels
 *    - Can stay enabled in release builds (VERIFY)
 *
 * 9. Assertion Levels:
 *
 *    Level 0 (always enabled):
 *      VERIFY() - Critical checks even in production
 *
 *    Level 1 (debug builds):
 *      assert() - Standard debugging checks
 *
 *    Level 2 (expensive checks):
 *      ASSERT_SLOW() - Only in special debug builds
 *
 * 10. Testing Assertions:
 *
 *     To test that assertions fire correctly:
 *
 *     #ifdef TESTING_ASSERTIONS
 *     int main() {
 *         // This should fail
 *         divide(10, 0);
 *     }
 *     #endif
 *
 *     Compile with: gcc -DTESTING_ASSERTIONS file.c
 */
