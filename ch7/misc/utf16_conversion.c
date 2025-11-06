#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

// Alternative implementation using wide characters (wchar_t)
// Note: <uchar.h> and char16_t are C11 features not available on all systems
// This version uses mbstowcs() which is more widely supported

int main(void)
{
    // Set locale to support UTF-8
    setlocale(LC_ALL, "en_US.UTF-8");

    // Original UTF-8 string
    char input[] = "I ♥ C!";
    printf("Original UTF-8 string: %s\n", input);
    printf("UTF-8 byte length: %zu bytes\n", strlen(input));

    // Show UTF-8 byte representation
    printf("UTF-8 bytes: [ ");
    for (size_t i = 0; i < strlen(input); i++)
    {
        printf("%#x ", (unsigned char)input[i]);
    }
    printf("]\n\n");

    // Convert to wide characters
    size_t input_len = strlen(input);
    wchar_t output[input_len + 1];
    mbstate_t state = {0};

    // Convert multibyte string to wide character string
    size_t result = mbstowcs(output, input, input_len + 1);

    if (result == (size_t)-1)
    {
        fprintf(stderr, "Error: Invalid multibyte sequence\n");
        return EXIT_FAILURE;
    }

    printf("Converted to wide characters:\n");
    printf("Number of wide characters: %zu\n", result);
    printf("Wide character values: [ ");
    for (size_t i = 0; i < result; i++)
    {
        printf("%#x ", (unsigned int)output[i]);
    }
    printf("]\n\n");

    // Display each character
    printf("Character breakdown:\n");
    for (size_t i = 0; i < result; i++)
    {
        printf("  wchar[%zu] = %#x", i, (unsigned int)output[i]);
        if (output[i] < 128)
        {
            printf(" ('%c')", (char)output[i]);
        }
        else
        {
            printf(" ('%lc')", (wint_t)output[i]);
        }
        printf("\n");
    }

    printf("\n=== Notes ===\n");
    printf("• This uses wchar_t instead of char16_t (more portable)\n");
    printf("• wchar_t size: %zu bytes\n", sizeof(wchar_t));
    printf("• On macOS/Linux, wchar_t is typically 4 bytes (UTF-32)\n");
    printf("• On Windows, wchar_t is 2 bytes (UTF-16)\n");
    printf("• For true UTF-16, use <uchar.h> and char16_t (C11)\n");
    printf("• The heart symbol ♥ is U+2665 in Unicode\n");

    return EXIT_SUCCESS;
}
