#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Provide strlcpy and strlcat implementations for portability
// These are BSD functions not in standard C but widely available
#ifndef __has_strlcpy
size_t strlcpy(char *dst, const char *src, size_t size)
{
    size_t src_len = strlen(src);
    if (size == 0)
    {
        return src_len;
    }
    size_t copy_len = (src_len < size - 1) ? src_len : size - 1;
    memcpy(dst, src, copy_len);
    dst[copy_len] = '\0';
    return src_len;
}

size_t strlcat(char *dst, const char *src, size_t size)
{
    size_t dst_len = strlen(dst);
    size_t src_len = strlen(src);
    if (dst_len >= size)
    {
        return size + src_len;
    }
    size_t copy_len = size - dst_len - 1;
    if (src_len < copy_len)
    {
        copy_len = src_len;
    }
    memcpy(dst + dst_len, src, copy_len);
    dst[dst_len + copy_len] = '\0';
    return dst_len + src_len;
}
#endif

int main(void)
{
    printf("=== Safe vs Unsafe String Operations ===\n\n");

    // ========================================
    // 1. FORMAT STRING: sprintf vs snprintf
    // ========================================
    printf("1. FORMAT STRING: sprintf (UNSAFE) vs snprintf (SAFE)\n");
    printf("Standard C: snprintf is C99\n");
    printf("---------------------------------------------------\n\n");

    // UNSAFE: sprintf - no bounds checking
    printf("UNSAFE: sprintf()\n");
    {
        char buffer[20];
        int value = 42;
        const char *name = "Alice";

        // This is SAFE because we know the output size
        sprintf(buffer, "Value: %d", value);
        printf("  Safe usage: \"%s\"\n", buffer);

        // This is DANGEROUS - can overflow!
        // sprintf(buffer, "Name: %s, Number: %d, Extra: %s", name, value, "This is too long");
        printf("  ✗ Can overflow buffer with long input\n");
        printf("  ✗ No way to limit output size\n\n");
    }

    // SAFE: snprintf - bounds checking
    printf("SAFE: snprintf()\n");
    {
        char buffer[20];
        int value = 42;
        const char *name = "Alice";

        // Safe: snprintf limits output
        int written = snprintf(buffer, sizeof(buffer), "Name: %s, Num: %d", name, value);
        printf("  Output: \"%s\"\n", buffer);
        printf("  Wanted to write: %d chars\n", written);
        printf("  Buffer size: %zu chars\n", sizeof(buffer));
        printf("  ✓ Guaranteed null-termination\n");
        printf("  ✓ Returns number of chars that would be written\n");
        printf("  ✓ Never overflows buffer\n\n");
    }

    // ========================================
    // 2. COPY STRING: strcpy vs strlcpy
    // ========================================
    printf("2. COPY STRING: strcpy (UNSAFE) vs strlcpy (SAFE)\n");
    printf("Standard C: strlcpy is NOT standard (BSD extension)\n");
    printf("---------------------------------------------------\n\n");

    // UNSAFE: strcpy - no bounds checking
    printf("UNSAFE: strcpy()\n");
    {
        char buffer[10];
        const char *safe_src = "Hello";
        const char *unsafe_src = "This string is way too long for the buffer";

        // Safe usage
        strcpy(buffer, safe_src);
        printf("  Safe: \"%s\"\n", buffer);

        // DANGEROUS - would overflow!
        // strcpy(buffer, unsafe_src); // DON'T DO THIS!
        printf("  ✗ No bounds checking\n");
        printf("  ✗ Buffer overflow if source > destination\n");
        printf("  ✗ Undefined behavior on overflow\n\n");
    }

    // SAFE: strlcpy - bounds checking
    printf("SAFE: strlcpy()\n");
    {
        char buffer[10];
        const char *short_src = "Hi";
        const char *long_src = "This string is way too long";

        // Short string
        size_t result1 = strlcpy(buffer, short_src, sizeof(buffer));
        printf("  Short string: \"%s\"\n", buffer);
        printf("    Source length: %zu, copied successfully\n", result1);

        // Long string - safely truncated
        size_t result2 = strlcpy(buffer, long_src, sizeof(buffer));
        printf("  Long string: \"%s\"\n", buffer);
        printf("    Source length: %zu, truncated to fit\n", result2);
        printf("  ✓ Guaranteed null-termination\n");
        printf("  ✓ Returns source length (can detect truncation)\n");
        printf("  ✓ Never overflows buffer\n\n");
    }

    // Standard C alternative: strncpy (with caution)
    printf("Standard C alternative: strncpy() + manual null termination\n");
    {
        char buffer[10];
        const char *src = "This is long";

        strncpy(buffer, src, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0'; // Must manually ensure null-termination!
        printf("  Result: \"%s\"\n", buffer);
        printf("  ⚠ Must manually add null terminator\n");
        printf("  ⚠ Doesn't return useful information\n\n");
    }

    // ========================================
    // 3. CONCATENATE STRING: strcat vs strlcat
    // ========================================
    printf("3. CONCATENATE STRING: strcat (UNSAFE) vs strlcat (SAFE)\n");
    printf("Standard C: strlcat is NOT standard (BSD extension)\n");
    printf("---------------------------------------------------\n\n");

    // UNSAFE: strcat - no bounds checking
    printf("UNSAFE: strcat()\n");
    {
        char buffer[20] = "Hello";
        const char *safe_add = " Hi";
        const char *unsafe_add = " This is way too long to concatenate";

        // Safe usage
        strcat(buffer, safe_add);
        printf("  Safe: \"%s\"\n", buffer);

        // DANGEROUS - would overflow!
        // strcat(buffer, unsafe_add); // DON'T DO THIS!
        printf("  ✗ No bounds checking\n");
        printf("  ✗ Must manually track remaining space\n");
        printf("  ✗ Buffer overflow if combined length > buffer size\n\n");
    }

    // SAFE: strlcat - bounds checking
    printf("SAFE: strlcat()\n");
    {
        char buffer1[20] = "Hello";
        char buffer2[20] = "Hello";
        const char *short_add = " World";
        const char *long_add = " This is a very long string to add";

        // Short concatenation
        size_t result1 = strlcat(buffer1, short_add, sizeof(buffer1));
        printf("  Short concat: \"%s\"\n", buffer1);
        printf("    Total length would be: %zu\n", result1);

        // Long concatenation - safely truncated
        size_t result2 = strlcat(buffer2, long_add, sizeof(buffer2));
        printf("  Long concat: \"%s\"\n", buffer2);
        printf("    Total length would be: %zu (truncated)\n", result2);
        printf("  ✓ Guaranteed null-termination\n");
        printf("  ✓ Returns final string length (can detect truncation)\n");
        printf("  ✓ Never overflows buffer\n\n");
    }

    // Standard C alternative: strncat (with caution)
    printf("Standard C alternative: strncat()\n");
    {
        char buffer[20] = "Hello";
        const char *add = " World!!!";

        strncat(buffer, add, sizeof(buffer) - strlen(buffer) - 1);
        printf("  Result: \"%s\"\n", buffer);
        printf("  ⚠ Must calculate remaining space manually\n");
        printf("  ⚠ Third parameter is max chars to append, not buffer size\n\n");
    }

    // ========================================
    // 4. READ LINE: gets vs fgets
    // ========================================
    printf("4. READ LINE: gets (UNSAFE) vs fgets (SAFE)\n");
    printf("Standard C: fgets is standard, gets removed in C11\n");
    printf("---------------------------------------------------\n\n");

    // UNSAFE: gets - NEVER USE THIS!
    printf("UNSAFE: gets() - REMOVED from C11!\n");
    {
        // char buffer[10];
        // gets(buffer); // NEVER DO THIS! Removed from C11

        printf("  ✗ NO bounds checking whatsoever\n");
        printf("  ✗ ALWAYS vulnerable to buffer overflow\n");
        printf("  ✗ Removed from C11 standard\n");
        printf("  ✗ Will cause compiler warnings/errors\n");
        printf("  ⚠ NEVER USE gets()!\n\n");
    }

    // SAFE: fgets - bounds checking
    printf("SAFE: fgets()\n");
    {
        printf("  Demonstration (reading from simulated input):\n");
        printf("  char buffer[50];\n");
        printf("  if (fgets(buffer, sizeof(buffer), stdin)) {\n");
        printf("      // Successfully read line\n");
        printf("  }\n\n");

        printf("  ✓ Requires buffer size parameter\n");
        printf("  ✓ Reads at most (size-1) characters\n");
        printf("  ✓ Guaranteed null-termination\n");
        printf("  ✓ Includes newline if present (can be removed)\n");
        printf("  ✓ Returns NULL on error or EOF\n\n");

        // Example with string stream
        printf("  Example: Reading from a string:\n");
        FILE *fake_input = fmemopen("Test line\nSecond line\n", 24, "r");
        if (fake_input)
        {
            char buffer[50];
            if (fgets(buffer, sizeof(buffer), fake_input))
            {
                // Remove newline if present
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n')
                {
                    buffer[len - 1] = '\0';
                }
                printf("    Read: \"%s\"\n", buffer);
            }
            fclose(fake_input);
        }
        printf("\n");
    }

    // ========================================
    // SUMMARY TABLE
    // ========================================
    printf("=== SUMMARY TABLE ===\n\n");
    printf("Task              | Unsafe (Old) | Safe (Modern)    | Standard C?\n");
    printf("------------------|--------------|------------------|-------------\n");
    printf("Format String     | sprintf      | snprintf         | Yes (C99)\n");
    printf("Copy String       | strcpy       | strlcpy          | No (BSD)\n");
    printf("Concatenate       | strcat       | strlcat          | No (BSD)\n");
    printf("Read Line         | gets         | fgets            | Yes\n");
    printf("\n");

    printf("=== BEST PRACTICES ===\n");
    printf("1. ALWAYS use bounds-checked functions\n");
    printf("2. snprintf: Use instead of sprintf (standard C99)\n");
    printf("3. strlcpy/strlcat: Use if available, or implement them\n");
    printf("4. fgets: ALWAYS use instead of gets\n");
    printf("5. Check return values to detect truncation\n");
    printf("6. Always ensure null-termination\n");
    printf("7. Validate buffer sizes before operations\n");
    printf("8. Use sizeof() not strlen() for buffer size\n");

    printf("\n=== WHY THESE FUNCTIONS ARE UNSAFE ===\n");
    printf("• sprintf: No way to specify buffer size\n");
    printf("• strcpy: No way to limit bytes copied\n");
    printf("• strcat: No way to limit bytes appended\n");
    printf("• gets: NO buffer size parameter at all!\n");

    printf("\n=== MODERN ALTERNATIVES (C11+) ===\n");
    printf("• sprintf_s (Windows/C11 Annex K)\n");
    printf("• strcpy_s (Windows/C11 Annex K)\n");
    printf("• strcat_s (Windows/C11 Annex K)\n");
    printf("• gets_s (C11 Annex K - but fgets still preferred)\n");
    printf("Note: Annex K functions are optional and not widely implemented\n");

    return EXIT_SUCCESS;
}
