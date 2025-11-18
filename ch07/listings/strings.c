#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== String Fundamentals ===\n\n");

    // Test 1: String literals
    printf("Test 1: String literals\n");
    {
        char *str1 = "Hello, World!";
        const char *str2 = "Hello, World!"; // Preferred: const

        printf("str1: \"%s\"\n", str1);
        printf("str2: \"%s\"\n", str2);
        printf("Length: %zu characters\n", strlen(str1));
        printf("Memory: %zu bytes (includes null terminator)\n\n", strlen(str1) + 1);
    }

    // Test 2: Character arrays as strings
    printf("Test 2: Character arrays\n");
    {
        char str1[] = "Hello";                          // Array initialized with string
        char str2[20] = "Hello";                        // Larger array
        char str3[6] = {'H', 'e', 'l', 'l', 'o', '\0'}; // Manual initialization

        printf("str1: \"%s\" (size: %zu bytes)\n", str1, sizeof(str1));
        printf("str2: \"%s\" (size: %zu bytes)\n", str2, sizeof(str2));
        printf("str3: \"%s\" (size: %zu bytes)\n\n", str3, sizeof(str3));
    }

    // Test 3: String initialization
    printf("Test 3: String initialization methods\n");
    {
        char s1[] = "Automatic size";
        char s2[50] = "Fixed size";
        char s3[10] = {'T', 'e', 's', 't', '\0'};
        char s4[20] = {0}; // All zeros

        printf("s1: \"%s\"\n", s1);
        printf("s2: \"%s\"\n", s2);
        printf("s3: \"%s\"\n", s3);
        printf("s4: \"%s\" (empty string)\n\n", s4);
    }

    // Test 4: Null terminator importance
    printf("Test 4: Null terminator (\\0)\n");
    {
        char good[6] = "Hello";                  // Automatically adds \0
        char bad[5] = {'H', 'e', 'l', 'l', 'o'}; // No \0 - DANGEROUS!

        printf("Good string (with \\0): \"%s\"\n", good);
        printf("String length: %zu\n", strlen(good));
        printf("\nBad string (no \\0): May print garbage after \"Hello\"\n");
        printf("IMPORTANT: Always ensure strings are null-terminated!\n\n");
    }

    // Test 5: String pointers vs arrays
    printf("Test 5: String pointers vs arrays\n");
    {
        char array[] = "Array";
        char *pointer = "Pointer";

        printf("Array string: \"%s\" (modifiable)\n", array);
        printf("Pointer string: \"%s\" (points to read-only memory)\n", pointer);
        printf("\nArray size: %zu bytes\n", sizeof(array));
        printf("Pointer size: %zu bytes (size of pointer itself)\n\n", sizeof(pointer));

        // Can modify array
        array[0] = 'a';
        printf("Modified array: \"%s\"\n", array);

        // Cannot modify pointer to string literal (undefined behavior)
        // pointer[0] = 'p'; // DON'T DO THIS!
        printf("String literal should NOT be modified\n\n");
    }

    // Test 6: Empty strings
    printf("Test 6: Empty strings\n");
    {
        char empty1[] = "";
        char empty2[10] = "";
        char *empty3 = "";

        printf("empty1: \"%s\" (length: %zu)\n", empty1, strlen(empty1));
        printf("empty2: \"%s\" (length: %zu)\n", empty2, strlen(empty2));
        printf("empty3: \"%s\" (length: %zu)\n\n", empty3, strlen(empty3));
    }

    // Test 7: Multi-line strings
    printf("Test 7: Multi-line string literals\n");
    {
        char *multiline1 = "This is a long string "
                           "that spans multiple lines "
                           "in the source code.";

        char *multiline2 = "Line 1\n"
                           "Line 2\n"
                           "Line 3";

        printf("Concatenated: %s\n\n", multiline1);
        printf("With newlines:\n%s\n\n", multiline2);
    }

    // Test 8: String comparison (preview)
    printf("Test 8: String comparison\n");
    {
        char str1[] = "Apple";
        char str2[] = "Apple";
        char str3[] = "Banana";

        printf("str1: \"%s\"\n", str1);
        printf("str2: \"%s\"\n", str2);
        printf("str3: \"%s\"\n", str3);

        printf("\nDirect comparison (str1 == str2): %s\n", (str1 == str2) ? "true" : "false");
        printf("This compares ADDRESSES, not contents!\n");

        printf("\nCorrect comparison (strcmp):\n");
        printf("strcmp(str1, str2) = %d (equal)\n", strcmp(str1, str2));
        printf("strcmp(str1, str3) = %d (str1 < str3)\n\n", strcmp(str1, str3));
    }

    // Test 9: String length vs array size
    printf("Test 9: String length vs array size\n");
    {
        char buffer[100] = "Hello";

        printf("String: \"%s\"\n", buffer);
        printf("strlen(buffer): %zu (actual string length)\n", strlen(buffer));
        printf("sizeof(buffer): %zu (total array size)\n", sizeof(buffer));
        printf("Unused space: %zu bytes\n\n", sizeof(buffer) - strlen(buffer) - 1);
    }

    // Test 10: Character access
    printf("Test 10: Accessing individual characters\n");
    {
        char str[] = "Programming";

        printf("String: \"%s\"\n", str);
        printf("Characters: ");
        for (size_t i = 0; i < strlen(str); i++)
        {
            printf("%c ", str[i]);
        }
        printf("\n");

        printf("ASCII values: ");
        for (size_t i = 0; i < strlen(str); i++)
        {
            printf("%d ", str[i]);
        }
        printf("\n\n");
    }

    // Test 11: String arrays (array of strings)
    printf("Test 11: Array of strings\n");
    {
        char *fruits[] = {"Apple", "Banana", "Cherry", "Date"};
        size_t count = sizeof(fruits) / sizeof(fruits[0]);

        printf("Fruits:\n");
        for (size_t i = 0; i < count; i++)
        {
            printf("  %zu: %s\n", i, fruits[i]);
        }
        printf("\n");
    }

    // Test 12: 2D character array
    printf("Test 12: 2D character array\n");
    {
        char colors[][10] = {"Red", "Green", "Blue", "Yellow"};
        size_t count = sizeof(colors) / sizeof(colors[0]);

        printf("Colors:\n");
        for (size_t i = 0; i < count; i++)
        {
            printf("  %zu: %s (uses %zu/%zu bytes)\n", i, colors[i], strlen(colors[i]) + 1, sizeof(colors[i]));
        }
        printf("\n");
    }

    printf("=== Important Notes ===\n");
    printf("1. Strings are arrays of characters ending with '\\0'\n");
    printf("2. String literals are stored in read-only memory\n");
    printf("3. Use const char* for string literals\n");
    printf("4. Always ensure null-termination\n");
    printf("5. strlen() gives character count (excluding \\0)\n");
    printf("6. sizeof() gives total memory size (including \\0)\n");
    printf("7. Never compare strings with == (compares addresses)\n");
    printf("8. Use strcmp() for string comparison\n");
    printf("9. String literals can be concatenated at compile time\n");
    printf("10. Buffer overflow is a common and dangerous error\n");

    return EXIT_SUCCESS;
}
