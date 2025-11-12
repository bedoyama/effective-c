#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("=== fflush() Examples ===\n\n");
    printf("Function: int fflush(FILE *stream)\n");
    printf("Purpose: Flush the output buffer of a stream\n");
    printf("Returns: 0 on success, EOF on error\n\n");

    // Example 1: Basic fflush usage
    printf("Example 1: Basic fflush() with file\n");
    {
        FILE *fp = fopen("fflush_test.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Line 1\n");
            fprintf(fp, "Line 2\n");

            printf("  Data written to buffer (not yet on disk)\n");

            // Force write to disk
            if (fflush(fp) == 0)
            {
                printf("  ✓ fflush() succeeded - data now on disk\n");
            }

            fprintf(fp, "Line 3\n");
            fclose(fp); // fclose() also flushes
        }
        printf("\n");
    }

    // Example 2: fflush with stdout (prompt without newline)
    printf("Example 2: fflush(stdout) - prompt without newline\n");
    {
        printf("  Enter something: ");
        fflush(stdout); // Force prompt to appear before input

        // Simulate user input with a small delay
        printf("[waiting...]\n");
        printf("  ✓ Prompt appeared immediately due to fflush(stdout)\n");
        printf("\n");
    }

    // Example 3: Without fflush - output may be delayed
    printf("Example 3: Output without fflush (may be buffered)\n");
    {
        FILE *fp = fopen("no_flush.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "This data stays in buffer");
            printf("  Data written to buffer\n");

            // If program crashes here, data might be lost!
            // fflush(fp) would ensure it's written to disk

            sleep(1);
            printf("  Without fflush(), data written only at fclose()\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Example 4: fflush(NULL) - flush all output streams
    printf("Example 4: fflush(NULL) - flush all open output streams\n");
    {
        FILE *fp1 = fopen("file1.txt", "w");
        FILE *fp2 = fopen("file2.txt", "w");
        FILE *fp3 = fopen("file3.txt", "w");

        if (fp1 && fp2 && fp3)
        {
            fprintf(fp1, "Data in file 1\n");
            fprintf(fp2, "Data in file 2\n");
            fprintf(fp3, "Data in file 3\n");
            printf("  Data written to 3 files\n");

            // Flush all output streams at once
            fflush(NULL);
            printf("  ✓ fflush(NULL) flushed all output streams\n");

            fclose(fp1);
            fclose(fp2);
            fclose(fp3);
        }
        printf("\n");
    }

    // Example 5: Error handling with fflush
    printf("Example 5: Error handling\n");
    {
        FILE *fp = fopen("error_test.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Some data\n");

            int result = fflush(fp);
            if (result == 0)
            {
                printf("  ✓ fflush() returned 0 (success)\n");
            }
            else if (result == EOF)
            {
                printf("  ✗ fflush() returned EOF (error)\n");
                perror("  Error");
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Example 6: fflush with stdin (undefined behavior in standard, but common)
    printf("Example 6: fflush(stdin) - behavior is implementation-defined\n");
    {
        printf("  fflush(stdin) is NOT part of standard C\n");
        printf("  Behavior is undefined/implementation-defined\n");
        printf("  Some systems use it to clear input buffer\n");
        printf("  Better alternatives:\n");
        printf("    • Read and discard: while(getchar() != '\\n');\n");
        printf("    • Use platform-specific functions\n");
        printf("\n");
    }

    // Example 7: When fflush is needed
    printf("Example 7: Common use cases for fflush()\n");
    {
        printf("  Use cases:\n");
        printf("  1. Interactive prompts (fflush(stdout))\n");
        printf("  2. Ensure critical data is written to disk\n");
        printf("  3. Before reading from same stream (r+ mode)\n");
        printf("  4. Debugging - force log output to appear\n");
        printf("  5. Before fork() to prevent duplicate output\n");
        printf("  6. Progress indicators without newlines\n");
        printf("\n");
    }

    // Example 8: Progress indicator using fflush
    printf("Example 8: Progress indicator with fflush()\n");
    {
        printf("  Progress: ");
        for (int i = 0; i <= 100; i += 20)
        {
            printf("%d%% ", i);
            fflush(stdout); // Force immediate output
            usleep(200000); // Sleep 200ms
        }
        printf("\n  ✓ Each percentage appeared immediately\n");
        printf("\n");
    }

    // Example 9: Buffering demonstration
    printf("Example 9: Demonstrating buffering\n");
    {
        FILE *fp = fopen("buffered_demo.txt", "w");
        if (fp != NULL)
        {
            // Write small amounts (stays in buffer)
            for (int i = 1; i <= 5; i++)
            {
                fprintf(fp, "Line %d\n", i);
            }
            printf("  5 lines written to buffer\n");

            // Check file size (might be 0 if not flushed)
            fflush(fp);
            printf("  ✓ After fflush(), data is on disk\n");

            fclose(fp);
        }
        printf("\n");
    }

    // Example 10: fflush return value
    printf("Example 10: Checking fflush() return value\n");
    {
        FILE *fp = fopen("return_test.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Test data\n");

            int result = fflush(fp);
            printf("  fflush() return value: %d\n", result);
            printf("  0 = success, EOF = error\n");

            if (result == 0)
            {
                printf("  ✓ Flush successful\n");
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Clean up test files
    remove("fflush_test.txt");
    remove("no_flush.txt");
    remove("file1.txt");
    remove("file2.txt");
    remove("file3.txt");
    remove("error_test.txt");
    remove("buffered_demo.txt");
    remove("return_test.txt");

    printf("=== Summary ===\n\n");
    printf("Prototype:\n");
    printf("  int fflush(FILE *stream);\n\n");

    printf("Parameters:\n");
    printf("  stream - FILE pointer to flush, or NULL for all streams\n\n");

    printf("Return Value:\n");
    printf("  0 on success\n");
    printf("  EOF on error (sets errno)\n\n");

    printf("Important Notes:\n");
    printf("  1. fflush() writes buffered output data to file\n");
    printf("  2. fflush(NULL) flushes all output streams\n");
    printf("  3. fflush(stdin) is undefined behavior in standard C\n");
    printf("  4. fclose() automatically flushes before closing\n");
    printf("  5. Only works on output streams (write mode)\n");
    printf("  6. Critical for interactive programs and critical data\n");
    printf("  7. May impact performance if overused\n");
    printf("  8. Necessary before switching between read/write on r+ streams\n\n");

    printf("Best Practices:\n");
    printf("  ✓ Use fflush(stdout) for prompts without newlines\n");
    printf("  ✓ Flush critical data before potential program termination\n");
    printf("  ✓ Check return value for error handling\n");
    printf("  ✓ Use fflush(NULL) before fork() to prevent duplicates\n");
    printf("  ✗ Don't use fflush(stdin) - undefined behavior\n");
    printf("  ✗ Don't overuse - impacts performance\n");

    return EXIT_SUCCESS;
}
