#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== Reading and Writing Characters and Lines ===\n\n");

    // Create a test file first
    FILE *fp = fopen("test_rw.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to create test file\n");
        return EXIT_FAILURE;
    }
    fprintf(fp, "Line 1: Hello\nLine 2: World\nLine 3: Test\n");
    fclose(fp);

    // Test 1: fgetc - read single character
    printf("Test 1: fgetc() - read single character\n");
    {
        FILE *fp = fopen("test_rw.txt", "r");
        if (fp != NULL)
        {
            printf("  First 10 characters: ");
            for (int i = 0; i < 10; i++)
            {
                int ch = fgetc(fp);
                if (ch != EOF)
                {
                    printf("%c", ch);
                }
            }
            printf("\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 2: fputc - write single character
    printf("Test 2: fputc() - write single character\n");
    {
        FILE *fp = fopen("test_putc.txt", "w");
        if (fp != NULL)
        {
            char str[] = "Hello!";
            for (size_t i = 0; str[i] != '\0'; i++)
            {
                fputc(str[i], fp);
            }
            fputc('\n', fp);
            printf("  ✓ Wrote characters using fputc()\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 3: getc and putc (macros)
    printf("Test 3: getc() and putc() - macro versions\n");
    {
        FILE *in = fopen("test_rw.txt", "r");
        FILE *out = fopen("test_copy.txt", "w");

        if (in != NULL && out != NULL)
        {
            int ch;
            while ((ch = getc(in)) != EOF)
            {
                putc(ch, out);
            }
            printf("  ✓ Copied file using getc() and putc()\n");
            fclose(in);
            fclose(out);
        }
        printf("\n");
    }

    // Test 4: getchar and putchar (stdin/stdout)
    printf("Test 4: getchar() and putchar() - stdin/stdout\n");
    {
        printf("  getchar() reads from stdin\n");
        printf("  putchar() writes to stdout\n");
        printf("  Example: putchar('A') outputs: ");
        putchar('A');
        putchar('\n');
        printf("\n");
    }

    // Test 5: ungetc - push character back
    printf("Test 5: ungetc() - push character back to stream\n");
    {
        FILE *fp = fopen("test_rw.txt", "r");
        if (fp != NULL)
        {
            int ch1 = fgetc(fp);
            int ch2 = fgetc(fp);
            printf("  Read two characters: '%c' '%c'\n", ch1, ch2);

            // Push second character back
            ungetc(ch2, fp);
            printf("  Pushed '%c' back to stream\n", ch2);

            // Read again
            int ch3 = fgetc(fp);
            printf("  Next read returns: '%c' (the pushed character)\n", ch3);
            fclose(fp);
        }
        printf("\n");
    }

    // Test 6: fgets - read line
    printf("Test 6: fgets() - read line\n");
    {
        FILE *fp = fopen("test_rw.txt", "r");
        if (fp != NULL)
        {
            char buffer[100];
            int line_num = 1;

            while (fgets(buffer, sizeof(buffer), fp) != NULL)
            {
                printf("  Line %d: %s", line_num++, buffer);
            }
            fclose(fp);
        }
        printf("\n");
    }

    // Test 7: fputs - write line
    printf("Test 7: fputs() - write string/line\n");
    {
        FILE *fp = fopen("test_puts.txt", "w");
        if (fp != NULL)
        {
            fputs("First line\n", fp);
            fputs("Second line\n", fp);
            fputs("Third line\n", fp);
            printf("  ✓ Wrote 3 lines using fputs()\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 8: gets and puts (stdin/stdout) - DON'T USE gets!
    printf("Test 8: puts() - write string to stdout\n");
    {
        puts("  This line written with puts() (adds newline)");
        printf("  ⚠ gets() is UNSAFE and removed from C11\n");
        printf("  ✓ Use fgets(buffer, size, stdin) instead\n");
        printf("\n");
    }

    // Test 9: Reading until EOF
    printf("Test 9: Reading until EOF\n");
    {
        FILE *fp = fopen("test_rw.txt", "r");
        if (fp != NULL)
        {
            int ch;
            int char_count = 0;

            while ((ch = fgetc(fp)) != EOF)
            {
                char_count++;
            }

            printf("  Total characters read: %d\n", char_count);

            if (feof(fp))
            {
                printf("  ✓ Reached end of file\n");
            }
            if (ferror(fp))
            {
                printf("  ✗ Error occurred while reading\n");
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 10: Line-by-line processing
    printf("Test 10: Processing lines\n");
    {
        FILE *fp = fopen("test_rw.txt", "r");
        if (fp != NULL)
        {
            char buffer[100];
            int line_num = 1;

            while (fgets(buffer, sizeof(buffer), fp) != NULL)
            {
                // Remove newline if present
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n')
                {
                    buffer[len - 1] = '\0';
                }

                printf("  [%d] '%s'\n", line_num++, buffer);
            }
            fclose(fp);
        }
        printf("\n");
    }

    // Test 11: Character I/O with error checking
    printf("Test 11: Character I/O with error checking\n");
    {
        FILE *fp = fopen("test_errors.txt", "w");
        if (fp != NULL)
        {
            for (char ch = 'A'; ch <= 'Z'; ch++)
            {
                if (fputc(ch, fp) == EOF)
                {
                    fprintf(stderr, "  Error writing character\n");
                    break;
                }
            }
            printf("  ✓ Wrote alphabet with error checking\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 12: Combining character and line I/O
    printf("Test 12: Mixed character and line I/O\n");
    {
        FILE *fp = fopen("test_mixed.txt", "w");
        if (fp != NULL)
        {
            // Write using different methods
            fputc('A', fp);
            fputc('\n', fp);
            fputs("Line with fputs\n", fp);
            fprintf(fp, "Line with fprintf: %d\n", 42);

            fclose(fp);

            // Read back
            fp = fopen("test_mixed.txt", "r");
            if (fp != NULL)
            {
                printf("  Reading back:\n");
                char buffer[100];
                while (fgets(buffer, sizeof(buffer), fp) != NULL)
                {
                    printf("    %s", buffer);
                }
                fclose(fp);
            }
        }
        printf("\n");
    }

    printf("=== Function Summary ===\n\n");
    printf("Character Input:\n");
    printf("  fgetc(fp)    - Read character from file, returns int\n");
    printf("  getc(fp)     - Same as fgetc (may be macro)\n");
    printf("  getchar()    - Read character from stdin\n");
    printf("  ungetc(c,fp) - Push character back to stream\n");
    printf("\n");

    printf("Character Output:\n");
    printf("  fputc(c,fp)  - Write character to file\n");
    printf("  putc(c,fp)   - Same as fputc (may be macro)\n");
    printf("  putchar(c)   - Write character to stdout\n");
    printf("\n");

    printf("Line Input:\n");
    printf("  fgets(buf,n,fp) - Read line (max n-1 chars), adds \\0\n");
    printf("  gets(buf)       - UNSAFE! Removed in C11. Use fgets.\n");
    printf("\n");

    printf("Line Output:\n");
    printf("  fputs(str,fp) - Write string (no newline added)\n");
    printf("  puts(str)     - Write string to stdout (adds newline)\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. fgetc/getc return int, not char (to handle EOF)\n");
    printf("2. EOF is typically -1, check with EOF constant\n");
    printf("3. fgets includes newline if present\n");
    printf("4. fgets always null-terminates\n");
    printf("5. fputs does NOT add newline automatically\n");
    printf("6. puts adds newline automatically\n");
    printf("7. ungetc guarantees at least one character pushback\n");
    printf("8. Use feof() and ferror() to check why reading stopped\n");
    printf("9. Never use gets() - use fgets(buffer, size, stdin)\n");
    printf("10. Character I/O is slower than block I/O for large data\n");

    return EXIT_SUCCESS;
}
