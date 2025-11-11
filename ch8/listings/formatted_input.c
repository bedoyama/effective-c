#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== Reading Formatted Text Streams ===\n\n");

    // Create test file
    FILE *fp = fopen("test_formatted.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "42 3.14159 Hello\n");
        fprintf(fp, "100 2.71828 World\n");
        fprintf(fp, "-5 1.41421 Test\n");
        fprintf(fp, "John Doe 25 5.9\n");
        fprintf(fp, "Jane Smith 30 5.7\n");
        fclose(fp);
    }

    // Test 1: fscanf - basic formatted input
    printf("Test 1: fscanf() - basic formatted input\n");
    {
        FILE *fp = fopen("test_formatted.txt", "r");
        if (fp != NULL)
        {
            int num;
            double fnum;
            char str[50];

            while (fscanf(fp, "%d %lf %s", &num, &fnum, str) == 3)
            {
                printf("  Read: int=%d, double=%.5f, string=%s\n", num, fnum, str);
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 2: scanf - read from stdin (demonstration)
    printf("Test 2: scanf() - read from stdin (demo only)\n");
    {
        printf("  scanf() reads from standard input\n");
        printf("  Example: scanf(\"%%d\", &value);\n");
        printf("  Always check return value!\n");
        printf("\n");
    }

    // Test 3: sscanf - read from string
    printf("Test 3: sscanf() - parse string\n");
    {
        char data[] = "25 John 75.5";
        int age;
        char name[50];
        double score;

        int result = sscanf(data, "%d %s %lf", &age, name, &score);
        printf("  Input string: \"%s\"\n", data);
        printf("  Parsed %d items:\n", result);
        printf("    age=%d, name=%s, score=%.1f\n", age, name, score);
        printf("\n");
    }

    // Test 4: fscanf return value
    printf("Test 4: fscanf() return value\n");
    {
        FILE *fp = fopen("test_formatted.txt", "r");
        if (fp != NULL)
        {
            int num;
            double fnum;
            char str[50];

            int result = fscanf(fp, "%d %lf %s", &num, &fnum, str);
            printf("  fscanf returned: %d (number of items successfully read)\n", result);
            printf("  Values: %d, %.5f, %s\n", num, fnum, str);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 5: Reading different types
    printf("Test 5: Reading various data types\n");
    {
        FILE *fp = tmpfile();
        if (fp != NULL)
        {
            // Write various types
            fprintf(fp, "%d %ld %f %lf %c %s\n", 42, 1234567890L, 3.14f, 2.71828, 'A', "Hello");
            rewind(fp);

            // Read them back
            int i;
            long l;
            float f;
            double d;
            char c;
            char s[50];

            fscanf(fp, "%d %ld %f %lf %c %s", &i, &l, &f, &d, &c, s);
            printf("  int: %d\n", i);
            printf("  long: %ld\n", l);
            printf("  float: %f\n", f);
            printf("  double: %lf\n", d);
            printf("  char: %c\n", c);
            printf("  string: %s\n", s);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 6: Width specifier
    printf("Test 6: Field width specifier\n");
    {
        char input[] = "12345ABCDE";

        int num;
        char str[10];

        sscanf(input, "%3d%5s", &num, str);
        printf("  Input: \"%s\"\n", input);
        printf("  %%3d reads 3 digits: %d\n", num);
        printf("  %%5s reads 5 chars: %s\n", str);
        printf("\n");
    }

    // Test 7: Skipping fields with *
    printf("Test 7: Suppressing assignment with *\n");
    {
        char input[] = "100 skip_this 42";

        int first, second;
        int result = sscanf(input, "%d %*s %d", &first, &second);

        printf("  Input: \"%s\"\n", input);
        printf("  %%d %%*s %%d: read=%d values (middle string skipped)\n", result);
        printf("  first=%d, second=%d\n", first, second);
        printf("\n");
    }

    // Test 8: Character sets with []
    printf("Test 8: Scanset ([]) - read specific characters\n");
    {
        char input[] = "abc123xyz";
        char letters[50];
        int number;
        char more[50];

        sscanf(input, "%[a-z]%d%s", letters, &number, more);
        printf("  Input: \"%s\"\n", input);
        printf("  %%[a-z] reads letters: %s\n", letters);
        printf("  %%d reads number: %d\n", number);
        printf("  %%s reads rest: %s\n", more);
        printf("\n");
    }

    // Test 9: Reading until newline
    printf("Test 9: Reading line with scanset\n");
    {
        FILE *fp = fopen("test_formatted.txt", "r");
        if (fp != NULL)
        {
            char line[100];

            // Read entire line (excluding newline)
            if (fscanf(fp, "%[^\n]", line) == 1)
            {
                printf("  Read line: \"%s\"\n", line);
                fgetc(fp); // Consume the newline
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 10: Error handling with fscanf
    printf("Test 10: Error handling\n");
    {
        char input[] = "abc";
        int value;

        int result = sscanf(input, "%d", &value);
        if (result == 1)
        {
            printf("  Successfully read: %d\n", value);
        }
        else if (result == 0)
        {
            printf("  ✗ No items matched (input was: \"%s\")\n", input);
        }
        else if (result == EOF)
        {
            printf("  ✗ Input failure before any conversion\n");
        }
        printf("\n");
    }

    // Test 11: Reading structured data
    printf("Test 11: Reading structured records\n");
    {
        FILE *fp = fopen("test_formatted.txt", "r");
        if (fp != NULL)
        {
            // Skip first 3 lines
            for (int i = 0; i < 3; i++)
            {
                fscanf(fp, "%*[^\n]");
                fgetc(fp);
            }

            // Read person records
            char first[50], last[50];
            int age;
            double height;

            printf("  Person records:\n");
            while (fscanf(fp, "%s %s %d %lf", first, last, &age, &height) == 4)
            {
                printf("    %s %s, Age: %d, Height: %.1f\n", first, last, age, height);
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 12: Mixing fscanf and fgets
    printf("Test 12: Combining fscanf and fgets\n");
    {
        FILE *fp = tmpfile();
        if (fp != NULL)
        {
            fprintf(fp, "42\nThis is a text line\n100\n");
            rewind(fp);

            int num1;
            char line[100];
            int num2;

            fscanf(fp, "%d\n", &num1);
            printf("  Read number: %d\n", num1);

            fgets(line, sizeof(line), fp);
            printf("  Read line: %s", line);

            fscanf(fp, "%d", &num2);
            printf("  Read number: %d\n", num2);

            fclose(fp);
        }
        printf("\n");
    }

    printf("=== Format Specifiers Summary ===\n\n");
    printf("Integer Types:\n");
    printf("  %%d or %%i  - int (signed decimal)\n");
    printf("  %%u         - unsigned int\n");
    printf("  %%ld        - long int\n");
    printf("  %%lld       - long long int\n");
    printf("  %%hd        - short int\n");
    printf("  %%o         - octal\n");
    printf("  %%x or %%X   - hexadecimal\n");
    printf("\n");

    printf("Floating Point:\n");
    printf("  %%f, %%e, %%g - float\n");
    printf("  %%lf         - double\n");
    printf("  %%Lf         - long double\n");
    printf("\n");

    printf("Characters and Strings:\n");
    printf("  %%c         - single character\n");
    printf("  %%s         - string (stops at whitespace)\n");
    printf("  %%[...]     - scanset (read specific chars)\n");
    printf("  %%[^...]    - inverted scanset\n");
    printf("\n");

    printf("Other:\n");
    printf("  %%p         - pointer\n");
    printf("  %%n         - write number of chars read so far\n");
    printf("  %%%%         - literal %%\n");
    printf("  %%*...      - suppress assignment\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. scanf family returns number of items successfully read\n");
    printf("2. Returns EOF on input failure before any conversion\n");
    printf("3. Always check return value!\n");
    printf("4. Whitespace in format string matches any whitespace\n");
    printf("5. %%s stops at first whitespace\n");
    printf("6. Use width specifier to prevent buffer overflow: %%49s\n");
    printf("7. %%[^\\n] reads until newline (but doesn't consume it)\n");
    printf("8. Use %%*s to skip fields without storing them\n");
    printf("9. scanf leaves whitespace (including \\n) in buffer\n");
    printf("10. Use fgets for safer line-based input\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Always check return value\n");
    printf("✓ Use width specifiers for strings: %%49s (not %%s)\n");
    printf("✓ Clear input buffer after failed scanf\n");
    printf("✓ Prefer fgets + sscanf over scanf for safer input\n");
    printf("✓ Use %%n to track how much was read\n");
    printf("✓ Handle EOF and error cases\n");
    printf("✗ Don't use %%s without width limit\n");
    printf("✗ Don't ignore return value\n");

    return EXIT_SUCCESS;
}
