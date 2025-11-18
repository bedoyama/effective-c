/*
 * Compiler Settings and Flags
 *
 * Demonstrates various compiler flags and their effects on code quality,
 * optimization, debugging, and error detection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// Example 1: Warning Flags
// ============================================================================

// Compile with different warning levels to see the difference:
// gcc -Wall file.c
// gcc -Wall -Wextra file.c
// gcc -Wall -Wextra -pedantic file.c

void warning_examples(void)
{
    // -Wunused-variable
    int unused_var = 42; // Warning: unused variable

    // -Wuninitialized (requires optimization)
    int uninitialized;
    // printf("%d\n", uninitialized);  // Warning: uninitialized

    // -Wimplicit-fallthrough
    int x = 2;
    switch (x)
    {
    case 1:
        printf("one\n");
        // Warning: fallthrough without comment
    case 2:
        printf("two\n");
        break;
    }

    // -Wsign-compare
    int signed_val = -1;
    unsigned int unsigned_val = 10;
    // if (signed_val < unsigned_val) {}  // Warning: signed/unsigned comparison

    (void)unused_var; // Suppress warning
    (void)signed_val;
    (void)unsigned_val;
}

// ============================================================================
// Example 2: Standard Conformance
// ============================================================================

// Compile with: gcc -std=c89, -std=c99, -std=c11, -std=c17

void standard_features(void)
{
    // C99 features
    // for (int i = 0; i < 10; i++) {}  // Declaration in for loop (C99)

    // C99 variable length arrays
    // int n = 5;
    // int vla[n];  // VLA (C99, optional in C11)

    // C11 features
#if __STDC_VERSION__ >= 201112L
    _Static_assert(sizeof(int) >= 4, "int too small");
    _Alignas(16) int aligned_var = 0;
    (void)aligned_var;
#endif

    printf("C standard: ");
#if __STDC_VERSION__ >= 201710L
    printf("C17\n");
#elif __STDC_VERSION__ >= 201112L
    printf("C11\n");
#elif __STDC_VERSION__ >= 199901L
    printf("C99\n");
#else
    printf("C89/C90\n");
#endif
}

// ============================================================================
// Example 3: Optimization Levels
// ============================================================================

// Compile with: -O0, -O1, -O2, -O3, -Os, -Ofast

// -O0: No optimization (default, best for debugging)
// -O1: Basic optimization
// -O2: Recommended for production
// -O3: Aggressive optimization (may increase code size)
// -Os: Optimize for size
// -Ofast: -O3 + non-standards-compliant optimizations

volatile int prevent_optimization = 0;

void optimization_demo(void)
{
    // Without volatile, optimizer might eliminate this loop at -O2+
    for (int i = 0; i < 1000000; i++)
    {
        prevent_optimization = i;
    }
}

// Dead code elimination example
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
    // Unreachable code - optimizer will remove this
    // printf("This will never execute\n");
    // return -1;
}

// ============================================================================
// Example 4: Debugging Flags
// ============================================================================

// -g: Generate debug information
// -g0: No debug info
// -g1: Minimal debug info
// -g3: Maximum debug info (includes macros)
// -ggdb: GDB-specific debug info

void debugging_target(int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += i;
    }
    printf("Sum: %d\n", sum);
}

// ============================================================================
// Example 5: Error Handling Flags
// ============================================================================

// -Werror: Treat all warnings as errors
// -Werror=specific-warning: Treat specific warning as error
// -Wfatal-errors: Stop after first error

// Example that would fail with -Werror -Wunused-variable
void error_example(void)
{
    int x = 10;
    (void)x; // Suppress warning
}

// ============================================================================
// Example 6: Security and Hardening Flags
// ============================================================================

// Security-related compiler flags:
// -fstack-protector-strong: Stack buffer overflow detection
// -D_FORTIFY_SOURCE=2: Compile-time and runtime buffer overflow checks
// -fPIE -pie: Position Independent Executable (ASLR)
// -Wformat-security: Format string vulnerability detection

void format_security_demo(void)
{
    const char *safe_str = "Hello, World!";
    printf("%s\n", safe_str); // Safe

    // Unsafe: would warn with -Wformat-security
    // printf(safe_str);  // Dangerous if safe_str contains %s, %x, etc.
}

char *buffer_demo(void)
{
    // With -D_FORTIFY_SOURCE=2, bounds checking on standard functions
    char buffer[10];
    strncpy(buffer, "safe", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    return NULL; // Just for demo, don't return local address
}

// ============================================================================
// Example 7: Preprocessor and Macro Debugging
// ============================================================================

// -E: Stop after preprocessing (show expanded macros)
// -dM: Dump macro definitions
// -dD: Include macro definitions in -E output

#define SQUARE(x) ((x) * (x))
#define DEBUG_PRINT(x) printf(#x " = %d\n", (x))

void preprocessor_demo(void)
{
    int value = 5;
    int result = SQUARE(value);
    DEBUG_PRINT(result);

    // To see expanded code: gcc -E file.c
    // To see all macros: gcc -dM -E file.c
}

// ============================================================================
// Example 8: Linker Flags
// ============================================================================

// -l: Link library (e.g., -lm for math library)
// -L: Add library search path
// -static: Static linking
// -shared: Create shared library
// -fPIC: Position Independent Code (for shared libraries)

#include <math.h>

void linker_demo(void)
{
    // Requires: gcc file.c -lm
    double x = 2.0;
    double result = sqrt(x);
    printf("sqrt(%.1f) = %.2f\n", x, result);
}

// ============================================================================
// Example 9: Architecture and Platform Flags
// ============================================================================

// -m32 / -m64: Target 32-bit or 64-bit
// -march=native: Optimize for current CPU
// -mtune=generic: Tune for generic CPU

void platform_info(void)
{
    printf("sizeof(void*) = %zu bytes ", sizeof(void *));
    printf("(%d-bit)\n", (int)(sizeof(void *) * 8));

#ifdef __x86_64__
    printf("Architecture: x86_64\n");
#elif defined(__i386__)
    printf("Architecture: x86\n");
#elif defined(__arm__)
    printf("Architecture: ARM\n");
#elif defined(__aarch64__)
    printf("Architecture: ARM64\n");
#endif
}

// ============================================================================
// Example 10: Dependency Generation
// ============================================================================

// -M: Generate dependencies for make
// -MM: Like -M but ignore system headers
// -MD: Generate dependencies while compiling
// -MF: Specify dependency file name

// Usage: gcc -MMD -c file.c -o file.o
// Creates: file.d with dependencies

// ============================================================================
// Main Function
// ============================================================================

int main(void)
{
    printf("=== Compiler Settings and Flags ===\n\n");

    printf("1. Warning Flags:\n");
    warning_examples();
    printf("\n");

    printf("2. Standard Conformance:\n");
    standard_features();
    printf("\n");

    printf("3. Optimization:\n");
    optimization_demo();
    printf("Optimization demo completed\n");
    printf("Result: %d\n\n", dead_code_example(15));

    printf("4. Debugging:\n");
    debugging_target(10);
    printf("\n");

    printf("5. Error Handling:\n");
    error_example();
    printf("Error handling demo completed\n\n");

    printf("6. Security:\n");
    format_security_demo();
    buffer_demo();
    printf("Security demo completed\n\n");

    printf("7. Preprocessor:\n");
    preprocessor_demo();
    printf("\n");

    printf("8. Linker:\n");
    linker_demo();
    printf("\n");

    printf("9. Platform:\n");
    platform_info();
    printf("\n");

    printf("=== Common Compilation Commands ===\n\n");

    printf("Basic Development Build:\n");
    printf("  gcc -Wall -Wextra -g -std=c17 file.c -o program\n\n");

    printf("Strict Warnings:\n");
    printf("  gcc -Wall -Wextra -Wpedantic -Werror -std=c17 file.c\n\n");

    printf("Optimized Production Build:\n");
    printf("  gcc -Wall -O2 -DNDEBUG -std=c17 file.c -o program\n\n");

    printf("Debug Build with Maximum Info:\n");
    printf("  gcc -Wall -g3 -O0 -std=c17 file.c -o program\n\n");

    printf("Security-Hardened Build:\n");
    printf("  gcc -Wall -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-strong \\\n");
    printf("      -fPIE -pie -Wformat-security file.c -o program\n\n");

    printf("Static Analysis:\n");
    printf("  gcc -Wall -Wextra -Wconversion -Wshadow -Wcast-qual \\\n");
    printf("      -Wcast-align -Wstrict-prototypes file.c\n\n");

    printf("Generate Assembly:\n");
    printf("  gcc -S -O2 file.c        # Creates file.s\n\n");

    printf("Preprocessor Output:\n");
    printf("  gcc -E file.c            # Show expanded macros\n\n");

    printf("Library Linking:\n");
    printf("  gcc file.c -lm -lpthread # Link math and pthread\n\n");

    printf("=== Useful Flag Categories ===\n\n");

    printf("Essential Warnings:\n");
    printf("  -Wall         Most important warnings\n");
    printf("  -Wextra       Additional warnings\n");
    printf("  -Wpedantic    Strict ISO C compliance\n");
    printf("  -Werror       Treat warnings as errors\n\n");

    printf("Additional Useful Warnings:\n");
    printf("  -Wshadow              Variable shadowing\n");
    printf("  -Wcast-align          Pointer alignment issues\n");
    printf("  -Wcast-qual           Cast removes qualifiers\n");
    printf("  -Wconversion          Implicit type conversions\n");
    printf("  -Wstrict-prototypes   Non-prototype functions\n");
    printf("  -Wmissing-prototypes  Missing function prototypes\n");
    printf("  -Wunused              Unused variables/functions\n");
    printf("  -Wformat=2            Format string checking\n\n");

    printf("Debug Information:\n");
    printf("  -g            Standard debug info\n");
    printf("  -g3           Maximum debug info + macros\n");
    printf("  -ggdb         GDB-specific debug info\n\n");

    printf("Optimization Levels:\n");
    printf("  -O0           No optimization (debugging)\n");
    printf("  -O1           Basic optimization\n");
    printf("  -O2           Production (recommended)\n");
    printf("  -O3           Aggressive (may increase size)\n");
    printf("  -Os           Optimize for size\n");
    printf("  -Ofast        Maximum speed (non-standard)\n\n");

    printf("C Standards:\n");
    printf("  -std=c89      ANSI C (C90)\n");
    printf("  -std=c99      C99 standard\n");
    printf("  -std=c11      C11 standard\n");
    printf("  -std=c17      C17 standard (latest)\n\n");

    printf("Security Hardening:\n");
    printf("  -D_FORTIFY_SOURCE=2        Buffer overflow checks\n");
    printf("  -fstack-protector-strong   Stack canaries\n");
    printf("  -fPIE -pie                 Position independent\n");
    printf("  -Wformat-security          Format vulnerabilities\n\n");

    printf("=== Build Configuration Tips ===\n\n");

    printf("Development:\n");
    printf("  • Use -g for debugging symbols\n");
    printf("  • Use -O0 for fast compilation and debugging\n");
    printf("  • Enable all warnings: -Wall -Wextra\n");
    printf("  • Keep assertions enabled (no -DNDEBUG)\n\n");

    printf("Testing:\n");
    printf("  • Use -O2 to catch optimizer-exposed bugs\n");
    printf("  • Add sanitizers (see dynamic_analysis.c)\n");
    printf("  • Use -Werror to enforce zero warnings\n");
    printf("  • Enable extra warnings: -Wconversion, -Wshadow\n\n");

    printf("Production:\n");
    printf("  • Use -O2 or -O3 for performance\n");
    printf("  • Define -DNDEBUG to disable assertions\n");
    printf("  • Add security hardening flags\n");
    printf("  • Strip debug symbols: strip program\n\n");

    printf("Static Analysis:\n");
    printf("  • Enable maximum warnings\n");
    printf("  • Use -fanalyzer (GCC 10+)\n");
    printf("  • Run clang --analyze\n");
    printf("  • Use external tools (cppcheck, splint)\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Compilation Stages:
 *    Preprocessing (-E) → Compilation (-S) → Assembly (-c) → Linking
 *
 *    gcc -E file.c              # Preprocessor only → .i
 *    gcc -S file.c              # Compilation only → .s (assembly)
 *    gcc -c file.c              # Assembly only → .o (object)
 *    gcc file.o -o program      # Linking only → executable
 *
 * 2. Warning Levels:
 *
 *    None:       Minimal warnings (dangerous)
 *    -Wall:      Most important warnings (minimum recommended)
 *    -Wextra:    Additional warnings beyond -Wall
 *    -Wpedantic: Strict ISO C compliance warnings
 *    -Werror:    Convert all warnings to errors
 *
 * 3. Optimization Trade-offs:
 *
 *    -O0: Fast compilation, easy debugging, slow execution
 *    -O1: Balance between compilation speed and performance
 *    -O2: Good performance, reasonable compilation time
 *    -O3: Best performance, slower compilation, larger code
 *    -Os: Small code size, good for embedded systems
 *
 * 4. Debug Builds vs Release Builds:
 *
 *    Debug Build:
 *      gcc -g -O0 -Wall -Wextra file.c -o program_debug
 *
 *    Release Build:
 *      gcc -O2 -DNDEBUG -Wall file.c -o program
 *      strip program  # Remove debug symbols
 *
 * 5. Recommended Flags for Projects:
 *
 *    CFLAGS = -std=c17 -Wall -Wextra -Wpedantic
 *    DEBUGFLAGS = -g -O0 -DDEBUG
 *    RELEASEFLAGS = -O2 -DNDEBUG
 *    SECURITYFLAGS = -D_FORTIFY_SOURCE=2 -fstack-protector-strong
 *
 * 6. GCC vs Clang:
 *
 *    Both support similar flags, but:
 *    - Clang often has better error messages
 *    - GCC may have better optimization for some code
 *    - Test with both compilers if possible
 *
 *    Clang-specific:
 *      -Weverything    # Enable ALL warnings (very strict)
 *      --analyze       # Static analysis
 *
 * 7. Makefile Integration:
 *
 *    CFLAGS := -std=c17 -Wall -Wextra -pedantic
 *
 *    ifeq ($(BUILD),debug)
 *        CFLAGS += -g -O0
 *    else
 *        CFLAGS += -O2 -DNDEBUG
 *    endif
 *
 *    program: main.c
 *        $(CC) $(CFLAGS) $< -o $@
 *
 * 8. Warning Suppression:
 *
 *    Sometimes need to disable specific warnings:
 *
 *    #pragma GCC diagnostic push
 *    #pragma GCC diagnostic ignored "-Wunused-parameter"
 *    void func(int unused_param) { }
 *    #pragma GCC diagnostic pop
 *
 * 9. Cross-Compilation:
 *
 *    arm-linux-gnueabi-gcc -march=armv7-a file.c
 *
 *    Specify:
 *      -march: Target architecture
 *      -mtune: Tune for specific CPU
 *      -mfpu:  Floating point unit
 *
 * 10. Compiler Output Control:
 *
 *     -v          Verbose (show all compilation steps)
 *     -Q          Show enabled optimization options
 *     -ftime-report  Show time spent in compilation phases
 *     -fmem-report   Show memory usage
 *     -save-temps    Keep intermediate files
 */
