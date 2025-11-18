/*
 * Static Analysis
 *
 * Demonstrates common code issues that static analysis tools can detect.
 * Static analysis finds bugs without running the code.
 *
 * Tools covered:
 * - GCC/Clang warnings
 * - GCC static analyzer (-fanalyzer)
 * - Clang Static Analyzer (scan-build)
 * - cppcheck
 * - splint
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// Example 1: Uninitialized Variables
// ============================================================================

// Detected by: -Wuninitialized (requires -O1 or higher)
int uninitialized_variable_issue(void)
{
    int x; // Warning: uninitialized
    // return x;  // Would use uninitialized value
    x = 10; // Fixed
    return x;
}

void conditional_initialization_issue(bool condition)
{
    int value;
    if (condition)
    {
        value = 42;
    }
    // printf("%d\n", value);  // May be uninitialized if condition is false

    // Fixed version:
    int value_fixed = 0; // Always initialize
    if (condition)
    {
        value_fixed = 42;
    }
    printf("%d\n", value_fixed);
}

// ============================================================================
// Example 2: Memory Leaks
// ============================================================================

// Detected by: -fanalyzer, scan-build
void memory_leak_example(void)
{
    int *data = malloc(100 * sizeof(int));
    if (data == NULL)
    {
        return;
    }

    // Do some work...
    data[0] = 42;

    // Bug: Missing free(data) - static analyzer will warn
    free(data); // Fixed
}

void conditional_leak_issue(bool condition)
{
    char *buffer = malloc(256);
    if (buffer == NULL)
    {
        return;
    }

    if (condition)
    {
        return; // Bug: Leak when condition is true
    }

    free(buffer);
}

void conditional_leak_fixed(bool condition)
{
    char *buffer = malloc(256);
    if (buffer == NULL)
    {
        return;
    }

    if (condition)
    {
        free(buffer); // Fixed
        return;
    }

    free(buffer);
}

// ============================================================================
// Example 3: Null Pointer Dereference
// ============================================================================

// Detected by: -fanalyzer, scan-build
void null_dereference_issue(void)
{
    int *ptr = NULL;
    // *ptr = 42;  // Bug: NULL dereference - analyzer warns

    // Fixed version:
    if (ptr != NULL)
    {
        *ptr = 42;
    }
}

void potential_null_dereference(int *data)
{
    // Bug: Doesn't check if data is NULL
    // *data = 100;  // Potential NULL dereference

    // Fixed:
    if (data != NULL)
    {
        *data = 100;
    }
}

// ============================================================================
// Example 4: Buffer Overflow
// ============================================================================

// Detected by: -Wstringop-overflow, cppcheck
void buffer_overflow_issues(void)
{
    char buffer[10];

    // Bug: Possible overflow
    // strcpy(buffer, "This is too long");  // Static analysis warning

    // Fixed:
    strncpy(buffer, "Safe", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
}

void array_bounds_issue(void)
{
    int arr[5] = {1, 2, 3, 4, 5};

    // Bug: Out of bounds access
    // arr[5] = 100;  // Warning with -Warray-bounds

    // Fixed:
    if (4 < 5)
    {
        arr[4] = 100;
    }
}

// ============================================================================
// Example 5: Use After Free
// ============================================================================

// Detected by: -fanalyzer, scan-build
void use_after_free_issue(void)
{
    int *data = malloc(sizeof(int));
    if (data == NULL)
        return;

    *data = 42;
    free(data);

    // Bug: Use after free
    // printf("%d\n", *data);  // Analyzer warns

    data = NULL; // Good practice: nullify after free
}

// ============================================================================
// Example 6: Resource Leaks
// ============================================================================

// Detected by: -fanalyzer, scan-build
void file_leak_issue(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
        return; // Bug: File not closed - analyzer warns
    }

    fclose(file);
}

void file_leak_fixed(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
        fclose(file); // Fixed: Close before return
        return;
    }

    fclose(file);
}

// ============================================================================
// Example 7: Dead Code
// ============================================================================

// Detected by: -Wunreachable-code
int dead_code_example(int x)
{
    if (x > 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    // return -1;  // Warning: Unreachable code
}

void dead_assignment_issue(void)
{
    int x = 10; // Warning: Value never used
    x = 20;     // Overwrites without reading first value
    printf("%d\n", x);
}

// ============================================================================
// Example 8: Sign Comparison Issues
// ============================================================================

// Detected by: -Wsign-compare
void sign_comparison_issues(void)
{
    int signed_val = -1;
    unsigned int unsigned_val = 1;

    // Bug: Comparing signed with unsigned
    // Result may be unexpected
    if (signed_val < (int)unsigned_val)
    { // Fixed: cast
        printf("Comparison done safely\n");
    }
}

// ============================================================================
// Example 9: Format String Vulnerabilities
// ============================================================================

// Detected by: -Wformat, -Wformat-security
void format_string_issues(const char *user_input)
{
    // Bug: Format string vulnerability
    // printf(user_input);  // Dangerous if user_input contains %s, %x

    // Fixed:
    printf("%s", user_input);
}

void format_mismatch_issue(void)
{
    int value = 42;
    // printf("%s\n", value);  // Bug: Format specifier mismatch
    printf("%d\n", value); // Fixed
}

// ============================================================================
// Example 10: Logic Errors
// ============================================================================

// Detected by: -fanalyzer, careful review
bool logic_error_example(int *arr, size_t size)
{
    if (arr == NULL && size > 0)
    { // Bug: Contradictory condition
        return false;
    }

    // Should be: if (arr == NULL || size == 0)
    return true;
}

void implicit_fallthrough_issue(int x)
{
    switch (x)
    {
    case 1:
        printf("One\n");
        // Bug: Implicit fallthrough
        // __attribute__((fallthrough));  // Fix: Mark intentional
    case 2:
        printf("Two\n");
        break;
    default:
        printf("Other\n");
    }
}

// ============================================================================
// Example 11: Integer Overflow
// ============================================================================

// Detected by: -ftrapv, -fanalyzer (sometimes)
int integer_overflow_issue(int a, int b)
{
    // Bug: Possible overflow
    return a + b; // May overflow if a and b are large
}

int integer_overflow_fixed(int a, int b)
{
    // Check before operation
    if (a > 0 && b > 0 && a > INT_MAX - b)
    {
        return INT_MAX; // Saturate
    }
    if (a < 0 && b < 0 && a < INT_MIN - b)
    {
        return INT_MIN; // Saturate
    }
    return a + b;
}

// ============================================================================
// Example 12: Missing Return Statement
// ============================================================================

// Detected by: -Wreturn-type
/*
int missing_return_issue(int x) {
    if (x > 0) {
        return 1;
    }
    // Bug: No return for x <= 0
}
*/

int missing_return_fixed(int x)
{
    if (x > 0)
    {
        return 1;
    }
    return 0; // Fixed
}

// ============================================================================
// Main Function
// ============================================================================

int main(void)
{
    printf("=== Static Analysis Examples ===\n\n");

    printf("1. Uninitialized Variables:\n");
    printf("   Result: %d\n", uninitialized_variable_issue());
    conditional_initialization_issue(true);

    printf("\n2. Memory Management:\n");
    memory_leak_example();
    conditional_leak_fixed(false);
    printf("   ✓ Memory properly managed\n");

    printf("\n3. Null Pointer Safety:\n");
    null_dereference_issue();
    int value = 42;
    potential_null_dereference(&value);
    printf("   ✓ No null dereferences\n");

    printf("\n4. Buffer Safety:\n");
    buffer_overflow_issues();
    array_bounds_issue();
    printf("   ✓ No buffer overflows\n");

    printf("\n5. Resource Management:\n");
    use_after_free_issue();
    printf("   ✓ No use-after-free\n");

    printf("\n6. File Handling:\n");
    file_leak_fixed("/etc/hosts");
    printf("   ✓ Files properly closed\n");

    printf("\n7. Code Quality:\n");
    printf("   dead_code_example(15) = %d\n", dead_code_example(15));
    dead_assignment_issue();

    printf("\n8. Type Safety:\n");
    sign_comparison_issues();
    printf("   ✓ Comparisons done safely\n");

    printf("\n9. Format String Safety:\n");
    format_string_issues("User input");
    format_mismatch_issue();
    printf("   ✓ Format strings used safely\n");

    printf("\n10. Logic Correctness:\n");
    int arr[] = {1, 2, 3};
    printf("    logic_error_example: %s\n",
           logic_error_example(arr, 3) ? "true" : "false");
    implicit_fallthrough_issue(1);

    printf("\n11. Integer Safety:\n");
    printf("    Overflow check: %d\n", integer_overflow_fixed(100, 200));

    printf("\n12. Return Paths:\n");
    printf("    missing_return_fixed(5) = %d\n", missing_return_fixed(5));

    printf("\n=== Static Analysis Tools ===\n\n");

    printf("GCC Built-in:\n");
    printf("  gcc -Wall -Wextra -Wpedantic file.c\n");
    printf("    -Wall          Most important warnings\n");
    printf("    -Wextra        Extra warnings\n");
    printf("    -Wpedantic     ISO C compliance\n");
    printf("    -Wconversion   Implicit conversions\n");
    printf("    -Wshadow       Variable shadowing\n");
    printf("    -Wcast-qual    Cast removes qualifiers\n");
    printf("    -Wformat=2     Format string checking\n\n");

    printf("GCC Static Analyzer (GCC 10+):\n");
    printf("  gcc -fanalyzer -Wall file.c\n");
    printf("  Detects:\n");
    printf("    • Memory leaks\n");
    printf("    • Use-after-free\n");
    printf("    • NULL dereferences\n");
    printf("    • Double-free\n");
    printf("    • File descriptor leaks\n\n");

    printf("Clang Static Analyzer:\n");
    printf("  scan-build gcc -Wall file.c\n");
    printf("  scan-build -o report-dir make\n");
    printf("  Generates HTML report with detailed analysis\n\n");

    printf("cppcheck:\n");
    printf("  cppcheck --enable=all file.c\n");
    printf("  cppcheck --enable=all --inconclusive .\n");
    printf("  Detects:\n");
    printf("    • Memory leaks\n");
    printf("    • Buffer overflows\n");
    printf("    • NULL pointer dereferences\n");
    printf("    • Resource leaks\n");
    printf("    • Unused functions\n\n");

    printf("splint (Secure Programming Lint):\n");
    printf("  splint +posixlib file.c\n");
    printf("  splint -strict file.c\n");
    printf("  Focuses on:\n");
    printf("    • Buffer overflows\n");
    printf("    • Type safety\n");
    printf("    • Memory management\n\n");

    printf("clang-tidy:\n");
    printf("  clang-tidy file.c -- -std=c17\n");
    printf("  clang-tidy -checks='*' file.c --\n");
    printf("  Provides:\n");
    printf("    • Code modernization\n");
    printf("    • Bug detection\n");
    printf("    • Performance hints\n\n");

    printf("=== Static Analysis Workflow ===\n\n");

    printf("Development Phase:\n");
    printf("  1. Enable compiler warnings during development\n");
    printf("     gcc -Wall -Wextra -Werror file.c\n");
    printf("  \n");
    printf("  2. Run static analyzer regularly\n");
    printf("     gcc -fanalyzer -Wall file.c\n");
    printf("  \n");
    printf("  3. Use cppcheck for additional checks\n");
    printf("     cppcheck --enable=warning,style file.c\n\n");

    printf("Pre-commit Phase:\n");
    printf("  1. Full static analysis\n");
    printf("     cppcheck --enable=all --inconclusive src/\n");
    printf("  \n");
    printf("  2. Strict compiler warnings\n");
    printf("     gcc -Wall -Wextra -Wpedantic -Werror *.c\n");
    printf("  \n");
    printf("  3. Clang static analyzer\n");
    printf("     scan-build make\n\n");

    printf("Continuous Integration:\n");
    printf("  • Run all static analyzers on every commit\n");
    printf("  • Fail build on new warnings\n");
    printf("  • Track metrics (warnings over time)\n");
    printf("  • Generate reports for review\n\n");

    printf("=== Makefile Integration ===\n\n");

    printf("analyze: static-gcc static-clang static-cppcheck\n");
    printf("\n");
    printf("static-gcc:\n");
    printf("    gcc -fanalyzer -Wall -Wextra *.c\n");
    printf("\n");
    printf("static-clang:\n");
    printf("    scan-build --status-bugs make\n");
    printf("\n");
    printf("static-cppcheck:\n");
    printf("    cppcheck --enable=all --error-exitcode=1 .\n\n");

    printf("=== Best Practices ===\n\n");

    printf("1. Enable Warnings Early:\n");
    printf("   • Use -Wall -Wextra from day one\n");
    printf("   • Treat warnings as errors with -Werror\n");
    printf("   • Don't ignore warnings, fix them\n\n");

    printf("2. Multiple Tools:\n");
    printf("   • No tool catches everything\n");
    printf("   • Use compiler + external tools\n");
    printf("   • Different tools find different issues\n\n");

    printf("3. Regular Analysis:\n");
    printf("   • Run during development (fast)\n");
    printf("   • Run before commit (thorough)\n");
    printf("   • Run in CI (comprehensive)\n\n");

    printf("4. Address Issues Promptly:\n");
    printf("   • Fix new warnings immediately\n");
    printf("   • Don't accumulate technical debt\n");
    printf("   • Understand why warning occurs\n\n");

    printf("5. Configuration:\n");
    printf("   • Create .cppcheck config file\n");
    printf("   • Configure clang-tidy checks\n");
    printf("   • Document suppressed warnings\n\n");

    printf("6. False Positives:\n");
    printf("   • Review each warning carefully\n");
    printf("   • Suppress with good reason only\n");
    printf("   • Document suppressions:\n");
    printf("     // cppcheck-suppress uninitvar\n");
    printf("     // Reason: Variable initialized in called function\n\n");

    printf("=== Tool Comparison ===\n\n");

    printf("Speed:         GCC warnings > cppcheck > fanalyzer > scan-build\n");
    printf("Thoroughness:  scan-build > fanalyzer > cppcheck > GCC warnings\n");
    printf("False positives: GCC warnings < cppcheck < fanalyzer < scan-build\n");
    printf("Setup:         GCC warnings < cppcheck < fanalyzer < scan-build\n\n");

    printf("Recommendation:\n");
    printf("  Development:   GCC -Wall -Wextra\n");
    printf("  Quick check:   cppcheck\n");
    printf("  Thorough:      GCC -fanalyzer or scan-build\n");
    printf("  CI Pipeline:   All of the above\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Static Analysis vs Dynamic Analysis:
 *
 *    Static (code inspection):
 *    • Analyzes code without running it
 *    • Finds potential issues in all paths
 *    • No runtime overhead
 *    • May have false positives
 *
 *    Dynamic (runtime checking):
 *    • Finds issues during execution
 *    • Only checks executed paths
 *    • Has runtime overhead
 *    • No false positives
 *
 *    Use both for comprehensive coverage.
 *
 * 2. Common Warning Flags:
 *
 *    Essential:
 *      -Wall -Wextra -Wpedantic
 *
 *    Additional:
 *      -Wshadow              Variable shadowing
 *      -Wcast-align          Alignment issues
 *      -Wcast-qual           Qualifier removal
 *      -Wconversion          Implicit conversions
 *      -Wformat=2            Format strings
 *      -Wunused              Unused code
 *      -Wmissing-prototypes  Missing declarations
 *      -Wstrict-prototypes   Non-prototype functions
 *
 * 3. GCC Analyzer Capabilities:
 *
 *    Memory:
 *    • malloc/free tracking
 *    • Use-after-free
 *    • Double-free
 *    • Memory leaks
 *    • NULL dereferences
 *
 *    Resources:
 *    • File descriptor leaks
 *    • fopen/fclose tracking
 *
 *    Data flow:
 *    • Uninitialized reads
 *    • Tainted input
 *
 * 4. Clang Static Analyzer:
 *
 *    Run with scan-build:
 *      scan-build gcc -Wall file.c
 *      scan-build make
 *
 *    Output HTML report:
 *      scan-build -o report make
 *      open report/*/
    index.html
        *
            *Exit on bugs : *scan -
    build-- status - bugs make * * 5. cppcheck Configuration : **Create.cppcheck in project root : **#Suppress specific warnings *[suppress] * uninitvar : src / legacy.c **#Exclude directories *[exclude] * tests / *external / **6. Suppressing Warnings : **GCC : *#pragma GCC diagnostic push *#pragma GCC diagnostic ignored "-Wunused-parameter" * void func(int unused){} * #pragma GCC diagnostic pop **cppcheck : * // cppcheck-suppress uninitvar
                                                                                                                                                                                                                                                                                                                                                                                                                            *int x;
**Clang : *#pragma clang diagnostic ignored "-Wunused-variable" *
            *7. IDE Integration : **VS Code : *    • Install C / C++ extension *    • Configure clangd *    • Enable clang -
        tidy checks
                *
                    *settings.json : *{
                        *"C_Cpp.codeAnalysis.clangTidy.enabled" : true,
                        *"C_Cpp.codeAnalysis.clangTidy.checks.enabled" : [
                            *"bugprone-*",
                            *"cert-*",
                            *"clang-analyzer-*" *
                        ] *
                    } *
            *8. CI / CD Integration : **GitHub Actions : **-name : Static Analysis *run : |
                                                                                          *sudo apt - get install cppcheck
                                                                                                          *cppcheck-- enable = all-- error - exitcode = 1 src /
                                                                                                                                                            *gcc -
                                                                                                                                                        fanalyzer - Wall - Wextra - Werror src /*.c
                                                                                                                                                                                                *
                                                                                                                                                                                                * 9. Metrics and Tracking:
                                                                                                                                                                                                *
                                                                                                                                                                                                *    Track over time:
                                                                                                                                                                                                *    • Number of warnings
                                                                                                                                                                                                *    • Lines of code
                                                                                                                                                                                                *    • Warning density (warnings/KLOC)
                                                                                                                                                                                                *    • Bug detection rate
                                                                                                                                                                                                *
                                                                                                                                                                                                *    Tools:
                                                                                                                                                                                                *    • SonarQube
                                                                                                                                                                                                *    • Coverity
                                                                                                                                                                                                *    • PVS-Studio
                                                                                                                                                                                                *
                                                                                                                                                                                                * 10. Advanced Tools:
                                                                                                                                                                                                *
                                                                                                                                                                                                *     Commercial:
                                                                                                                                                                                                *     • PVS-Studio - Deep analysis
                                                                                                                                                                                                *     • Coverity - Enterprise grade
                                                                                                                                                                                                *     • Klocwork - For large codebases
                                                                                                                                                                                                *
                                                                                                                                                                                                *     Research:
                                                                                                                                                                                                *     • Infer (Facebook) - Separation logic
                                                                                                                                                                                                *     • Frama-C - Formal verification
                                                                                                                                                                                                *     • TIS Analyzer - Undefined behavior
                                                                                                                                                                                                */
