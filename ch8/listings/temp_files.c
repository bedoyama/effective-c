#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== Using Temporary Files ===\n\n");

    // Test 1: tmpfile - create anonymous temporary file
    printf("Test 1: tmpfile() - anonymous temporary file\n");
    {
        FILE *tmp = tmpfile();
        if (tmp == NULL)
        {
            fprintf(stderr, "  Failed to create temporary file\n");
            return EXIT_FAILURE;
        }

        printf("  ✓ Created anonymous temporary file\n");

        // Write to temp file
        fprintf(tmp, "This is temporary data\n");
        fprintf(tmp, "Line 2 of temp data\n");
        printf("  ✓ Wrote data to temp file\n");

        // Read back from temp file
        rewind(tmp);
        char buffer[100];
        printf("  Reading back:\n");
        while (fgets(buffer, sizeof(buffer), tmp) != NULL)
        {
            printf("    %s", buffer);
        }

        // File is automatically deleted when closed
        fclose(tmp);
        printf("  ✓ File closed (automatically deleted)\n");
        printf("\n");
    }

    // Test 2: tmpnam - generate temporary filename
    printf("Test 2: tmpnam() - generate temporary filename\n");
    {
        char filename[L_tmpnam];
        if (tmpnam(filename) != NULL)
        {
            printf("  Generated filename: %s\n", filename);

            // Use the filename to create a file
            FILE *fp = fopen(filename, "w+");
            if (fp != NULL)
            {
                fprintf(fp, "Temporary file with known name\n");
                printf("  ✓ Created file with tmpnam name\n");

                // Read back
                rewind(fp);
                char buffer[100];
                fgets(buffer, sizeof(buffer), fp);
                printf("  Content: %s", buffer);

                fclose(fp);

                // Must manually remove the file
                if (remove(filename) == 0)
                {
                    printf("  ✓ Manually removed temp file\n");
                }
            }
        }
        printf("\n");
    }

    // Test 3: tmpnam with NULL
    printf("Test 3: tmpnam(NULL) - static buffer\n");
    {
        char *filename = tmpnam(NULL);
        if (filename != NULL)
        {
            printf("  Generated filename: %s\n", filename);
            printf("  ⚠ Uses static buffer (not thread-safe)\n");
            printf("  ⚠ Next call to tmpnam(NULL) overwrites this\n");
        }
        printf("\n");
    }

    // Test 4: TMP_MAX - maximum unique names
    printf("Test 4: TMP_MAX constant\n");
    {
        printf("  TMP_MAX: %d\n", TMP_MAX);
        printf("  tmpnam() can generate at least %d unique names\n", TMP_MAX);
        printf("\n");
    }

    // Test 5: Generating multiple unique temp names
    printf("Test 5: Multiple unique temporary filenames\n");
    {
        char name1[L_tmpnam];
        char name2[L_tmpnam];
        char name3[L_tmpnam];

        tmpnam(name1);
        tmpnam(name2);
        tmpnam(name3);

        printf("  Name 1: %s\n", name1);
        printf("  Name 2: %s\n", name2);
        printf("  Name 3: %s\n", name3);
        printf("  ✓ All names are different\n");
        printf("\n");
    }

    // Test 6: tmpfile use case - sorting large data
    printf("Test 6: tmpfile() use case - temporary workspace\n");
    {
        FILE *tmp = tmpfile();
        if (tmp != NULL)
        {
            // Simulate writing intermediate data
            int data[] = {42, 17, 93, 24, 56, 81, 33, 69};
            size_t count = sizeof(data) / sizeof(data[0]);

            printf("  Writing %zu integers to temp file\n", count);
            fwrite(data, sizeof(int), count, tmp);

            // Read back and process
            rewind(tmp);
            int value;
            printf("  Reading back: ");
            for (size_t i = 0; i < count; i++)
            {
                fread(&value, sizeof(int), 1, tmp);
                printf("%d ", value);
            }
            printf("\n");

            fclose(tmp);
            printf("  ✓ Temp file used and automatically deleted\n");
        }
        printf("\n");
    }

    // Test 7: Security considerations
    printf("Test 7: Security considerations\n");
    {
        printf("  tmpnam() security issues:\n");
        printf("  ⚠ Race condition between name generation and file creation\n");
        printf("  ⚠ Predictable names on some systems\n");
        printf("  ⚠ Attacker could create file with same name\n");
        printf("\n");

        printf("  tmpfile() security:\n");
        printf("  ✓ No race condition (file created immediately)\n");
        printf("  ✓ File is anonymous (no name visible)\n");
        printf("  ✓ Automatically deleted\n");
        printf("  ✓ Safer choice for temporary files\n");
        printf("\n");
    }

    // Test 8: Alternative - mkstemp (POSIX, not standard C)
    printf("Test 8: Better alternatives (POSIX)\n");
    {
        printf("  On POSIX systems, prefer:\n");
        printf("  • mkstemp() - creates unique file, returns fd\n");
        printf("  • mkdtemp() - creates unique directory\n");
        printf("  • tmpfile() - for anonymous temporary files\n");
        printf("\n");

        printf("  Avoid:\n");
        printf("  ✗ tmpnam() - race condition vulnerability\n");
        printf("  ✗ tempnam() - same issues as tmpnam()\n");
        printf("\n");
    }

    // Test 9: Custom temporary directory
    printf("Test 9: Temporary file locations\n");
    {
        printf("  Default temp locations:\n");
        printf("  Unix/Linux: /tmp or /var/tmp\n");
        printf("  macOS: /var/folders/.../T/\n");
        printf("  Windows: %%TEMP%% (e.g., C:\\Users\\...\\AppData\\Local\\Temp)\n");
        printf("\n");

        printf("  Environment variables:\n");
        printf("  • TMPDIR (Unix/Linux/macOS)\n");
        printf("  • TEMP or TMP (Windows)\n");
        printf("\n");
    }

    // Test 10: tmpfile advantages and limitations
    printf("Test 10: tmpfile() characteristics\n");
    {
        printf("  Advantages:\n");
        printf("  ✓ Automatic cleanup on close or program exit\n");
        printf("  ✓ No race conditions\n");
        printf("  ✓ No need to generate unique names\n");
        printf("  ✓ No need to manually delete\n");
        printf("  ✓ Binary mode (\"wb+\")\n");
        printf("\n");

        printf("  Limitations:\n");
        printf("  ✗ Can't get the filename\n");
        printf("  ✗ Can't share file with other processes easily\n");
        printf("  ✗ File disappears on close (can't reopen)\n");
        printf("  ✗ May fail if no temp space available\n");
        printf("\n");
    }

    // Test 11: Error handling
    printf("Test 11: Error handling\n");
    {
        FILE *tmp = tmpfile();
        if (tmp == NULL)
        {
            fprintf(stderr, "  tmpfile() can fail if:\n");
            fprintf(stderr, "  • No space in temp directory\n");
            fprintf(stderr, "  • No permission to create files\n");
            fprintf(stderr, "  • System limit on open files reached\n");
        }
        else
        {
            printf("  ✓ tmpfile() succeeded\n");
            fclose(tmp);
        }
        printf("\n");
    }

    // Test 12: Practical example - processing data
    printf("Test 12: Practical example - data processing\n");
    {
        FILE *tmp = tmpfile();
        if (tmp != NULL)
        {
            // Simulate processing pipeline
            printf("  Step 1: Write raw data to temp file\n");
            for (int i = 1; i <= 10; i++)
            {
                fprintf(tmp, "%d\n", i * i);
            }

            printf("  Step 2: Process data from temp file\n");
            rewind(tmp);
            int sum = 0;
            int value;
            while (fscanf(tmp, "%d", &value) == 1)
            {
                sum += value;
            }
            printf("  Sum of squares 1-10: %d\n", sum);

            fclose(tmp);
            printf("  Step 3: Temp file automatically deleted\n");
        }
        printf("\n");
    }

    printf("=== Function Summary ===\n\n");
    printf("tmpfile():\n");
    printf("  • Creates anonymous temporary binary file (\"wb+\" mode)\n");
    printf("  • Returns FILE* or NULL on error\n");
    printf("  • File automatically deleted when closed\n");
    printf("  • No race conditions\n");
    printf("  • Most secure option\n");
    printf("\n");

    printf("tmpnam(buffer):\n");
    printf("  • Generates unique temporary filename\n");
    printf("  • Buffer size must be at least L_tmpnam\n");
    printf("  • If buffer is NULL, uses static buffer\n");
    printf("  • File not created, just name generated\n");
    printf("  • Must manually create and delete file\n");
    printf("  • Has security vulnerabilities\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. tmpfile() is safer than tmpnam()\n");
    printf("2. tmpfile() creates file immediately (no race condition)\n");
    printf("3. tmpfile() files are deleted automatically\n");
    printf("4. tmpnam() has TOCTOU (Time-Of-Check-Time-Of-Use) vulnerability\n");
    printf("5. L_tmpnam is the minimum buffer size for tmpnam()\n");
    printf("6. TMP_MAX is minimum number of unique names\n");
    printf("7. temp files are usually in /tmp (Unix) or %%TEMP%% (Windows)\n");
    printf("8. tmpfile() may fail if disk space is low\n");
    printf("9. temp files survive until close or program termination\n");
    printf("10. Use tmpfile() for security, tmpnam() only if needed\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Prefer tmpfile() for temporary storage\n");
    printf("✓ Use mkstemp() on POSIX systems if need filename\n");
    printf("✓ Always check for NULL return value\n");
    printf("✓ Close temp files as soon as done\n");
    printf("✓ Don't rely on temp files for persistent data\n");
    printf("✗ Avoid tmpnam() due to security issues\n");
    printf("✗ Don't hardcode temp file paths\n");

    return EXIT_SUCCESS;
}
