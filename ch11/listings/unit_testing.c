/*
 * Unit Testing in C
 *
 * Demonstrates various approaches to unit testing in C, from simple
 * assertion-based tests to more structured testing patterns.
 *
 * Note: For production use, consider dedicated testing frameworks like:
 * - Unity (embedded-friendly)
 * - CMocka
 * - Check
 * - CUnit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// ============================================================================
// Simple Testing Framework
// ============================================================================

typedef struct
{
    int tests_run;
    int tests_passed;
    int tests_failed;
    const char *current_suite;
} TestContext;

static TestContext test_ctx = {0};

#define TEST_SUITE(name)                            \
    do                                              \
    {                                               \
        test_ctx.current_suite = name;              \
        printf("\n=== Test Suite: %s ===\n", name); \
    } while (0)

#define TEST_CASE(name)               \
    do                                \
    {                                 \
        printf("\nTest: %s\n", name); \
    } while (0)

#define ASSERT_TRUE(expr)                                 \
    do                                                    \
    {                                                     \
        test_ctx.tests_run++;                             \
        if (expr)                                         \
        {                                                 \
            test_ctx.tests_passed++;                      \
            printf("  ✓ PASS: " #expr "\n");              \
        }                                                 \
        else                                              \
        {                                                 \
            test_ctx.tests_failed++;                      \
            printf("  ✗ FAIL: " #expr "\n");              \
            printf("    at %s:%d\n", __FILE__, __LINE__); \
        }                                                 \
    } while (0)

#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))

#define ASSERT_EQUAL(a, b)                                                         \
    do                                                                             \
    {                                                                              \
        test_ctx.tests_run++;                                                      \
        if ((a) == (b))                                                            \
        {                                                                          \
            test_ctx.tests_passed++;                                               \
            printf("  ✓ PASS: " #a " == " #b " (%d == %d)\n", (int)(a), (int)(b)); \
        }                                                                          \
        else                                                                       \
        {                                                                          \
            test_ctx.tests_failed++;                                               \
            printf("  ✗ FAIL: " #a " == " #b "\n");                                \
            printf("    Expected: %d, Got: %d\n", (int)(b), (int)(a));             \
            printf("    at %s:%d\n", __FILE__, __LINE__);                          \
        }                                                                          \
    } while (0)

#define ASSERT_NOT_EQUAL(a, b)                                              \
    do                                                                      \
    {                                                                       \
        test_ctx.tests_run++;                                               \
        if ((a) != (b))                                                     \
        {                                                                   \
            test_ctx.tests_passed++;                                        \
            printf("  ✓ PASS: " #a " != " #b "\n");                         \
        }                                                                   \
        else                                                                \
        {                                                                   \
            test_ctx.tests_failed++;                                        \
            printf("  ✗ FAIL: " #a " != " #b " (both are %d)\n", (int)(a)); \
            printf("    at %s:%d\n", __FILE__, __LINE__);                   \
        }                                                                   \
    } while (0)

#define ASSERT_STR_EQUAL(a, b)                                       \
    do                                                               \
    {                                                                \
        test_ctx.tests_run++;                                        \
        if (strcmp((a), (b)) == 0)                                   \
        {                                                            \
            test_ctx.tests_passed++;                                 \
            printf("  ✓ PASS: " #a " == " #b " (\"%s\")\n", (a));    \
        }                                                            \
        else                                                         \
        {                                                            \
            test_ctx.tests_failed++;                                 \
            printf("  ✗ FAIL: " #a " == " #b "\n");                  \
            printf("    Expected: \"%s\", Got: \"%s\"\n", (b), (a)); \
            printf("    at %s:%d\n", __FILE__, __LINE__);            \
        }                                                            \
    } while (0)

#define ASSERT_NULL(ptr)                                  \
    do                                                    \
    {                                                     \
        test_ctx.tests_run++;                             \
        if ((ptr) == NULL)                                \
        {                                                 \
            test_ctx.tests_passed++;                      \
            printf("  ✓ PASS: " #ptr " is NULL\n");       \
        }                                                 \
        else                                              \
        {                                                 \
            test_ctx.tests_failed++;                      \
            printf("  ✗ FAIL: " #ptr " is not NULL\n");   \
            printf("    at %s:%d\n", __FILE__, __LINE__); \
        }                                                 \
    } while (0)

#define ASSERT_NOT_NULL(ptr)                              \
    do                                                    \
    {                                                     \
        test_ctx.tests_run++;                             \
        if ((ptr) != NULL)                                \
        {                                                 \
            test_ctx.tests_passed++;                      \
            printf("  ✓ PASS: " #ptr " is not NULL\n");   \
        }                                                 \
        else                                              \
        {                                                 \
            test_ctx.tests_failed++;                      \
            printf("  ✗ FAIL: " #ptr " is NULL\n");       \
            printf("    at %s:%d\n", __FILE__, __LINE__); \
        }                                                 \
    } while (0)

void print_test_summary(void)
{
    printf("\n=== Test Summary ===\n");
    printf("Total:  %d\n", test_ctx.tests_run);
    printf("Passed: %d\n", test_ctx.tests_passed);
    printf("Failed: %d\n", test_ctx.tests_failed);
    if (test_ctx.tests_failed == 0)
    {
        printf("Result: ✓ ALL TESTS PASSED\n");
    }
    else
    {
        printf("Result: ✗ SOME TESTS FAILED\n");
    }
}

// ============================================================================
// Code Under Test: Math Functions
// ============================================================================

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide_safe(int a, int b, bool *error)
{
    if (b == 0)
    {
        *error = true;
        return 0;
    }
    *error = false;
    return a / b;
}

int factorial(int n)
{
    if (n < 0)
        return -1; // Error
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

bool is_prime(int n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

// ============================================================================
// Code Under Test: String Functions
// ============================================================================

char *string_reverse(const char *str)
{
    if (str == NULL)
        return NULL;

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL)
        return NULL;

    for (size_t i = 0; i < len; i++)
    {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';

    return result;
}

bool string_is_palindrome(const char *str)
{
    if (str == NULL)
        return false;

    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - 1 - i])
        {
            return false;
        }
    }
    return true;
}

// ============================================================================
// Code Under Test: Data Structures
// ============================================================================

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} IntVector;

IntVector *vector_create(size_t initial_capacity)
{
    if (initial_capacity == 0)
        return NULL;

    IntVector *vec = malloc(sizeof(IntVector));
    if (vec == NULL)
        return NULL;

    vec->data = malloc(initial_capacity * sizeof(int));
    if (vec->data == NULL)
    {
        free(vec);
        return NULL;
    }

    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

bool vector_push(IntVector *vec, int value)
{
    if (vec == NULL)
        return false;

    if (vec->size >= vec->capacity)
    {
        size_t new_capacity = vec->capacity * 2;
        int *new_data = realloc(vec->data, new_capacity * sizeof(int));
        if (new_data == NULL)
            return false;

        vec->data = new_data;
        vec->capacity = new_capacity;
    }

    vec->data[vec->size++] = value;
    return true;
}

int vector_get(const IntVector *vec, size_t index)
{
    if (vec == NULL || index >= vec->size)
    {
        return -1; // Error indicator
    }
    return vec->data[index];
}

size_t vector_size(const IntVector *vec)
{
    return vec ? vec->size : 0;
}

void vector_destroy(IntVector *vec)
{
    if (vec != NULL)
    {
        free(vec->data);
        free(vec);
    }
}

// ============================================================================
// Test Suites
// ============================================================================

void test_math_functions(void)
{
    TEST_SUITE("Math Functions");

    TEST_CASE("add() - basic addition");
    ASSERT_EQUAL(add(2, 3), 5);
    ASSERT_EQUAL(add(-1, 1), 0);
    ASSERT_EQUAL(add(0, 0), 0);

    TEST_CASE("subtract() - basic subtraction");
    ASSERT_EQUAL(subtract(5, 3), 2);
    ASSERT_EQUAL(subtract(3, 5), -2);
    ASSERT_EQUAL(subtract(0, 0), 0);

    TEST_CASE("multiply() - basic multiplication");
    ASSERT_EQUAL(multiply(3, 4), 12);
    ASSERT_EQUAL(multiply(-2, 3), -6);
    ASSERT_EQUAL(multiply(0, 100), 0);

    TEST_CASE("divide_safe() - division with error handling");
    bool error;
    ASSERT_EQUAL(divide_safe(10, 2, &error), 5);
    ASSERT_FALSE(error);

    divide_safe(10, 0, &error);
    ASSERT_TRUE(error);

    TEST_CASE("factorial() - edge cases and normal operation");
    ASSERT_EQUAL(factorial(0), 1);
    ASSERT_EQUAL(factorial(1), 1);
    ASSERT_EQUAL(factorial(5), 120);
    ASSERT_EQUAL(factorial(-1), -1); // Error case

    TEST_CASE("is_prime() - prime number detection");
    ASSERT_FALSE(is_prime(0));
    ASSERT_FALSE(is_prime(1));
    ASSERT_TRUE(is_prime(2));
    ASSERT_TRUE(is_prime(3));
    ASSERT_FALSE(is_prime(4));
    ASSERT_TRUE(is_prime(17));
    ASSERT_FALSE(is_prime(100));
}

void test_string_functions(void)
{
    TEST_SUITE("String Functions");

    TEST_CASE("string_reverse() - basic reversal");
    char *rev1 = string_reverse("hello");
    ASSERT_NOT_NULL(rev1);
    ASSERT_STR_EQUAL(rev1, "olleh");
    free(rev1);

    TEST_CASE("string_reverse() - single character");
    char *rev2 = string_reverse("a");
    ASSERT_NOT_NULL(rev2);
    ASSERT_STR_EQUAL(rev2, "a");
    free(rev2);

    TEST_CASE("string_reverse() - empty string");
    char *rev3 = string_reverse("");
    ASSERT_NOT_NULL(rev3);
    ASSERT_STR_EQUAL(rev3, "");
    free(rev3);

    TEST_CASE("string_reverse() - NULL input");
    char *rev4 = string_reverse(NULL);
    ASSERT_NULL(rev4);

    TEST_CASE("string_is_palindrome() - palindromes");
    ASSERT_TRUE(string_is_palindrome("racecar"));
    ASSERT_TRUE(string_is_palindrome("a"));
    ASSERT_TRUE(string_is_palindrome(""));

    TEST_CASE("string_is_palindrome() - non-palindromes");
    ASSERT_FALSE(string_is_palindrome("hello"));
    ASSERT_FALSE(string_is_palindrome("ab"));

    TEST_CASE("string_is_palindrome() - NULL input");
    ASSERT_FALSE(string_is_palindrome(NULL));
}

void test_vector_operations(void)
{
    TEST_SUITE("IntVector Data Structure");

    TEST_CASE("vector_create() - creation");
    IntVector *vec = vector_create(2);
    ASSERT_NOT_NULL(vec);
    ASSERT_EQUAL(vector_size(vec), 0);

    TEST_CASE("vector_push() - adding elements");
    ASSERT_TRUE(vector_push(vec, 10));
    ASSERT_EQUAL(vector_size(vec), 1);
    ASSERT_EQUAL(vector_get(vec, 0), 10);

    ASSERT_TRUE(vector_push(vec, 20));
    ASSERT_EQUAL(vector_size(vec), 2);
    ASSERT_EQUAL(vector_get(vec, 1), 20);

    TEST_CASE("vector_push() - trigger reallocation");
    ASSERT_TRUE(vector_push(vec, 30)); // Should trigger realloc
    ASSERT_EQUAL(vector_size(vec), 3);
    ASSERT_EQUAL(vector_get(vec, 2), 30);

    TEST_CASE("vector_get() - out of bounds");
    ASSERT_EQUAL(vector_get(vec, 100), -1);

    vector_destroy(vec);

    TEST_CASE("vector_create() - zero capacity");
    IntVector *vec2 = vector_create(0);
    ASSERT_NULL(vec2);
}

void test_edge_cases(void)
{
    TEST_SUITE("Edge Cases and Error Handling");

    TEST_CASE("NULL pointer handling");
    ASSERT_EQUAL(vector_size(NULL), 0);
    ASSERT_FALSE(vector_push(NULL, 10));
    ASSERT_EQUAL(vector_get(NULL, 0), -1);

    TEST_CASE("Boundary values");
    ASSERT_TRUE(is_prime(2));      // Smallest prime
    ASSERT_FALSE(is_prime(-5));    // Negative
    ASSERT_EQUAL(factorial(0), 1); // Base case

    TEST_CASE("Empty inputs");
    char *rev = string_reverse("");
    ASSERT_NOT_NULL(rev);
    ASSERT_STR_EQUAL(rev, "");
    free(rev);

    ASSERT_TRUE(string_is_palindrome(""));
}

// ============================================================================
// Test-Driven Development Example
// ============================================================================

// Step 1: Write the test first (it will fail)
void test_gcd_tdd(void)
{
    TEST_SUITE("TDD Example: Greatest Common Divisor");

    // These tests are written before implementing gcd()
    // This is the TDD approach
}

// Step 2: Implement to make tests pass
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Step 3: Tests now pass
void test_gcd(void)
{
    TEST_SUITE("Greatest Common Divisor (TDD)");

    TEST_CASE("gcd() - basic cases");
    ASSERT_EQUAL(gcd(48, 18), 6);
    ASSERT_EQUAL(gcd(54, 24), 6);

    TEST_CASE("gcd() - edge cases");
    ASSERT_EQUAL(gcd(7, 3), 1);   // Coprime
    ASSERT_EQUAL(gcd(10, 0), 10); // Zero
    ASSERT_EQUAL(gcd(0, 10), 10); // Zero
}

// ============================================================================
// Main Function
// ============================================================================

int main(void)
{
    printf("=== Unit Testing in C ===\n");

    // Run all test suites
    test_math_functions();
    test_string_functions();
    test_vector_operations();
    test_edge_cases();
    test_gcd();

    // Print summary
    print_test_summary();

    printf("\n=== Unit Testing Best Practices ===\n\n");

    printf("1. Test Structure:\n");
    printf("   • Arrange: Set up test data\n");
    printf("   • Act: Execute the code under test\n");
    printf("   • Assert: Verify the results\n");
    printf("   • Cleanup: Free resources\n\n");

    printf("2. What to Test:\n");
    printf("   ✓ Normal cases (typical inputs)\n");
    printf("   ✓ Edge cases (boundaries, empty, max)\n");
    printf("   ✓ Error cases (NULL, invalid, overflow)\n");
    printf("   ✓ All code paths (branches, loops)\n");
    printf("   ✗ Don't test trivial getters/setters\n\n");

    printf("3. Test Independence:\n");
    printf("   • Each test should be independent\n");
    printf("   • Tests should not depend on order\n");
    printf("   • Setup/teardown for each test\n");
    printf("   • Avoid shared state between tests\n\n");

    printf("4. Test Naming:\n");
    printf("   • Use descriptive names\n");
    printf("   • Format: test_function_scenario_expectedResult\n");
    printf("   • Example: test_divide_byZero_returnsError\n\n");

    printf("5. Assertions:\n");
    printf("   • One logical assertion per test\n");
    printf("   • Use appropriate assertion type\n");
    printf("   • Provide meaningful failure messages\n\n");

    printf("6. Test Coverage:\n");
    printf("   • Aim for high statement coverage\n");
    printf("   • Test all branches (if/else, switch)\n");
    printf("   • Test boundary conditions\n");
    printf("   • Use coverage tools: gcov, lcov\n\n");

    printf("7. TDD Workflow:\n");
    printf("   1. Write a failing test\n");
    printf("   2. Implement minimal code to pass\n");
    printf("   3. Refactor while keeping tests green\n");
    printf("   4. Repeat\n\n");

    printf("8. Test Organization:\n");
    printf("   project/\n");
    printf("     src/\n");
    printf("       module.c\n");
    printf("       module.h\n");
    printf("     tests/\n");
    printf("       test_module.c\n");
    printf("       test_main.c\n");
    printf("     Makefile\n\n");

    printf("9. Makefile Example:\n");
    printf("   test: tests/test_main.c src/module.c\n");
    printf("       gcc -Wall -g $^ -o test\n");
    printf("       ./test\n\n");

    printf("10. Popular Testing Frameworks:\n");
    printf("    • Unity - Lightweight, embedded-friendly\n");
    printf("    • CMocka - Mocking support\n");
    printf("    • Check - Comprehensive features\n");
    printf("    • CUnit - JUnit-style for C\n");

    // Return non-zero if any tests failed
    return test_ctx.tests_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
 * NOTES:
 *
 * 1. Testing Pyramid:
 *
 *         /\        E2E Tests (few)
 *        /  \       Integration Tests (some)
 *       /    \      Unit Tests (many)
 *      /______\
 *
 *    Unit tests should be most numerous and fast.
 *
 * 2. F.I.R.S.T. Principles:
 *
 *    Fast:       Tests run quickly
 *    Independent: No dependencies between tests
 *    Repeatable:  Same results every time
 *    Self-validating: Pass/fail, no manual check
 *    Timely:     Written before or with code
 *
 * 3. Code Coverage:
 *
 *    Generate coverage report:
 *      gcc -fprofile-arcs -ftest-coverage test.c -o test
 *      ./test
 *      gcov test.c
 *      lcov --capture --directory . --output-file coverage.info
 *      genhtml coverage.info --output-directory coverage_html
 *
 * 4. Mocking and Stubbing:
 *
 *    Mock: Fake object to verify interactions
 *    Stub: Fake object that returns preset data
 *
 *    In C, often done with function pointers or weak symbols.
 *
 * 5. Test Doubles:
 *
 *    // Original function
 *    extern int database_get(int id);
 *
 *    // Test double (stub)
 *    int database_get(int id) {
 *        return 42;  // Fake return value
 *    }
 *
 * 6. Testing Private Functions:
 *
 *    Option 1: Include .c file in test (not recommended)
 *    Option 2: Make functions non-static for testing
 *    Option 3: Test through public API only (preferred)
 *
 * 7. Parameterized Tests:
 *
 *    typedef struct {
 *        int input;
 *        int expected;
 *    } TestCase;
 *
 *    TestCase cases[] = {
 *        {0, 1}, {1, 1}, {5, 120}
 *    };
 *
 *    for (size_t i = 0; i < sizeof(cases)/sizeof(cases[0]); i++) {
 *        ASSERT_EQUAL(factorial(cases[i].input), cases[i].expected);
 *    }
 *
 * 8. Continuous Integration:
 *
 *    .github/workflows/tests.yml:
 *
 *    name: Tests
 *    on: [push, pull_request]
 *    jobs:
 *      test:
 *        runs-on: ubuntu-latest
 *        steps:
 *          - uses: actions/checkout@v2
 *          - run: make test
 *
 * 9. Test Fixtures:
 *
 *    void setup(void) {
 *        // Initialize test data
 *    }
 *
 *    void teardown(void) {
 *        // Clean up
 *    }
 *
 *    void test_something(void) {
 *        setup();
 *        // Test code
 *        teardown();
 *    }
 *
 * 10. Memory Testing:
 *
 *     Run tests with Valgrind:
 *       valgrind --leak-check=full ./test
 *
 *     Or AddressSanitizer:
 *       gcc -fsanitize=address test.c
 *       ./a.out
 */
