#include <errno.h>
#include <iconv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GNU libiconv example for macOS
// libiconv is included with macOS by default
// Compile: gcc -o program program.c
// (no need for -liconv on macOS, it's in the system)

int main(void)
{
    printf("=== GNU libiconv Character Encoding Conversion ===\n\n");

    // Test 1: UTF-8 to UTF-16
    printf("Test 1: UTF-8 to UTF-16 conversion\n");
    {
        char input[] = "Hello, World! ♥";
        size_t input_len = strlen(input);
        printf("Input (UTF-8): %s\n", input);
        printf("Input length: %zu bytes\n", input_len);

        // Allocate output buffer (UTF-16 may need 2x space)
        size_t output_size = input_len * 4;
        char *output = malloc(output_size);
        if (!output)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        // Create conversion descriptor
        iconv_t cd = iconv_open("UTF-16LE", "UTF-8");
        if (cd == (iconv_t)-1)
        {
            perror("iconv_open failed");
            free(output);
            return EXIT_FAILURE;
        }

        // Prepare pointers
        char *in_ptr = input;
        char *out_ptr = output;
        size_t in_left = input_len;
        size_t out_left = output_size;

        // Perform conversion
        size_t result = iconv(cd, &in_ptr, &in_left, &out_ptr, &out_left);
        if (result == (size_t)-1)
        {
            perror("iconv conversion failed");
            iconv_close(cd);
            free(output);
            return EXIT_FAILURE;
        }

        size_t output_len = output_size - out_left;
        printf("Output (UTF-16LE): %zu bytes\n", output_len);
        printf("UTF-16LE bytes: [ ");
        for (size_t i = 0; i < output_len; i++)
        {
            printf("%02x ", (unsigned char)output[i]);
        }
        printf("]\n\n");

        iconv_close(cd);
        free(output);
    }

    // Test 2: UTF-8 to ASCII with transliteration
    printf("Test 2: UTF-8 to ASCII with transliteration\n");
    {
        char input[] = "Café résumé naïve";
        size_t input_len = strlen(input);
        printf("Input (UTF-8): %s\n", input);

        size_t output_size = input_len * 2;
        char *output = malloc(output_size);
        if (!output)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        memset(output, 0, output_size);

        // ASCII//TRANSLIT tries to transliterate characters
        iconv_t cd = iconv_open("ASCII//TRANSLIT", "UTF-8");
        if (cd == (iconv_t)-1)
        {
            perror("iconv_open failed");
            free(output);
            return EXIT_FAILURE;
        }

        char *in_ptr = input;
        char *out_ptr = output;
        size_t in_left = input_len;
        size_t out_left = output_size;

        size_t result = iconv(cd, &in_ptr, &in_left, &out_ptr, &out_ptr);
        if (result == (size_t)-1)
        {
            if (errno == EILSEQ)
            {
                printf("Invalid byte sequence encountered\n");
            }
            else if (errno == E2BIG)
            {
                printf("Output buffer too small\n");
            }
        }

        printf("Output (ASCII): %s\n\n", output);

        iconv_close(cd);
        free(output);
    }

    // Test 3: UTF-8 to ISO-8859-1 (Latin-1)
    printf("Test 3: UTF-8 to ISO-8859-1 (Latin-1)\n");
    {
        char input[] = "Schön!"; // German word
        size_t input_len = strlen(input);
        printf("Input (UTF-8): %s\n", input);

        size_t output_size = input_len * 2;
        char *output = malloc(output_size);
        if (!output)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        memset(output, 0, output_size);

        iconv_t cd = iconv_open("ISO-8859-1", "UTF-8");
        if (cd == (iconv_t)-1)
        {
            perror("iconv_open failed");
            free(output);
            return EXIT_FAILURE;
        }

        char *in_ptr = input;
        char *out_ptr = output;
        size_t in_left = input_len;
        size_t out_left = output_size;

        size_t result = iconv(cd, &in_ptr, &in_left, &out_ptr, &out_ptr);
        if (result == (size_t)-1)
        {
            perror("iconv failed");
        }
        else
        {
            printf("Output (ISO-8859-1): %s\n", output);
            printf("ISO-8859-1 bytes: [ ");
            for (size_t i = 0; output[i] != '\0'; i++)
            {
                printf("%02x ", (unsigned char)output[i]);
            }
            printf("]\n");
        }
        printf("\n");

        iconv_close(cd);
        free(output);
    }

    // Test 4: List conversion capabilities
    printf("Test 4: Common encoding conversions\n");
    {
        const char *encodings[][2] = {
            {"UTF-8", "UTF-16"},
            {"UTF-8", "UTF-16LE"},
            {"UTF-8", "UTF-16BE"},
            {"UTF-8", "UTF-32"},
            {"UTF-8", "ISO-8859-1"},
            {"UTF-8", "ASCII"},
            {"UTF-8", "ASCII//TRANSLIT"},
            {"ISO-8859-1", "UTF-8"},
            {"UTF-16", "UTF-8"},
        };
        size_t count = sizeof(encodings) / sizeof(encodings[0]);

        printf("Supported conversions:\n");
        for (size_t i = 0; i < count; i++)
        {
            iconv_t cd = iconv_open(encodings[i][1], encodings[i][0]);
            if (cd != (iconv_t)-1)
            {
                printf("  ✓ %s -> %s\n", encodings[i][0], encodings[i][1]);
                iconv_close(cd);
            }
            else
            {
                printf("  ✗ %s -> %s (not supported)\n", encodings[i][0], encodings[i][1]);
            }
        }
        printf("\n");
    }

    // Test 5: Handling invalid sequences
    printf("Test 5: Error handling\n");
    {
        // Invalid UTF-8 sequence
        char input[] = {0xFF, 0xFE, 0x00}; // Invalid UTF-8
        size_t input_len = 2;
        printf("Input: Invalid UTF-8 bytes [0xFF 0xFE]\n");

        char output[100];
        iconv_t cd = iconv_open("UTF-16", "UTF-8");
        if (cd == (iconv_t)-1)
        {
            perror("iconv_open failed");
            return EXIT_FAILURE;
        }

        char *in_ptr = input;
        char *out_ptr = output;
        size_t in_left = input_len;
        size_t out_left = sizeof(output);

        size_t result = iconv(cd, &in_ptr, &in_left, &out_ptr, &out_left);
        if (result == (size_t)-1)
        {
            if (errno == EILSEQ)
            {
                printf("✓ Correctly detected: Invalid multibyte sequence (EILSEQ)\n");
            }
            else if (errno == EINVAL)
            {
                printf("✓ Correctly detected: Incomplete sequence (EINVAL)\n");
            }
            else if (errno == E2BIG)
            {
                printf("Output buffer too small (E2BIG)\n");
            }
            else
            {
                perror("iconv failed with unknown error");
            }
        }
        printf("\n");

        iconv_close(cd);
    }

    printf("=== Important Notes ===\n");
    printf("1. libiconv is included with macOS by default\n");
    printf("2. No need to install or link separately on macOS\n");
    printf("3. iconv_open(to_encoding, from_encoding) creates converter\n");
    printf("4. iconv() performs the actual conversion\n");
    printf("5. iconv_close() releases the converter resources\n");
    printf("6. Use //TRANSLIT for approximate conversions\n");
    printf("7. Use //IGNORE to skip unconvertible characters\n");
    printf("8. Always check return values for errors\n");
    printf("9. Common error codes:\n");
    printf("   - EILSEQ: Invalid byte sequence\n");
    printf("   - EINVAL: Incomplete sequence\n");
    printf("   - E2BIG: Output buffer too small\n");

    printf("\n=== Common Encodings ===\n");
    printf("• UTF-8, UTF-16, UTF-16LE, UTF-16BE, UTF-32\n");
    printf("• ASCII, ISO-8859-1 (Latin-1), ISO-8859-15\n");
    printf("• Windows-1252 (CP1252)\n");
    printf("• GB2312, BIG5 (Chinese)\n");
    printf("• Shift-JIS, EUC-JP (Japanese)\n");
    printf("• EUC-KR (Korean)\n");

    printf("\n=== To list all supported encodings ===\n");
    printf("Run in terminal: iconv -l\n");

    return EXIT_SUCCESS;
}
