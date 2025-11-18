/*
 * Dynamic Analysis
 *
 * Demonstrates runtime analysis tools and techniques for detecting bugs
 * during program execution.
 *
 * Tools covered:
 * - AddressSanitizer (ASan) - Memory errors
 * - UndefinedBehaviorSanitizer (UBSan) - Undefined behavior
 * - MemorySanitizer (MSan) - Uninitialized memory
 * - LeakSanitizer (LSan) - Memory leaks
 * - ThreadSanitizer (TSan) - Race conditions
 * - Valgrind - Comprehensive memory debugging
 *
 * Compile with sanitizers:
 *   gcc -fsanitize=address -g -O1 file.c -o program
 *   gcc -fsanitize=undefined -g file.c -o program
 *   gcc -fsanitize=leak -g file.c -o program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// ============================================================================
// Example 1: Memory Errors (AddressSanitizer)
// ============================================================================

// Heap buffer overflow
void heap_buffer_overflow_demo(void)
{
    printf("\n=== Heap Buffer Overflow ===\n");
    int *array = malloc(10 * sizeof(int));
    if (array == NULL)
        return;

    for (int i = 0; i < 10; i++)
    {
        array[i] = i;
    }

    // Bug: Writing beyond allocated memory
    // array[10] = 42;  // ASan detects: heap-buffer-overflow

    printf("Array allocated and used correctly\n");
    free(array);
}

// Stack buffer overflow
void stack_buffer_overflow_demo(void)
{
    printf("\n=== Stack Buffer Overflow ===\n");
    char buffer[10];

    // Bug: Writing beyond stack buffer
    // strcpy(buffer, "This string is too long");  // ASan detects

    // Fixed version:
    strncpy(buffer, "Safe", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    printf("Buffer: %s\n", buffer);
}

// Use after free
void use_after_free_demo(void)
{
    printf("\n=== Use After Free ===\n");
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL)
        return;

    *ptr = 42;
    printf("Value: %d\n", *ptr);

    free(ptr);

    // Bug: Using freed memory
    // printf("Value: %d\n", *ptr);  // ASan detects: heap-use-after-free

    ptr = NULL; // Good practice
    printf("Pointer properly nullified\n");
}

// Double free
void double_free_demo(void)
{
    printf("\n=== Double Free ===\n");
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL)
        return;

    *ptr = 42;
    free(ptr);

    // Bug: Freeing already freed memory
    // free(ptr);  // ASan detects: double-free

    printf("Memory freed once (correctly)\n");
}

// ============================================================================
// Example 2: Memory Leaks (LeakSanitizer)
// ============================================================================

void memory_leak_simple(void)
{
    printf("\n=== Simple Memory Leak ===\n");
    int *data = malloc(100 * sizeof(int));
    if (data == NULL)
        return;

    data[0] = 42;
    printf("Data allocated: %d\n", data[0]);

    // Bug: Forgot to free
    // LSan detects at program exit
    free(data); // Fixed
}

void memory_leak_conditional(int condition)
{
    printf("\n=== Conditional Memory Leak ===\n");
    char *buffer = malloc(256);
    if (buffer == NULL)
        return;

    if (condition)
    {
        // Bug: Early return without free
        // return;  // LSan detects
        free(buffer); // Fixed
        return;
    }

    free(buffer);
}

// ============================================================================
// Example 3: Undefined Behavior (UndefinedBehaviorSanitizer)
// ============================================================================

// Integer overflow
void integer_overflow_demo(void)
{
    printf("\n=== Integer Overflow ===\n");
    int x = INT_MAX;

    // Bug: Signed integer overflow (undefined behavior)
    // int y = x + 1;  // UBSan detects: signed-integer-overflow

    // Fixed: Check before operation
    if (x < INT_MAX)
    {
        int y = x + 1;
        printf("Result: %d\n", y);
    }
    else
    {
        printf("Would overflow, skipping\n");
    }
}

// Division by zero
void division_by_zero_demo(void)
{
    printf("\n=== Division by Zero ===\n");
    int a = 10;
    int b = 0;

    // Bug: Division by zero
    // int result = a / b;  // UBSan detects: division-by-zero

    // Fixed:
    if (b != 0)
    {
        int result = a / b;
        printf("Result: %d\n", result);
    }
    else
    {
        printf("Cannot divide by zero\n");
    }
}

// Null pointer dereference
void null_pointer_demo(void)
{
    printf("\n=== Null Pointer Dereference ===\n");
    int *ptr = NULL;

    // Bug: Dereferencing NULL
    // *ptr = 42;  // Segfault, caught by ASan

    // Fixed:
    if (ptr != NULL)
    {
        *ptr = 42;
    }
    else
    {
        printf("Pointer is NULL, not dereferencing\n");
    }
}

// Shift overflow
void shift_overflow_demo(void)
{
    printf("\n=== Shift Overflow ===\n");
    int x = 1;

    // Bug: Shifting by too many bits
    // int y = x << 32;  // UBSan detects: shift-exponent overflow

    // Fixed: Check shift amount
    int shift = 5;
    if (shift < 32)
    {
        int y = x << shift;
        printf("Result: %d\n", y);
    }
}

// Misaligned pointer
void misaligned_pointer_demo(void)
{
    printf("\n=== Misaligned Pointer ===\n");
    char buffer[16];

    // Bug: Creating misaligned pointer
    // int *ptr = (int*)(buffer + 1);  // May cause UBSan warning
    // *ptr = 42;  // Misaligned access

    // Fixed: Proper alignment
    int *ptr = (int *)buffer;
    *ptr = 42;
    printf("Value: %d\n", *ptr);
}

// ============================================================================
// Example 4: Uninitialized Memory (MemorySanitizer)
// ============================================================================

void uninitialized_read_demo(void)
{
    printf("\n=== Uninitialized Read ===\n");
    int x;

    // Bug: Reading uninitialized variable
    // if (x > 10) { }  // MSan detects: use-of-uninitialized-value

    // Fixed: Initialize before use
    x = 0;
    if (x > 10)
    {
        printf("x is large\n");
    }
    else
    {
        printf("x is small or zero\n");
    }
}

void uninitialized_struct_demo(void)
{
    printf("\n=== Uninitialized Struct ===\n");

    typedef struct
    {
        int id;
        char name[20];
        double value;
    } Data;

    Data data;

    // Bug: Using uninitialized struct
    // printf("ID: %d\n", data.id);  // MSan detects

    // Fixed: Initialize properly
    memset(&data, 0, sizeof(Data));
    data.id = 1;
    strcpy(data.name, "Test");
    data.value = 3.14;

    printf("ID: %d, Name: %s, Value: %.2f\n", data.id, data.name, data.value);
}

// ============================================================================
// Example 5: Advanced Sanitizer Features
// ============================================================================

// Stack use after scope
void stack_use_after_scope_demo(void)
{
    printf("\n=== Stack Use After Scope ===\n");
    int *ptr;

    {
        int local = 42;
        ptr = &local;
        printf("In scope: %d\n", *ptr);
    }

    // Bug: Using pointer to out-of-scope variable
    // printf("Out of scope: %d\n", *ptr);  // ASan detects (with flag)

    printf("Avoided use after scope\n");
}

// Global buffer overflow
static int global_array[10];

void global_buffer_overflow_demo(void)
{
    printf("\n=== Global Buffer Overflow ===\n");

    for (int i = 0; i < 10; i++)
    {
        global_array[i] = i;
    }

    // Bug: Writing beyond global array
    // global_array[10] = 42;  // ASan detects: global-buffer-overflow

    printf("Global array used correctly\n");
}

// ============================================================================
// Helper Functions for Demonstration
// ============================================================================

void demonstrate_sanitizer_output(const char *sanitizer, const char *error_type)
{
    printf("\n%s would detect:\n", sanitizer);
    printf("  Error Type: %s\n", error_type);
    printf("  Stack Trace: (showing where error occurred)\n");
    printf("  Memory State: (showing allocation/deallocation)\n");
}

// ============================================================================
// Main Function
// ============================================================================

int main(void)
{
    printf("=== Dynamic Analysis Examples ===\n");
    printf("Note: Uncomment bug examples to see sanitizers in action\n");

    // Memory errors
    heap_buffer_overflow_demo();
    stack_buffer_overflow_demo();
    use_after_free_demo();
    double_free_demo();

    // Memory leaks
    memory_leak_simple();
    memory_leak_conditional(0);

    // Undefined behavior
    integer_overflow_demo();
    division_by_zero_demo();
    null_pointer_demo();
    shift_overflow_demo();
    misaligned_pointer_demo();

    // Uninitialized memory
    uninitialized_read_demo();
    uninitialized_struct_demo();

    // Advanced features
    stack_use_after_scope_demo();
    global_buffer_overflow_demo();

    printf("\n=== Sanitizer Compilation Guide ===\n\n");

    printf("AddressSanitizer (ASan):\n");
    printf("  gcc -fsanitize=address -g -O1 file.c -o program\n");
    printf("  ./program\n");
    printf("  \n");
    printf("  Detects:\n");
    printf("    • Heap buffer overflow/underflow\n");
    printf("    • Stack buffer overflow\n");
    printf("    • Use after free\n");
    printf("    • Use after return\n");
    printf("    • Use after scope\n");
    printf("    • Double free\n");
    printf("    • Memory leaks (with LSan)\n");
    printf("  \n");
    printf("  Options:\n");
    printf("    ASAN_OPTIONS=detect_leaks=1 ./program\n");
    printf("    ASAN_OPTIONS=halt_on_error=0 ./program\n");
    printf("    ASAN_OPTIONS=log_path=asan.log ./program\n\n");

    printf("UndefinedBehaviorSanitizer (UBSan):\n");
    printf("  gcc -fsanitize=undefined -g file.c -o program\n");
    printf("  ./program\n");
    printf("  \n");
    printf("  Detects:\n");
    printf("    • Signed integer overflow\n");
    printf("    • Division by zero\n");
    printf("    • NULL pointer dereference\n");
    printf("    • Shift errors\n");
    printf("    • Array bounds\n");
    printf("    • Alignment errors\n");
    printf("    • Type mismatches\n");
    printf("  \n");
    printf("  Specific checks:\n");
    printf("    -fsanitize=shift            Shift errors\n");
    printf("    -fsanitize=integer-divide-by-zero\n");
    printf("    -fsanitize=null             NULL dereference\n");
    printf("    -fsanitize=bounds           Array bounds\n\n");

    printf("LeakSanitizer (LSan):\n");
    printf("  gcc -fsanitize=leak -g file.c -o program\n");
    printf("  ./program\n");
    printf("  \n");
    printf("  Detects:\n");
    printf("    • Memory leaks\n");
    printf("    • Reports at program exit\n");
    printf("  \n");
    printf("  Note: Included in ASan by default\n\n");

    printf("MemorySanitizer (MSan):\n");
    printf("  clang -fsanitize=memory -g file.c -o program\n");
    printf("  ./program\n");
    printf("  \n");
    printf("  Detects:\n");
    printf("    • Use of uninitialized memory\n");
    printf("  \n");
    printf("  Note: Clang only, requires instrumented libraries\n\n");

    printf("ThreadSanitizer (TSan):\n");
    printf("  gcc -fsanitize=thread -g file.c -o program\n");
    printf("  ./program\n");
    printf("  \n");
    printf("  Detects:\n");
    printf("    • Data races\n");
    printf("    • Deadlocks\n");
    printf("  \n");
    printf("  Note: Use with multi-threaded programs\n\n");

    printf("=== Valgrind ===\n\n");

    printf("Memory Error Detection:\n");
    printf("  valgrind ./program\n");
    printf("  valgrind --leak-check=full ./program\n");
    printf("  valgrind --leak-check=full --show-leak-kinds=all ./program\n");
    printf("  \n");
    printf("  Detects:\n");
    printf("    • Invalid memory access\n");
    printf("    • Use of uninitialized memory\n");
    printf("    • Memory leaks\n");
    printf("    • Double free\n");
    printf("    • Mismatched free/delete\n\n");

    printf("Valgrind Tools:\n");
    printf("  valgrind --tool=memcheck    Memory errors (default)\n");
    printf("  valgrind --tool=cachegrind  Cache profiling\n");
    printf("  valgrind --tool=callgrind   Call graph profiling\n");
    printf("  valgrind --tool=helgrind    Thread errors\n");
    printf("  valgrind --tool=massif      Heap profiling\n\n");

    printf("Detailed Options:\n");
    printf("  valgrind --track-origins=yes ./program\n");
    printf("    Track origin of uninitialized values\n");
    printf("  \n");
    printf("  valgrind --leak-check=full --show-leak-kinds=all ./program\n");
    printf("    Show all types of leaks\n");
    printf("  \n");
    printf("  valgrind --gen-suppressions=all ./program\n");
    printf("    Generate suppression patterns\n\n");

    printf("=== Comparison: Sanitizers vs Valgrind ===\n\n");

    printf("Sanitizers:\n");
    printf("  Pros:\n");
    printf("    ✓ Fast (1-3x slowdown)\n");
    printf("    ✓ Compile-time instrumentation\n");
    printf("    ✓ Better error messages\n");
    printf("    ✓ Can combine multiple sanitizers\n");
    printf("  Cons:\n");
    printf("    ✗ Requires recompilation\n");
    printf("    ✗ Some incompatible with each other\n");
    printf("    ✗ MSan requires instrumented libraries\n\n");

    printf("Valgrind:\n");
    printf("  Pros:\n");
    printf("    ✓ No recompilation needed\n");
    printf("    ✓ Works with any binary\n");
    printf("    ✓ Comprehensive tools\n");
    printf("    ✓ Stable and mature\n");
    printf("  Cons:\n");
    printf("    ✗ Slow (10-50x slowdown)\n");
    printf("    ✗ Not available on all platforms\n");
    printf("    ✗ May not work with JIT compilers\n\n");

    printf("=== Best Practices ===\n\n");

    printf("Development Workflow:\n");
    printf("  1. Develop with ASan enabled:\n");
    printf("     gcc -fsanitize=address -g -O1 *.c\n");
    printf("  \n");
    printf("  2. Run tests with sanitizers:\n");
    printf("     make test CFLAGS='-fsanitize=address,undefined'\n");
    printf("  \n");
    printf("  3. Check for leaks before commit:\n");
    printf("     ASAN_OPTIONS=detect_leaks=1 ./test_suite\n");
    printf("  \n");
    printf("  4. Periodic Valgrind run:\n");
    printf("     valgrind --leak-check=full ./test_suite\n\n");

    printf("Sanitizer Combinations:\n");
    printf("  Safe to combine:\n");
    printf("    -fsanitize=address,undefined\n");
    printf("    -fsanitize=address,leak\n");
    printf("  \n");
    printf("  Cannot combine:\n");
    printf("    ASan with MSan\n");
    printf("    ASan with TSan\n");
    printf("    MSan with TSan\n\n");

    printf("CI/CD Integration:\n");
    printf("  # Build with sanitizers\n");
    printf("  gcc -fsanitize=address,undefined -g tests/*.c -o test\n");
    printf("  \n");
    printf("  # Run tests\n");
    printf("  ASAN_OPTIONS=halt_on_error=1 ./test\n");
    printf("  \n");
    printf("  # Fail CI if errors detected\n");
    printf("  if [ $? -ne 0 ]; then exit 1; fi\n\n");

    printf("Debugging with Sanitizers:\n");
    printf("  # Break on sanitizer errors in GDB:\n");
    printf("  gdb --args ./program\n");
    printf("  (gdb) break __asan_report_error\n");
    printf("  (gdb) run\n");
    printf("  \n");
    printf("  # Get more detailed output:\n");
    printf("  ASAN_OPTIONS=verbosity=1:debug=1 ./program\n\n");

    printf("Performance Tips:\n");
    printf("  • Use -O1 with ASan (not -O0)\n");
    printf("  • Disable for performance testing\n");
    printf("  • Use in debug/test builds only\n");
    printf("  • Consider selective instrumentation\n\n");

    printf("=== Sanitizer Environment Variables ===\n\n");

    printf("ASAN_OPTIONS:\n");
    printf("  detect_leaks=1          Enable leak detection\n");
    printf("  halt_on_error=0         Continue after error\n");
    printf("  log_path=asan.log       Write to file\n");
    printf("  symbolize=1             Symbolize stack traces\n");
    printf("  abort_on_error=1        Abort on first error\n\n");

    printf("UBSAN_OPTIONS:\n");
    printf("  print_stacktrace=1      Show stack trace\n");
    printf("  halt_on_error=1         Stop on first error\n");
    printf("  suppressions=file.txt   Suppress known issues\n\n");

    printf("LSAN_OPTIONS:\n");
    printf("  suppressions=file.txt   Suppress leak patterns\n");
    printf("  report_objects=1        Show leaked objects\n\n");

    printf("=== Makefile Integration ===\n\n");

    printf("SANITIZE ?= 0\n");
    printf("\n");
    printf("ifeq ($(SANITIZE),1)\n");
    printf("  CFLAGS += -fsanitize=address,undefined -g -O1\n");
    printf("  LDFLAGS += -fsanitize=address,undefined\n");
    printf("endif\n");
    printf("\n");
    printf("Usage:\n");
    printf("  make                    # Normal build\n");
    printf("  make SANITIZE=1         # Build with sanitizers\n");
    printf("  make test SANITIZE=1    # Run tests with sanitizers\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Sanitizer Performance:
 *
 *    Slowdown (approximate):
 *      ASan:  2-3x slower, 2-3x memory
 *      MSan:  2-3x slower, 2x memory
 *      TSan:  5-15x slower, 5-10x memory
 *      UBSan: 1.2x slower, minimal memory
 *      LSan:  Minimal (only at exit)
 *
 * 2. Platform Support:
 *
 *    Linux:
 *      All sanitizers fully supported
 *      GCC and Clang
 *
 *    macOS:
 *      ASan, UBSan, TSan (Clang)
 *      LSan included in ASan
 *      MSan not supported
 *
 *    Windows:
 *      Limited support (Clang)
 *      ASan available in recent versions
 *
 * 3. Symbolization:
 *
 *    Ensure symbols in stack traces:
 *      • Compile with -g
 *      • Install llvm-symbolizer
 *      • Set ASAN_SYMBOLIZER_PATH if needed
 *
 *    Example:
 *      export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
 *
 * 4. Common ASan Errors:
 *
 *    heap-buffer-overflow:
 *      Writing past allocated buffer
 *
 *    stack-buffer-overflow:
 *      Writing past stack array
 *
 *    heap-use-after-free:
 *      Using freed memory
 *
 *    double-free:
 *      Freeing already freed memory
 *
 *    memory-leaks:
 *      Not freeing allocated memory
 *
 * 5. Suppression Files:
 *
 *    Create suppressions.txt:
 *
 *    leak:known_leak_function
 *    leak:*third_party*
 *
 *    Use:
 *      LSAN_OPTIONS=suppressions=suppressions.txt ./program
 *
 * 6. Valgrind Suppression:
 *
 *    Generate:
 *      valgrind --gen-suppressions=all ./program
 *
 *    Create valgrind.supp:
 *    {
 *       <insert_name_here>
 *       Memcheck:Leak
 *       fun:malloc
 *       fun:known_leak
 *    }
 *
 *    Use:
 *      valgrind --suppressions=valgrind.supp ./program
 *
 * 7. False Positives:
 *
 *    Some code may trigger false positives:
 *      • Intentional overlapping operations
 *      • Custom allocators
 *      • Assembly code
 *      • Third-party libraries
 *
 *    Solutions:
 *      • Use suppression files
 *      • Annotate with __attribute__
 *      • Selectively disable sanitizers
 *
 * 8. Testing Strategy:
 *
 *    Daily development:
 *      -fsanitize=address,undefined
 *
 *    Before commit:
 *      All sanitizers + Valgrind
 *
 *    CI/CD:
 *      Multiple builds with different sanitizers
 *
 *    Periodic:
 *      Fuzzing with sanitizers
 *
 * 9. Combining with Other Tools:
 *
 *    Sanitizers + GDB:
 *      gcc -fsanitize=address -g file.c
 *      gdb ./a.out
 *      (gdb) break __asan_report_error
 *
 *    Sanitizers + Fuzzing:
 *      afl-gcc -fsanitize=address fuzzer.c
 *
 *    Sanitizers + Coverage:
 *      gcc -fsanitize=address -fprofile-arcs -ftest-coverage file.c
 *
 * 10. Production Considerations:
 *
 *     DO NOT ship with sanitizers:
 *       • Significant overhead
 *       • Larger binary size
 *       • Potential instability
 *
 *     Consider hardening instead:
 *       -D_FORTIFY_SOURCE=2
 *       -fstack-protector-strong
 *       -fPIE -pie
 *
 *     Use sanitizers in:
 *       • Development builds
 *       • Testing/QA builds
 *       • CI/CD pipelines
 *       • Pre-production testing
 */
