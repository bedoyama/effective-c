#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== Character Types and Operations ===\n\n");

    // Test 1: Basic character types
    printf("Test 1: Character types and representation\n");
    {
        char c1 = 'A';
        char c2 = 65;   // ASCII value of 'A'
        char c3 = 0x41; // Hexadecimal value of 'A'

        printf("c1 = '%c' (character literal)\n", c1);
        printf("c2 = '%c' (decimal value: %d)\n", c2, c2);
        printf("c3 = '%c' (hexadecimal value: 0x%X)\n", c3, c3);
        printf("All three represent the same character: %s\n\n", (c1 == c2 && c2 == c3) ? "YES" : "NO");
    }

    // Test 2: Character classification functions
    printf("Test 2: Character classification (ctype.h)\n");
    {
        char test_chars[] = {'A', 'z', '5', ' ', '\n', '!', '\0'};
        printf("Char  | isalpha | isdigit | isalnum | isspace | isupper | islower | ispunct\n");
        printf("------|---------|---------|---------|---------|---------|---------|--------\n");

        for (size_t i = 0; test_chars[i] != '\0'; i++)
        {
            char c = test_chars[i];
            char display = (c == '\n') ? 'n' : (c == ' ') ? '_'
                                                          : c;
            printf("  %c   |    %d    |    %d    |    %d    |    %d    |    %d    |    %d    |    %d\n",
                   display,
                   isalpha(c) ? 1 : 0,
                   isdigit(c) ? 1 : 0,
                   isalnum(c) ? 1 : 0,
                   isspace(c) ? 1 : 0,
                   isupper(c) ? 1 : 0,
                   islower(c) ? 1 : 0,
                   ispunct(c) ? 1 : 0);
        }
        printf("\n");
    }

    // Test 3: Character conversion
    printf("Test 3: Character case conversion\n");
    {
        char lower = 'a';
        char upper = 'Z';
        char digit = '5';

        printf("Original: '%c' -> toupper: '%c'\n", lower, toupper(lower));
        printf("Original: '%c' -> tolower: '%c'\n", upper, tolower(upper));
        printf("Original: '%c' -> toupper: '%c' (no change)\n", digit, toupper(digit));
        printf("Original: '%c' -> tolower: '%c' (no change)\n\n", digit, tolower(digit));
    }

    // Test 4: Escape sequences
    printf("Test 4: Escape sequences\n");
    {
        printf("Newline: line1\\nline2\n");
        printf("line1\nline2\n");
        printf("\nTab: word1\\tword2\n");
        printf("word1\tword2\n");
        printf("\nBackslash: \\\\\n");
        printf("Single quote: \\'\n");
        printf("Double quote: \\\"\n");
        printf("Question mark: \\?\n");
        printf("Backspace: abc\\bdef\n");
        printf("abc\bdef\n");
        printf("Carriage return: 12345\\rabcd\n");
        printf("12345\rabcd\n\n");
    }

    // Test 5: Character arithmetic
    printf("Test 5: Character arithmetic\n");
    {
        char c = 'A';
        printf("Starting with: '%c' (ASCII %d)\n", c, c);
        printf("c + 1 = '%c' (ASCII %d)\n", c + 1, c + 1);
        printf("c + 25 = '%c' (ASCII %d)\n", c + 25, c + 25);

        char digit = '0';
        printf("\nDigit character: '%c' (ASCII %d)\n", digit, digit);
        printf("digit + 5 = '%c' (ASCII %d)\n", digit + 5, digit + 5);
        printf("Numeric value: %d\n\n", digit - '0');
    }

    // Test 6: Character arrays vs single characters
    printf("Test 6: Character vs character array\n");
    {
        char single = 'A';
        char array[] = "A"; // Actually "A\0" - 2 bytes

        printf("Single char 'A': size = %zu byte\n", sizeof(single));
        printf("Char array \"A\": size = %zu bytes (includes \\0)\n", sizeof(array));
        printf("single = '%c'\n", single);
        printf("array = \"%s\"\n\n", array);
    }

    // Test 7: Control characters
    printf("Test 7: Control characters\n");
    {
        printf("NULL character: '\\0' (ASCII %d)\n", '\0');
        printf("Bell character: '\\a' (ASCII %d) ", '\a');
        printf("<-- You might hear a beep\n");
        printf("Form feed: '\\f' (ASCII %d)\n", '\f');
        printf("Vertical tab: '\\v' (ASCII %d)\n\n", '\v');
    }

    // Test 8: Wide characters (preview)
    printf("Test 8: Character size and types\n");
    {
        char c = 'A';
        signed char sc = 'B';
        unsigned char uc = 'C';

        printf("char:          '%c' (size: %zu byte)\n", c, sizeof(c));
        printf("signed char:   '%c' (size: %zu byte)\n", sc, sizeof(sc));
        printf("unsigned char: '%c' (size: %zu byte)\n", uc, sizeof(uc));
        printf("\nNote: char may be signed or unsigned (implementation-defined)\n\n");
    }

    // Test 9: Converting characters to numeric values
    printf("Test 9: Character to numeric conversion\n");
    {
        char digits[] = "0123456789";
        printf("Converting digit characters to integers:\n");
        for (size_t i = 0; digits[i] != '\0'; i++)
        {
            int value = digits[i] - '0';
            printf("'%c' -> %d  ", digits[i], value);
            if ((i + 1) % 5 == 0)
                printf("\n");
        }
        printf("\n");
    }

    // Test 10: Hexadecimal digit checking
    printf("Test 10: Hexadecimal digit validation\n");
    {
        char test[] = "0 5 9 A F G a f z";
        printf("Testing characters: %s\n", test);
        printf("Hexadecimal digits: ");
        for (size_t i = 0; test[i] != '\0'; i++)
        {
            if (isxdigit(test[i]))
            {
                printf("%c ", test[i]);
            }
        }
        printf("\n");
    }

    printf("\n=== Important Notes ===\n");
    printf("1. char is an integer type (typically 8 bits)\n");
    printf("2. Characters enclosed in single quotes: 'A'\n");
    printf("3. Character values are ASCII codes (0-127 for standard ASCII)\n");
    printf("4. Extended ASCII uses 0-255 (implementation-dependent)\n");
    printf("5. Use <ctype.h> functions for portable character testing\n");
    printf("6. toupper/tolower only affect letters\n");
    printf("7. Escape sequences start with backslash (\\)\n");
    printf("8. '0' has ASCII value 48, not 0\n");

    return EXIT_SUCCESS;
}
