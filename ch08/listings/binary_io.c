#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char name[50];
    double salary;
} Employee;

int main(void)
{
    printf("=== Reading from and Writing to Binary Streams ===\n\n");

    // Test 1: fwrite - write binary data
    printf("Test 1: fwrite() - write binary data\n");
    {
        FILE *fp = fopen("test_binary.dat", "wb");
        if (fp != NULL)
        {
            int data[] = {10, 20, 30, 40, 50};
            size_t count = sizeof(data) / sizeof(data[0]);

            size_t written = fwrite(data, sizeof(int), count, fp);
            printf("  ✓ Wrote %zu integers (%zu bytes each)\n", written, sizeof(int));
            printf("  Total bytes: %zu\n", written * sizeof(int));

            fclose(fp);
        }
        printf("\n");
    }

    // Test 2: fread - read binary data
    printf("Test 2: fread() - read binary data\n");
    {
        FILE *fp = fopen("test_binary.dat", "rb");
        if (fp != NULL)
        {
            int data[5];

            size_t read = fread(data, sizeof(int), 5, fp);
            printf("  ✓ Read %zu integers:\n", read);
            printf("  ");
            for (size_t i = 0; i < read; i++)
            {
                printf("%d ", data[i]);
            }
            printf("\n");

            fclose(fp);
        }
        printf("\n");
    }

    // Test 3: Writing structures
    printf("Test 3: Writing structures to binary file\n");
    {
        FILE *fp = fopen("employees.dat", "wb");
        if (fp != NULL)
        {
            Employee employees[] = {
                {1, "Alice Johnson", 75000.50},
                {2, "Bob Smith", 82000.00},
                {3, "Carol White", 69500.75}};

            size_t count = sizeof(employees) / sizeof(employees[0]);
            size_t written = fwrite(employees, sizeof(Employee), count, fp);

            printf("  ✓ Wrote %zu employee records\n", written);
            printf("  Each record: %zu bytes\n", sizeof(Employee));

            fclose(fp);
        }
        printf("\n");
    }

    // Test 4: Reading structures
    printf("Test 4: Reading structures from binary file\n");
    {
        FILE *fp = fopen("employees.dat", "rb");
        if (fp != NULL)
        {
            Employee emp;

            printf("  Employee records:\n");
            while (fread(&emp, sizeof(Employee), 1, fp) == 1)
            {
                printf("    ID: %d, Name: %s, Salary: $%.2f\n",
                       emp.id, emp.name, emp.salary);
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 5: Random access in binary files
    printf("Test 5: Random access in binary files\n");
    {
        FILE *fp = fopen("employees.dat", "rb");
        if (fp != NULL)
        {
            Employee emp;

            // Read second employee
            fseek(fp, sizeof(Employee), SEEK_SET);
            fread(&emp, sizeof(Employee), 1, fp);
            printf("  Second employee: %s\n", emp.name);

            // Read last employee
            fseek(fp, -sizeof(Employee), SEEK_END);
            fread(&emp, sizeof(Employee), 1, fp);
            printf("  Last employee: %s\n", emp.name);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 6: Updating binary records
    printf("Test 6: Updating binary file records\n");
    {
        FILE *fp = fopen("employees.dat", "r+b");
        if (fp != NULL)
        {
            Employee emp;

            // Read first employee
            fread(&emp, sizeof(Employee), 1, fp);
            printf("  Before: %s, Salary: $%.2f\n", emp.name, emp.salary);

            // Update salary
            emp.salary += 5000.00;

            // Write back to same position
            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, fp);

            // Verify update
            fseek(fp, 0, SEEK_SET);
            fread(&emp, sizeof(Employee), 1, fp);
            printf("  After: %s, Salary: $%.2f\n", emp.name, emp.salary);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 7: Binary vs Text mode
    printf("Test 7: Binary vs Text mode differences\n");
    {
        printf("  Binary mode (\"wb\", \"rb\"):\n");
        printf("  • No newline translation (\\n stays as \\n)\n");
        printf("  • Exact byte-for-byte read/write\n");
        printf("  • Use for structures, arrays, non-text data\n");
        printf("  • Portable across same platform\n");
        printf("\n");

        printf("  Text mode (\"w\", \"r\"):\n");
        printf("  • Newline translation on Windows (\\n <-> \\r\\n)\n");
        printf("  • For human-readable text\n");
        printf("  • May modify data during I/O\n");
        printf("  • Better portability for text\n");
        printf("\n");
    }

    // Test 8: Writing mixed binary data
    printf("Test 8: Writing mixed data types\n");
    {
        FILE *fp = fopen("mixed.dat", "wb");
        if (fp != NULL)
        {
            int count = 5;
            double values[] = {1.1, 2.2, 3.3, 4.4, 5.5};

            // Write count first
            fwrite(&count, sizeof(int), 1, fp);

            // Then write array
            fwrite(values, sizeof(double), count, fp);

            printf("  ✓ Wrote count and array\n");

            fclose(fp);
        }

        // Read back
        fp = fopen("mixed.dat", "rb");
        if (fp != NULL)
        {
            int count;
            fread(&count, sizeof(int), 1, fp);
            printf("  Read count: %d\n", count);

            double values[10];
            fread(values, sizeof(double), count, fp);
            printf("  Read values: ");
            for (int i = 0; i < count; i++)
            {
                printf("%.1f ", values[i]);
            }
            printf("\n");

            fclose(fp);
        }
        printf("\n");
    }

    // Test 9: Checking read/write success
    printf("Test 9: Error checking with fread/fwrite\n");
    {
        FILE *fp = fopen("test_check.dat", "wb");
        if (fp != NULL)
        {
            int data[] = {1, 2, 3, 4, 5};

            size_t written = fwrite(data, sizeof(int), 5, fp);
            if (written == 5)
            {
                printf("  ✓ All 5 items written\n");
            }
            else
            {
                printf("  ✗ Only %zu items written\n", written);
            }

            fclose(fp);
        }

        fp = fopen("test_check.dat", "rb");
        if (fp != NULL)
        {
            int data[10];

            size_t read = fread(data, sizeof(int), 10, fp);
            printf("  Read %zu items (requested 10)\n", read);

            if (feof(fp))
            {
                printf("  ✓ Reached end of file\n");
            }
            if (ferror(fp))
            {
                printf("  ✗ Error occurred during read\n");
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 10: Portability concerns
    printf("Test 10: Binary file portability issues\n");
    {
        printf("  Portability concerns:\n");
        printf("  • sizeof(int) varies by platform\n");
        printf("  • Endianness (byte order) differs\n");
        printf("  • Structure padding varies by compiler\n");
        printf("  • Alignment requirements differ\n");
        printf("\n");

        printf("  Current platform:\n");
        printf("    sizeof(int): %zu bytes\n", sizeof(int));
        printf("    sizeof(long): %zu bytes\n", sizeof(long));
        printf("    sizeof(double): %zu bytes\n", sizeof(double));
        printf("    sizeof(Employee): %zu bytes\n", sizeof(Employee));
        printf("\n");
    }

    // Test 11: Block I/O efficiency
    printf("Test 11: Block I/O vs character I/O\n");
    {
        FILE *fp = fopen("block_test.dat", "wb");
        if (fp != NULL)
        {
            int data[1000];
            for (int i = 0; i < 1000; i++)
            {
                data[i] = i;
            }

            // Efficient: single block write
            fwrite(data, sizeof(int), 1000, fp);
            printf("  ✓ Wrote 1000 integers in one block (fast)\n");

            fclose(fp);
        }

        // Compare with character-by-character (much slower for large data)
        printf("  Block I/O is much faster for large data\n");
        printf("  Use fread/fwrite for binary, not fgetc/fputc\n");
        printf("\n");
    }

    // Test 12: Safe structure writing with padding
    printf("Test 12: Structure padding awareness\n");
    {
        typedef struct
        {
            char c;   // 1 byte + 3 bytes padding
            int i;    // 4 bytes
            double d; // 8 bytes
        } PaddedStruct;

        printf("  PaddedStruct size: %zu bytes\n", sizeof(PaddedStruct));
        printf("  Sum of members: %zu bytes\n", sizeof(char) + sizeof(int) + sizeof(double));
        printf("  Padding: %zu bytes\n", sizeof(PaddedStruct) - (sizeof(char) + sizeof(int) + sizeof(double)));
        printf("\n");

        printf("  For portable binary files:\n");
        printf("  • Use fixed-size types (int32_t, etc.)\n");
        printf("  • Use packed structures (#pragma pack)\n");
        printf("  • Or write/read members individually\n");
        printf("\n");
    }

    printf("=== Function Summary ===\n\n");
    printf("fwrite(ptr, size, count, stream):\n");
    printf("  • Writes 'count' items of 'size' bytes each\n");
    printf("  • Returns number of items successfully written\n");
    printf("  • Binary mode recommended\n");
    printf("\n");

    printf("fread(ptr, size, count, stream):\n");
    printf("  • Reads 'count' items of 'size' bytes each\n");
    printf("  • Returns number of items successfully read\n");
    printf("  • Binary mode recommended\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. Always open binary files with 'b' mode: \"rb\", \"wb\", \"r+b\"\n");
    printf("2. fread/fwrite return number of complete items read/written\n");
    printf("3. Check return value to detect short reads/writes\n");
    printf("4. Use feof() and ferror() to determine why read stopped\n");
    printf("5. Binary files are not portable across different platforms\n");
    printf("6. Structure padding affects binary layout\n");
    printf("7. Endianness varies by architecture\n");
    printf("8. Use fixed-size types for portable binary formats\n");
    printf("9. fseek/ftell work well with binary files\n");
    printf("10. Block I/O is much faster than character I/O\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Always use binary mode for non-text data\n");
    printf("✓ Check fread/fwrite return values\n");
    printf("✓ Use fixed-size types for portability\n");
    printf("✓ Document binary file format\n");
    printf("✓ Consider using a library for portable binary I/O\n");
    printf("✓ Write version numbers in file headers\n");
    printf("✓ Use checksums for data integrity\n");
    printf("✗ Don't assume binary files are portable\n");
    printf("✗ Don't ignore structure padding\n");

    return EXIT_SUCCESS;
}
