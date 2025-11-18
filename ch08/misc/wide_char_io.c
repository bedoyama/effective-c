#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

int main(void)
{
    // Set locale to support wide characters
    setlocale(LC_ALL, "");

    printf("=== Narrow and Wide String I/O Functions ===\n\n");

    // Test 1: fgetc vs fgetwc - read character from stream
    printf("Test 1: fgetc() vs fgetwc() - read character from stream\n");
    {
        // Create test file with narrow characters
        FILE *fp = fopen("narrow_test.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "ABC");
            fclose(fp);
        }

        // Read with fgetc
        fp = fopen("narrow_test.txt", "r");
        if (fp != NULL)
        {
            int ch = fgetc(fp);
            printf("  fgetc() read: '%c' (value: %d)\n", ch, ch);
            fclose(fp);
        }

        // Create test file with wide characters
        fp = fopen("wide_test.txt", "w");
        if (fp != NULL)
        {
            fwprintf(fp, L"Ñom");
            fclose(fp);
        }

        // Read with fgetwc
        fp = fopen("wide_test.txt", "r");
        if (fp != NULL)
        {
            wint_t wch = fgetwc(fp);
            printf("  fgetwc() read: '%lc' (value: %d)\n", wch, wch);
            fclose(fp);
        }
        printf("\n");
    }

    // Test 2: getc vs getwc - read character (macro version)
    printf("Test 2: getc() vs getwc() - read character (often a macro)\n");
    {
        FILE *fp = fopen("narrow_test.txt", "r");
        if (fp != NULL)
        {
            int ch1 = getc(fp);
            int ch2 = getc(fp);
            printf("  getc() read: '%c' and '%c'\n", ch1, ch2);
            fclose(fp);
        }

        fp = fopen("wide_test.txt", "r");
        if (fp != NULL)
        {
            wint_t wch = getwc(fp);
            printf("  getwc() read: '%lc'\n", wch);
            fclose(fp);
        }
        printf("  Note: getc/getwc may be macros, fgetc/fgetwc are functions\n");
        printf("\n");
    }

    // Test 3: getchar vs getwchar - read from stdin
    printf("Test 3: getchar() vs getwchar() - read from stdin\n");
    {
        // Redirect stdin from a file to demonstrate
        FILE *saved_stdin = stdin;

        // Test getchar()
        FILE *narrow_stdin = fopen("narrow_test.txt", "r");
        if (narrow_stdin != NULL)
        {
            stdin = narrow_stdin;
            int ch = getchar();
            printf("  getchar() read from stdin: '%c'\n", ch);
            fclose(narrow_stdin);
        }

        // Test getwchar()
        FILE *wide_stdin = fopen("wide_test.txt", "r");
        if (wide_stdin != NULL)
        {
            stdin = wide_stdin;
            wint_t wch = getwchar();
            printf("  getwchar() read from stdin: '%lc'\n", wch);
            fclose(wide_stdin);
        }

        stdin = saved_stdin;
        printf("  Note: Normally these read from actual stdin\n");
        printf("\n");
    }

    // Test 4: fgets vs fgetws - read line from stream
    printf("Test 4: fgets() vs fgetws() - read line from stream\n");
    {
        // Create test file with narrow string
        FILE *fp = fopen("lines_test.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Hello World\nSecond Line\n");
            fclose(fp);
        }

        // Read with fgets
        fp = fopen("lines_test.txt", "r");
        if (fp != NULL)
        {
            char buffer[100];
            if (fgets(buffer, sizeof(buffer), fp) != NULL)
            {
                printf("  fgets() read: \"%s\"", buffer);
            }
            fclose(fp);
        }

        // Create test file with wide string
        fp = fopen("wide_lines_test.txt", "w");
        if (fp != NULL)
        {
            fwprintf(fp, L"Héllo Wörld\n");
            fclose(fp);
        }

        // Read with fgetws
        fp = fopen("wide_lines_test.txt", "r");
        if (fp != NULL)
        {
            wchar_t wbuffer[100];
            if (fgetws(wbuffer, 100, fp) != NULL)
            {
                printf("  fgetws() read: \"%ls\"\n", wbuffer);
            }
            fclose(fp);
        }
        printf("\n");
    }

    // Test 5: fputc vs fputwc - write character to stream
    printf("Test 5: fputc() vs fputwc() - write character to stream\n");
    {
        FILE *fp = fopen("output_narrow.txt", "w");
        if (fp != NULL)
        {
            fputc('X', fp);
            fputc('Y', fp);
            fputc('Z', fp);
            fclose(fp);
            printf("  ✓ fputc() wrote 'XYZ' to file\n");
        }

        fp = fopen("output_wide.txt", "w");
        if (fp != NULL)
        {
            fputwc(L'Ñ', fp);
            fputwc(L'ö', fp);
            fputwc(L'é', fp);
            fclose(fp);
            printf("  ✓ fputwc() wrote 'Ñöé' to file\n");
        }
        printf("\n");
    }

    // Test 6: putc vs putwc - write character (macro version)
    printf("Test 6: putc() vs putwc() - write character (often a macro)\n");
    {
        FILE *fp = fopen("output_narrow2.txt", "w");
        if (fp != NULL)
        {
            putc('A', fp);
            putc('B', fp);
            putc('C', fp);
            fclose(fp);
            printf("  ✓ putc() wrote 'ABC' to file\n");
        }

        fp = fopen("output_wide2.txt", "w");
        if (fp != NULL)
        {
            putwc(L'日', fp);
            putwc(L'本', fp);
            fclose(fp);
            printf("  ✓ putwc() wrote wide characters to file\n");
        }
        printf("\n");
    }

    // Test 7: fputs vs fputws - write string to stream
    printf("Test 7: fputs() vs fputws() - write string to stream\n");
    {
        FILE *fp = fopen("string_narrow.txt", "w");
        if (fp != NULL)
        {
            fputs("Hello, World!\n", fp);
            fputs("Second line\n", fp);
            fclose(fp);
            printf("  ✓ fputs() wrote narrow strings\n");
        }

        fp = fopen("string_wide.txt", "w");
        if (fp != NULL)
        {
            fputws(L"Héllo, Wörld!\n", fp);
            fputws(L"Sécond liné\n", fp);
            fclose(fp);
            printf("  ✓ fputws() wrote wide strings\n");
        }
        printf("\n");
    }

    // Test 8: putchar vs putwchar - write to stdout
    printf("Test 8: putchar() vs putwchar() - write to stdout\n");
    {
        printf("  putchar() output: ");
        putchar('H');
        putchar('i');
        putchar('!');
        putchar('\n');

        printf("  putwchar() output: ");
        putwchar(L'¡');
        putwchar(L'H');
        putwchar(L'ö');
        putwchar(L'l');
        putwchar(L'a');
        putwchar(L'!');
        putwchar(L'\n');
        printf("\n");
    }

    // Test 9: puts - write string to stdout (no wide equivalent)
    printf("Test 9: puts() - write string to stdout (no wide equivalent)\n");
    {
        printf("  puts() output:\n");
        puts("  Hello from puts()");
        puts("  Automatically adds newline");
        printf("  Note: puts() adds a newline, fputs() does not\n");
        printf("\n");
    }

    // Test 10: ungetc vs ungetwc - return character to stream
    printf("Test 10: ungetc() vs ungetwc() - return character to stream\n");
    {
        FILE *fp = fopen("narrow_test.txt", "r");
        if (fp != NULL)
        {
            int ch = fgetc(fp);
            printf("  Read with fgetc(): '%c'\n", ch);

            ungetc(ch, fp);
            printf("  Pushed back with ungetc()\n");

            ch = fgetc(fp);
            printf("  Read again: '%c'\n", ch);
            fclose(fp);
        }

        fp = fopen("wide_test.txt", "r");
        if (fp != NULL)
        {
            wint_t wch = fgetwc(fp);
            printf("  Read with fgetwc(): '%lc'\n", wch);

            ungetwc(wch, fp);
            printf("  Pushed back with ungetwc()\n");

            wch = fgetwc(fp);
            printf("  Read again: '%lc'\n", wch);
            fclose(fp);
        }
        printf("\n");
    }

    // Test 11: scanf vs wscanf - read formatted input from stdin
    printf("Test 11: scanf() vs wscanf() - read formatted from stdin\n");
    {
        FILE *saved_stdin = stdin;

        // Create test input for scanf
        FILE *narrow_input = fopen("scanf_test.txt", "w");
        if (narrow_input != NULL)
        {
            fprintf(narrow_input, "42 Hello");
            fclose(narrow_input);
        }

        // Test scanf()
        narrow_input = fopen("scanf_test.txt", "r");
        if (narrow_input != NULL)
        {
            stdin = narrow_input;
            int value;
            char str[50];
            int result = scanf("%d %s", &value, str);
            printf("  scanf() read %d items: value=%d, str=%s\n", result, value, str);
            fclose(narrow_input);
        }

        // Create test input for wscanf
        FILE *wide_input = fopen("wscanf_test.txt", "w");
        if (wide_input != NULL)
        {
            fwprintf(wide_input, L"99 Wörld");
            fclose(wide_input);
        }

        // Test wscanf()
        wide_input = fopen("wscanf_test.txt", "r");
        if (wide_input != NULL)
        {
            stdin = wide_input;
            int wvalue;
            wchar_t wstr[50];
            int wresult = wscanf(L"%d %ls", &wvalue, wstr);
            printf("  wscanf() read %d items: value=%d, str=%ls\n", wresult, wvalue, wstr);
            fclose(wide_input);
        }

        stdin = saved_stdin;
        printf("  Note: Normally these read from actual stdin\n");
        printf("\n");
    }

    // Test 12: fscanf vs fwscanf - read formatted from stream
    printf("Test 12: fscanf() vs fwscanf() - read formatted from stream\n");
    {
        FILE *fp = fopen("formatted_narrow.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "42 3.14 Hello");
            fclose(fp);
        }

        fp = fopen("formatted_narrow.txt", "r");
        if (fp != NULL)
        {
            int num;
            double dnum;
            char str[50];
            fscanf(fp, "%d %lf %s", &num, &dnum, str);
            printf("  fscanf() read: %d, %.2f, %s\n", num, dnum, str);
            fclose(fp);
        }

        FILE *wfp = fopen("formatted_wide.txt", "w");
        if (wfp != NULL)
        {
            fwprintf(wfp, L"99 2.71 Wörd");
            fclose(wfp);
        }

        wfp = fopen("formatted_wide.txt", "r");
        if (wfp != NULL)
        {
            int wnum;
            double wdnum;
            wchar_t wstr[50];
            fwscanf(wfp, L"%d %lf %ls", &wnum, &wdnum, wstr);
            printf("  fwscanf() read: %d, %.2f, %ls\n", wnum, wdnum, wstr);
            fclose(wfp);
        }
        printf("\n");
    }

    // Test 13: sscanf vs swscanf - read formatted from buffer
    printf("Test 13: sscanf() vs swscanf() - read formatted from buffer\n");
    {
        char narrow_str[] = "25 John 75.5";
        int age;
        char name[50];
        double score;

        sscanf(narrow_str, "%d %s %lf", &age, name, &score);
        printf("  sscanf() parsed: age=%d, name=%s, score=%.1f\n", age, name, score);

        wchar_t wide_str[] = L"30 Mária 85.5";
        int wage;
        wchar_t wname[50];
        double wscore;

        swscanf(wide_str, L"%d %ls %lf", &wage, wname, &wscore);
        printf("  swscanf() parsed: age=%d, name=%ls, score=%.1f\n", wage, wname, wscore);
        printf("\n");
    }

    // Test 14: printf vs wprintf - print formatted to stdout
    printf("Test 14: printf() vs wprintf() - print formatted to stdout\n");
    {
        printf("  printf() output: ");
        printf("Number: %d, String: %s\n", 42, "Hello");

        printf("  wprintf() output: ");
        wprintf(L"Number: %d, String: %ls\n", 42, L"Héllo");
        printf("\n");
    }

    // Test 15: fprintf vs fwprintf - print formatted to stream
    printf("Test 15: fprintf() vs fwprintf() - print formatted to stream\n");
    {
        FILE *fp = fopen("printf_narrow.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Value: %d, Name: %s, Score: %.2f\n", 100, "Alice", 95.5);
            fclose(fp);
            printf("  ✓ fprintf() wrote formatted output\n");
        }

        fp = fopen("printf_wide.txt", "w");
        if (fp != NULL)
        {
            fwprintf(fp, L"Value: %d, Name: %ls, Score: %.2f\n", 100, L"Alicé", 95.5);
            fclose(fp);
            printf("  ✓ fwprintf() wrote formatted wide output\n");
        }
        printf("\n");
    }

    // Test 16: sprintf vs swprintf - print formatted to buffer
    printf("Test 16: sprintf() vs swprintf() - print formatted to buffer\n");
    {
        char narrow_buf[100];
        sprintf(narrow_buf, "Result: %d + %d = %d", 5, 3, 8);
        printf("  sprintf() result: \"%s\"\n", narrow_buf);

        wchar_t wide_buf[100];
        swprintf(wide_buf, 100, L"Résult: %d + %d = %d", 5, 3, 8);
        printf("  swprintf() result: \"%ls\"\n", wide_buf);
        printf("  Note: swprintf() requires size parameter\n");
        printf("\n");
    }

    // Test 17: snprintf - sprintf with truncation (no wide equivalent with same behavior)
    printf("Test 17: snprintf() - sprintf with truncation\n");
    {
        char buffer[10];
        int written = snprintf(buffer, sizeof(buffer), "Long string that will be truncated");
        printf("  Buffer: \"%s\"\n", buffer);
        printf("  Would have written: %d characters\n", written);
        printf("  Actual buffer size: %zu\n", sizeof(buffer));
        printf("\n");

        printf("  Note: swprintf() also takes length but behaves differently:\n");
        printf("  • snprintf() returns chars that would be written\n");
        printf("  • swprintf() returns -1 if truncated\n");
        printf("\n");
    }

    // Test 18: Comparison of behaviors
    printf("Test 18: Key differences summary\n");
    {
        printf("  Narrow character functions (char):\n");
        printf("  • Work with char and char* types\n");
        printf("  • Single-byte per character (ASCII, extended ASCII)\n");
        printf("  • Functions: fgetc, fgets, fprintf, etc.\n");
        printf("\n");

        printf("  Wide character functions (wchar_t):\n");
        printf("  • Work with wchar_t and wchar_t* types\n");
        printf("  • Multi-byte per character (Unicode support)\n");
        printf("  • Functions: fgetwc, fgetws, fwprintf, etc.\n");
        printf("  • Require locale setup: setlocale(LC_ALL, \"\")\n");
        printf("\n");

        printf("  Special notes:\n");
        printf("  • puts() has no wide equivalent\n");
        printf("  • snprintf() behavior differs from swprintf()\n");
        printf("  • Wide functions use L prefix for format strings\n");
        printf("  • Use %%ls for wide strings in format\n");
        printf("\n");
    }

    // Clean up test files
    remove("narrow_test.txt");
    remove("wide_test.txt");
    remove("lines_test.txt");
    remove("wide_lines_test.txt");
    remove("output_narrow.txt");
    remove("output_wide.txt");
    remove("output_narrow2.txt");
    remove("output_wide2.txt");
    remove("string_narrow.txt");
    remove("string_wide.txt");
    remove("formatted_narrow.txt");
    remove("formatted_wide.txt");
    remove("printf_narrow.txt");
    remove("printf_wide.txt");
    remove("scanf_test.txt");
    remove("wscanf_test.txt");

    printf("=== Function Pairs Summary ===\n\n");
    printf("Character I/O:\n");
    printf("  fgetc   / fgetwc    - Read character from stream\n");
    printf("  getc    / getwc     - Read character (macro)\n");
    printf("  getchar / getwchar  - Read from stdin\n");
    printf("  fputc   / fputwc    - Write character to stream\n");
    printf("  putc    / putwc     - Write character (macro)\n");
    printf("  putchar / putwchar  - Write to stdout\n");
    printf("  ungetc  / ungetwc   - Push back character\n");
    printf("\n");

    printf("String I/O:\n");
    printf("  fgets   / fgetws    - Read line from stream\n");
    printf("  fputs   / fputws    - Write string to stream\n");
    printf("  puts    / (none)    - Write string to stdout\n");
    printf("\n");

    printf("Formatted I/O:\n");
    printf("  scanf   / wscanf    - Read formatted from stdin\n");
    printf("  fscanf  / fwscanf   - Read formatted from stream\n");
    printf("  sscanf  / swscanf   - Read formatted from buffer\n");
    printf("  printf  / wprintf   - Write formatted to stdout\n");
    printf("  fprintf / fwprintf  - Write formatted to stream\n");
    printf("  sprintf / swprintf  - Write formatted to buffer\n");
    printf("  snprintf/ (special) - sprintf with size limit\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. Wide character functions require setlocale(LC_ALL, \"\")\n");
    printf("2. Use L prefix for wide string literals: L\"text\"\n");
    printf("3. Use %%ls format specifier for wide strings\n");
    printf("4. Use %%lc format specifier for wide characters\n");
    printf("5. getc/putc may be macros, fgetc/fputc are always functions\n");
    printf("6. Don't mix narrow and wide I/O on same stream\n");
    printf("7. swprintf() requires size parameter, behaves differently than snprintf()\n");
    printf("8. puts() adds newline, fputs() does not\n");
    printf("9. Wide functions better for internationalization\n");
    printf("10. wchar_t size is platform-dependent (usually 2 or 4 bytes)\n");

    return EXIT_SUCCESS;
}
