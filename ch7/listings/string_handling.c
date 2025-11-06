#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== String-Handling Functions ===\n\n");

    // Test 1: strlen - string length
    printf("Test 1: strlen() - string length\n");
    {
        char *str = "Hello, World!";
        printf("String: \"%s\"\n", str);
        printf("Length: %zu characters\n\n", strlen(str));
    }

    // Test 2: strcpy - string copy
    printf("Test 2: strcpy() - copy string\n");
    {
        char source[] = "Source string";
        char dest[50];

        strcpy(dest, source);
        printf("Source: \"%s\"\n", source);
        printf("Dest:   \"%s\"\n\n", dest);
    }

    // Test 3: strncpy - bounded string copy
    printf("Test 3: strncpy() - bounded copy\n");
    {
        char source[] = "Hello, World!";
        char dest[20];

        strncpy(dest, source, sizeof(dest) - 1);
        dest[sizeof(dest) - 1] = '\0'; // Ensure null-termination
        printf("Source: \"%s\"\n", source);
        printf("Dest:   \"%s\"\n\n", dest);
    }

    // Test 4: strcat - string concatenation
    printf("Test 4: strcat() - concatenate strings\n");
    {
        char dest[50] = "Hello";
        char *src = ", World!";

        printf("Before: \"%s\"\n", dest);
        strcat(dest, src);
        printf("After:  \"%s\"\n\n", dest);
    }

    // Test 5: strncat - bounded concatenation
    printf("Test 5: strncat() - bounded concatenation\n");
    {
        char dest[50] = "Hello";
        char *src = ", World!";

        printf("Before: \"%s\"\n", dest);
        strncat(dest, src, 7); // Only add first 7 chars
        printf("After:  \"%s\"\n\n", dest);
    }

    // Test 6: strcmp - string comparison
    printf("Test 6: strcmp() - compare strings\n");
    {
        char *str1 = "Apple";
        char *str2 = "Apple";
        char *str3 = "Banana";
        char *str4 = "Aardvark";

        printf("strcmp(\"%s\", \"%s\") = %d (equal)\n", str1, str2, strcmp(str1, str2));
        printf("strcmp(\"%s\", \"%s\") = %d (str1 < str3)\n", str1, str3, strcmp(str1, str3));
        printf("strcmp(\"%s\", \"%s\") = %d (str1 > str4)\n\n", str1, str4, strcmp(str1, str4));
    }

    // Test 7: strncmp - bounded comparison
    printf("Test 7: strncmp() - compare n characters\n");
    {
        char *str1 = "Hello, World!";
        char *str2 = "Hello, Earth!";

        printf("Full comparison:  strcmp(\"%s\", \"%s\") = %d\n", str1, str2, strcmp(str1, str2));
        printf("First 5 chars:    strncmp(\"%s\", \"%s\", 5) = %d\n", str1, str2, strncmp(str1, str2, 5));
        printf("First 7 chars:    strncmp(\"%s\", \"%s\", 7) = %d\n\n", str1, str2, strncmp(str1, str2, 7));
    }

    // Test 8: strchr - find character
    printf("Test 8: strchr() - find character in string\n");
    {
        char *str = "Hello, World!";
        char ch = 'o';

        char *result = strchr(str, ch);
        if (result)
        {
            printf("String: \"%s\"\n", str);
            printf("Found '%c' at position %ld\n", ch, result - str);
            printf("Remainder: \"%s\"\n\n", result);
        }
    }

    // Test 9: strrchr - find last occurrence
    printf("Test 9: strrchr() - find last occurrence\n");
    {
        char *str = "Hello, World!";
        char ch = 'o';

        char *first = strchr(str, ch);
        char *last = strrchr(str, ch);

        printf("String: \"%s\"\n", str);
        printf("First '%c' at position %ld\n", ch, first - str);
        printf("Last '%c' at position %ld\n\n", ch, last - str);
    }

    // Test 10: strstr - find substring
    printf("Test 10: strstr() - find substring\n");
    {
        char *str = "The quick brown fox jumps over the lazy dog";
        char *sub = "fox";

        char *result = strstr(str, sub);
        if (result)
        {
            printf("String: \"%s\"\n", str);
            printf("Found \"%s\" at position %ld\n", sub, result - str);
            printf("Remainder: \"%s\"\n\n", result);
        }
    }

    // Test 11: strtok - tokenize string
    printf("Test 11: strtok() - tokenize string\n");
    {
        char str[] = "apple,banana,cherry,date"; // Must be modifiable
        char *delim = ",";
        char *token;

        printf("Original: \"%s\"\n", "apple,banana,cherry,date");
        printf("Tokens:\n");

        token = strtok(str, delim);
        while (token != NULL)
        {
            printf("  \"%s\"\n", token);
            token = strtok(NULL, delim);
        }
        printf("\n");
    }

    // Test 12: strcspn and strspn
    printf("Test 12: strcspn() and strspn()\n");
    {
        char *str = "hello123world";

        size_t letters = strcspn(str, "0123456789");
        size_t digits = strspn(str + letters, "0123456789");

        printf("String: \"%s\"\n", str);
        printf("Letters before digit: %zu\n", letters);
        printf("Consecutive digits: %zu\n\n", digits);
    }

    // Test 13: strpbrk - find any character from set
    printf("Test 13: strpbrk() - find any character from set\n");
    {
        char *str = "Hello, World!";
        char *vowels = "aeiouAEIOU";

        char *result = strpbrk(str, vowels);
        if (result)
        {
            printf("String: \"%s\"\n", str);
            printf("First vowel '%c' at position %ld\n\n", *result, result - str);
        }
    }

    // Test 14: memcpy and memmove
    printf("Test 14: memcpy() and memmove()\n");
    {
        char src[] = "Source data";
        char dest1[20];
        char dest2[20] = "Original content";

        memcpy(dest1, src, strlen(src) + 1);
        printf("memcpy result: \"%s\"\n", dest1);

        // memmove handles overlapping memory
        char overlap[30] = "0123456789";
        memmove(overlap + 2, overlap, 8);
        printf("memmove overlap: \"%s\"\n\n", overlap);
    }

    // Test 15: memset - fill memory
    printf("Test 15: memset() - fill memory\n");
    {
        char buffer[20];

        memset(buffer, 'A', sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
        printf("Filled with 'A': \"%s\"\n", buffer);

        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        printf("Cleared: \"%s\" (empty)\n\n", buffer);
    }

    // Test 16: memcmp - memory comparison
    printf("Test 16: memcmp() - compare memory\n");
    {
        char str1[] = "Hello";
        char str2[] = "Hello";
        char str3[] = "World";

        printf("memcmp(str1, str2, 5) = %d\n", memcmp(str1, str2, 5));
        printf("memcmp(str1, str3, 5) = %d\n\n", memcmp(str1, str3, 5));
    }

    // Test 17: Safe string handling pattern
    printf("Test 17: Safe string handling pattern\n");
    {
        char source[] = "This is a longer string that needs to be copied safely";
        char dest[20];
        size_t dest_size = sizeof(dest);

        // Safe copy pattern
        strncpy(dest, source, dest_size - 1);
        dest[dest_size - 1] = '\0';

        printf("Source: \"%s\"\n", source);
        printf("Dest (truncated): \"%s\"\n", dest);
        printf("Safely copied with guaranteed null-termination\n\n");
    }

    printf("=== Important Notes ===\n");
    printf("1. strcpy/strcat are UNSAFE - no bounds checking\n");
    printf("2. Use strncpy/strncat for bounded operations\n");
    printf("3. Always ensure null-termination with strncpy\n");
    printf("4. strcmp returns: 0 (equal), <0 (str1<str2), >0 (str1>str2)\n");
    printf("5. strtok modifies the original string\n");
    printf("6. strchr/strstr return pointer to match or NULL\n");
    printf("7. memcpy does NOT check for overlap\n");
    printf("8. memmove handles overlapping memory safely\n");
    printf("9. memset fills memory with a single byte value\n");
    printf("10. Always validate buffer sizes to prevent overflow\n");

    printf("\n=== Safer Alternatives ===\n");
    printf("• snprintf() - safer than strcpy/strcat\n");
    printf("• strlcpy() - BSD function (not standard C)\n");
    printf("• strlcat() - BSD function (not standard C)\n");
    printf("• strdup() - POSIX function (allocates memory)\n");

    return EXIT_SUCCESS;
}
