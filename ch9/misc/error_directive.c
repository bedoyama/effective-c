/*
 * #error Directive Demonstration
 *
 * Shows how to use #error to generate compilation errors
 * when required conditions are not met.
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// Example 1: Check for required configuration
// ============================================================================

// Uncomment the next line to see #error in action
// #define FORCE_ERROR_TEST

#ifdef FORCE_ERROR_TEST
#error "FORCE_ERROR_TEST is defined - this is an intentional compilation error"
#endif

// ============================================================================
// Example 2: Version checking
// ============================================================================

#define API_VERSION 3

#if API_VERSION < 2
#error "API_VERSION must be at least 2"
#endif

// ============================================================================
// Example 3: Platform requirements
// ============================================================================

// This code requires a 64-bit platform
// Uncomment to test the error
// #if !defined(__LP64__) && !defined(_WIN64)
//     #error "This code requires a 64-bit platform"
// #endif

// ============================================================================
// Example 4: Mutually exclusive options
// ============================================================================

#define USE_MALLOC 1
// #define USE_POOL   1  // Uncomment to trigger error

#if defined(USE_MALLOC) && defined(USE_POOL)
#error "Cannot use both USE_MALLOC and USE_POOL - choose one"
#endif

// ============================================================================
// Example 5: Require specific compiler
// ============================================================================

// Example: Code that requires GCC extensions
// #ifndef __GNUC__
//     #error "This code requires GCC compiler"
// #endif

// ============================================================================
// Example 6: C standard requirement
// ============================================================================

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
// Uncomment to require C99 or later
// #error "This code requires C99 or later (compile with -std=c99 or -std=c11)"
#endif

int main(void)
{
    printf("=== #error Directive Demonstration ===\n\n");

    printf("Test 1: Purpose of #error\n");
    printf("  ✓ Generate compile-time errors for invalid configurations\n");
    printf("  ✓ Enforce required macros, versions, or platforms\n");
    printf("  ✓ Catch configuration problems early\n\n");

    printf("Test 2: Basic #error syntax\n");
    printf("  #error \"Error message here\"\n");
    printf("  ✓ Stops compilation immediately\n");
    printf("  ✓ Displays the error message\n\n");

    printf("Test 3: Configuration validation\n");
    printf("  API_VERSION = %d\n", API_VERSION);
#if API_VERSION >= 2
    printf("  ✓ API version check passed (>= 2)\n");
#else
    printf("  ✗ Would fail: API_VERSION must be at least 2\n");
#endif
    printf("\n");

    printf("Test 4: Mutually exclusive options\n");
#if defined(USE_MALLOC) && !defined(USE_POOL)
    printf("  ✓ Using malloc for memory allocation\n");
#elif !defined(USE_MALLOC) && defined(USE_POOL)
    printf("  ✓ Using pool allocator\n");
#elif defined(USE_MALLOC) && defined(USE_POOL)
    printf("  ✗ ERROR: Both USE_MALLOC and USE_POOL defined\n");
    printf("  (Would fail with: #error \"Cannot use both...\")\n");
#else
    printf("  ✗ No memory allocator defined\n");
#endif
    printf("\n");

    printf("Test 5: Platform detection\n");
#if defined(__LP64__) || defined(_WIN64)
    printf("  ✓ Running on 64-bit platform\n");
#else
    printf("  ✓ Running on 32-bit platform\n");
    printf("  (Some code might require: #error \"Requires 64-bit\")\n");
#endif
    printf("\n");

    printf("Test 6: Compiler detection\n");
#ifdef __GNUC__
    printf("  ✓ GCC-compatible compiler detected\n");
#else
    printf("  ✓ Non-GCC compiler\n");
    printf("  (Some code might require: #error \"Requires GCC\")\n");
#endif
    printf("\n");

    printf("Test 7: C standard detection\n");
#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 201112L
    printf("  ✓ C11 or later\n");
#elif __STDC_VERSION__ >= 199901L
    printf("  ✓ C99\n");
#else
    printf("  ✓ Pre-C99 standard\n");
#endif
#else
    printf("  ✓ C89/C90\n");
#endif
    printf("\n");

    printf("=== Common Use Cases ===\n\n");

    printf("Use Case 1: Required macro not defined\n");
    printf("  #ifndef API_KEY\n");
    printf("      #error \"API_KEY must be defined\"\n");
    printf("  #endif\n\n");

    printf("Use Case 2: Invalid configuration combination\n");
    printf("  #if defined(OPTION_A) && defined(OPTION_B)\n");
    printf("      #error \"OPTION_A and OPTION_B are mutually exclusive\"\n");
    printf("  #endif\n\n");

    printf("Use Case 3: Unsupported platform\n");
    printf("  #if !defined(__linux__) && !defined(_WIN32)\n");
    printf("      #error \"Unsupported platform\"\n");
    printf("  #endif\n\n");

    printf("Use Case 4: Version too old\n");
    printf("  #if VERSION < 3\n");
    printf("      #error \"VERSION must be at least 3\"\n");
    printf("  #endif\n\n");

    printf("Use Case 5: Feature not available\n");
    printf("  #ifndef _POSIX_C_SOURCE\n");
    printf("      #error \"POSIX features required\"\n");
    printf("  #endif\n\n");

    printf("=== #warning Directive ===\n");
    printf("Similar to #error but doesn't stop compilation:\n");
    printf("  #warning \"This feature is deprecated\"\n");
    printf("  ✓ Generates a warning instead of an error\n");
    printf("  ✓ Compilation continues\n");
    printf("  Note: Not part of C standard, but widely supported\n\n");

    printf("=== Best Practices ===\n");
    printf("1. Use clear, descriptive error messages\n");
    printf("2. Tell user how to fix the problem\n");
    printf("3. Check for #error conditions early in headers\n");
    printf("4. Use #error for invalid configurations\n");
    printf("5. Use #warning for deprecation notices\n");
    printf("6. Combine with #ifdef for conditional checking\n");
    printf("7. Document required macros in comments\n\n");

    printf("=== Testing #error ===\n");
    printf("To see #error in action, uncomment this line at the top:\n");
    printf("  #define FORCE_ERROR_TEST\n");
    printf("Then recompile to see the compilation error.\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. #error Purpose:
 *    - Generate compile-time errors
 *    - Enforce configuration requirements
 *    - Prevent invalid builds
 *    - Catch problems before runtime
 *
 * 2. Syntax:
 *    - #error "message"
 *    - Message is displayed during compilation
 *    - Compilation stops immediately
 *
 * 3. Common Scenarios:
 *    - Missing required macros
 *    - Invalid macro combinations
 *    - Unsupported platforms or compilers
 *    - Version requirements not met
 *    - Deprecated features used
 *
 * 4. Error Message Guidelines:
 *    - Be specific about what's wrong
 *    - Explain how to fix it
 *    - Example: "#error API_KEY not defined. Set -DAPI_KEY=xxx"
 *
 * 5. Conditional Errors:
 *    - Use with #if/#ifdef for smart checking
 *    - Only error when conditions aren't met
 *    - Example:
 *        #ifndef REQUIRED_MACRO
 *            #error "REQUIRED_MACRO must be defined"
 *        #endif
 *
 * 6. #warning:
 *    - Similar to #error but non-fatal
 *    - Generates warning instead
 *    - Compilation continues
 *    - Not part of C standard but widely supported
 *    - Good for deprecation notices
 *
 * 7. Practical Example:
 *    // config.h
 *    #ifndef CONFIG_H
 *    #define CONFIG_H
 *
 *    #ifndef DATABASE_URL
 *        #error "DATABASE_URL must be defined. Compile with -DDATABASE_URL=\"...\""
 *    #endif
 *
 *    #if !defined(USE_MYSQL) && !defined(USE_POSTGRES)
 *        #error "Must define either USE_MYSQL or USE_POSTGRES"
 *    #endif
 *
 *    #endif
 *
 * 8. Testing:
 *    - Temporarily define invalid configurations
 *    - Verify #error triggers as expected
 *    - Test with different compilers/platforms
 *
 * 9. When to Use:
 *    - Configuration validation
 *    - Platform/compiler requirements
 *    - API version checking
 *    - Mutually exclusive options
 *    - Required feature detection
 *
 * 10. Related Directives:
 *     - #error: Fatal compile error
 *     - #warning: Non-fatal warning (compiler-specific)
 *     - #pragma message: Info message (compiler-specific)
 */
