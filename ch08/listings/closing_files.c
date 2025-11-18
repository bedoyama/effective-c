#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== Closing Files ===\n\n");

    // Test 1: Basic fclose usage
    printf("Test 1: Basic fclose() usage\n");
    {
        FILE *fp = fopen("test_close.txt", "w");
        if (fp == NULL)
        {
            fprintf(stderr, "  Failed to open file\n");
            return EXIT_FAILURE;
        }

        fprintf(fp, "Test data\n");
        printf("  ✓ File opened and data written\n");

        int result = fclose(fp);
        if (result == 0)
        {
            printf("  ✓ File closed successfully\n");
        }
        else
        {
            printf("  ✗ Error closing file: %s\n", strerror(errno));
        }
        printf("\n");
    }

    // Test 2: Attempting to use file after closing
    printf("Test 2: File pointer after fclose() (invalid)\n");
    {
        FILE *fp = fopen("test_close2.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Data before close\n");
            fclose(fp);
            printf("  ✓ File closed\n");

            // This is WRONG - undefined behavior!
            // fprintf(fp, "Data after close\n"); // DON'T DO THIS!
            printf("  ⚠ Using file pointer after fclose() is undefined behavior\n");
            printf("  ⚠ Never use fp after fclose(fp)\n");
        }
        printf("\n");
    }

    // Test 3: Closing NULL pointer (safe)
    printf("Test 3: Closing NULL pointer\n");
    {
        FILE *fp = NULL;
        // Many implementations handle this gracefully, but it's not guaranteed
        // if (fp != NULL) fclose(fp); // Recommended pattern

        printf("  ✓ Always check for NULL before fclose()\n");
        printf("  ✓ Safe pattern: if (fp != NULL) fclose(fp);\n");
        printf("\n");
    }

    // Test 4: fclose return value
    printf("Test 4: Checking fclose() return value\n");
    {
        FILE *fp = fopen("test_close3.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Important data\n");

            int result = fclose(fp);
            if (result == EOF)
            {
                printf("  ✗ fclose() failed: %s\n", strerror(errno));
                printf("  ⚠ Data may not be fully written to disk\n");
            }
            else
            {
                printf("  ✓ fclose() returned 0 (success)\n");
                printf("  ✓ All buffered data has been flushed to disk\n");
            }
        }
        printf("\n");
    }

    // Test 5: Standard streams - don't close them!
    printf("Test 5: Standard streams (don't close!)\n");
    {
        printf("  stdout: Should NOT be closed\n");
        fprintf(stderr, "  stderr: Should NOT be closed\n");
        printf("  stdin: Should NOT be closed\n");
        printf("  ⚠ Closing standard streams causes undefined behavior\n");
        printf("  ⚠ They are automatically closed at program exit\n");
        printf("\n");
    }

    // Test 6: Multiple file handling
    printf("Test 6: Closing multiple files\n");
    {
        FILE *files[3];
        const char *names[] = {"file1.txt", "file2.txt", "file3.txt"};

        // Open multiple files
        for (int i = 0; i < 3; i++)
        {
            files[i] = fopen(names[i], "w");
            if (files[i] == NULL)
            {
                fprintf(stderr, "  Failed to open %s\n", names[i]);
                // Close any files we already opened
                for (int j = 0; j < i; j++)
                {
                    fclose(files[j]);
                }
                return EXIT_FAILURE;
            }
            fprintf(files[i], "Data in %s\n", names[i]);
        }
        printf("  ✓ Opened 3 files\n");

        // Close all files
        for (int i = 0; i < 3; i++)
        {
            if (fclose(files[i]) == 0)
            {
                printf("  ✓ Closed %s\n", names[i]);
            }
        }
        printf("\n");
    }

    // Test 7: Error handling pattern
    printf("Test 7: Proper error handling pattern\n");
    {
        FILE *fp = fopen("test_pattern.txt", "w");
        if (fp == NULL)
        {
            fprintf(stderr, "  Failed to open file: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        // Do work with file
        if (fprintf(fp, "Important data\n") < 0)
        {
            fprintf(stderr, "  Write error: %s\n", strerror(errno));
            fclose(fp);
            return EXIT_FAILURE;
        }

        // Close and check for errors
        if (fclose(fp) == EOF)
        {
            fprintf(stderr, "  Error closing file: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        printf("  ✓ File operations completed successfully\n");
        printf("  ✓ Proper error handling at each step\n");
        printf("\n");
    }

    // Test 8: Resource cleanup with goto
    printf("Test 8: Resource cleanup pattern with goto\n");
    {
        FILE *fp1 = NULL, *fp2 = NULL;
        int success = 0;

        fp1 = fopen("resource1.txt", "w");
        if (fp1 == NULL)
        {
            printf("  Failed to open resource1.txt\n");
            goto cleanup;
        }

        fp2 = fopen("resource2.txt", "w");
        if (fp2 == NULL)
        {
            printf("  Failed to open resource2.txt\n");
            goto cleanup;
        }

        fprintf(fp1, "Data 1\n");
        fprintf(fp2, "Data 2\n");
        success = 1;

    cleanup:
        if (fp1 != NULL)
        {
            fclose(fp1);
            printf("  ✓ Closed resource1.txt\n");
        }
        if (fp2 != NULL)
        {
            fclose(fp2);
            printf("  ✓ Closed resource2.txt\n");
        }

        if (success)
        {
            printf("  ✓ All resources cleaned up properly\n");
        }
        printf("\n");
    }

    // Test 9: When fclose can fail
    printf("Test 9: Conditions where fclose() can fail\n");
    {
        printf("  fclose() can fail when:\n");
        printf("  • Buffered data cannot be written to disk\n");
        printf("  • Disk is full\n");
        printf("  • Network connection lost (for network filesystems)\n");
        printf("  • Permission issues\n");
        printf("  • Hardware errors\n");
        printf("  ⚠ Always check fclose() return value for critical data\n");
        printf("\n");
    }

    printf("=== Important Notes ===\n");
    printf("1. fclose() flushes buffered data to disk\n");
    printf("2. Returns 0 on success, EOF on error\n");
    printf("3. Never use file pointer after fclose()\n");
    printf("4. Always check for NULL before closing\n");
    printf("5. Don't close stdin, stdout, stderr\n");
    printf("6. File is closed automatically at program exit\n");
    printf("7. But explicit fclose() is good practice\n");
    printf("8. Check return value for critical operations\n");
    printf("9. Use goto for cleanup in complex error handling\n");
    printf("10. Closing writes buffered data or returns error\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Always fclose() files you opened\n");
    printf("✓ Check fclose() return value for important data\n");
    printf("✓ Set pointer to NULL after fclose() to prevent reuse\n");
    printf("✓ Close files in reverse order of opening (LIFO)\n");
    printf("✓ Use cleanup patterns for multiple files\n");
    printf("✓ Close files as soon as you're done with them\n");

    return EXIT_SUCCESS;
}
