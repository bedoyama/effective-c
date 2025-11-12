#include <stdio.h>
#include <stdlib.h>

// Define some feature flags
#define FEATURE_LOGGING 1
#define FEATURE_DEBUG 0
#define VERSION_MAJOR 2

int main(void)
{
    printf("=== Conditional Inclusion ===\n\n");

    printf("Test 1: #ifdef - Check if defined\n");
#ifdef FEATURE_LOGGING
    printf("  ✓ Logging feature is enabled\n");
#else
    printf("  ✗ Logging feature is disabled\n");
#endif
    printf("\n");

    printf("Test 2: #ifndef - Check if NOT defined\n");
#ifndef FEATURE_EXPERIMENTAL
    printf("  ✓ Experimental features are disabled\n");
#else
    printf("  ✓ Experimental features are enabled\n");
#endif
    printf("\n");

    printf("Test 3: #if - Test expression\n");
#if FEATURE_DEBUG
    printf("  ✓ Debug mode is ON\n");
#else
    printf("  ✗ Debug mode is OFF\n");
#endif
    printf("\n");

    printf("Test 4: #if with comparisons\n");
#if VERSION_MAJOR >= 2
    printf("  ✓ Version 2.x or higher detected\n");
#else
    printf("  ✗ Old version detected\n");
#endif
    printf("\n");

    printf("Test 5: #elif - else if chain\n");
#if VERSION_MAJOR == 1
    printf("  Version 1.x\n");
#elif VERSION_MAJOR == 2
    printf("  ✓ Version 2.x (current)\n");
#elif VERSION_MAJOR == 3
    printf("  Version 3.x\n");
#else
    printf("  Unknown version\n");
#endif
    printf("\n");

    printf("Test 6: defined() operator\n");
#if defined(FEATURE_LOGGING) && defined(VERSION_MAJOR)
    printf("  ✓ Both FEATURE_LOGGING and VERSION_MAJOR are defined\n");
#endif
    printf("\n");

    printf("Test 7: Platform detection\n");
#ifdef __linux__
    printf("  Platform: Linux\n");
#elif defined(_WIN32) || defined(_WIN64)
    printf("  Platform: Windows\n");
#elif defined(__APPLE__) && defined(__MACH__)
    printf("  Platform: macOS\n");
#elif defined(__unix__)
    printf("  Platform: Unix-like\n");
#else
    printf("  Platform: Unknown\n");
#endif
    printf("\n");

    printf("Test 8: Compiler detection\n");
#ifdef __GNUC__
    printf("  Compiler: GCC or compatible\n");
    printf("  Version: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(__clang__)
    printf("  Compiler: Clang\n");
#elif defined(_MSC_VER)
    printf("  Compiler: Microsoft Visual C++\n");
#else
    printf("  Compiler: Unknown\n");
#endif
    printf("\n");

    printf("Test 9: Standard version detection\n");
#if __STDC_VERSION__ >= 201112L
    printf("  ✓ C11 or later\n");
#elif __STDC_VERSION__ >= 199901L
    printf("  ✓ C99\n");
#else
    printf("  ✓ C89/C90\n");
#endif
    printf("\n");

    printf("Test 10: Nested conditionals\n");
#ifdef FEATURE_LOGGING
#if VERSION_MAJOR >= 2
    printf("  ✓ Advanced logging available (v2+ with logging)\n");
#else
    printf("  ✓ Basic logging available (v1 with logging)\n");
#endif
#else
    printf("  ✗ No logging available\n");
#endif
    printf("\n");

    printf("=== Common Predefined Macros ===\n");
    printf("__FILE__     = %s\n", __FILE__);
    printf("__LINE__     = %d\n", __LINE__);
    printf("__DATE__     = %s\n", __DATE__);
    printf("__TIME__     = %s\n", __TIME__);
    printf("__STDC__     = %d\n", __STDC__);
#ifdef __STDC_VERSION__
    printf("__STDC_VERSION__ = %ldL\n", __STDC_VERSION__);
#endif
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. #ifdef/#ifndef check if macro is defined (not its value)\n");
    printf("2. #if checks if expression is non-zero\n");
    printf("3. Use #if defined(X) instead of #ifdef X in complex conditions\n");
    printf("4. #elif provides else-if functionality\n");
    printf("5. All conditional blocks must end with #endif\n");
    printf("6. Conditionals are evaluated at preprocessing time\n");
    printf("7. Code inside false conditionals is completely removed\n");

    return EXIT_SUCCESS;
}
