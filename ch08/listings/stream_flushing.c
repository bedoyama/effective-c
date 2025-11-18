#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== Stream Flushing ===\n\n");

    // Test 1: Basic fflush usage
    printf("Test 1: fflush() - flush output buffer\n");
    {
        FILE *fp = fopen("test_flush.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Before flush");
            printf("  ✓ Data written to buffer\n");

            fflush(fp); // Force write to disk
            printf("  ✓ Buffer flushed to disk with fflush()\n");

            fprintf(fp, " After flush\n");
            fclose(fp); // fclose() also flushes
        }
        printf("\n");
    }

    // Test 2: fflush with stdout
    printf("Test 2: Flushing stdout\n");
    {
        printf("  Printing without newline...");
        fflush(stdout); // Force output to appear immediately
        // In a real program, you might do some work here
        printf(" Done!\n");
        printf("  ✓ fflush(stdout) ensures output appears immediately\n");
        printf("\n");
    }

    // Test 3: Buffering modes
    printf("Test 3: Buffering modes with setvbuf()\n");
    {
        FILE *fp = fopen("test_buffering.txt", "w");
        if (fp != NULL)
        {
            // Unbuffered
            setvbuf(fp, NULL, _IONBF, 0);
            fprintf(fp, "Unbuffered");
            printf("  _IONBF: No buffering, immediate write\n");
            fclose(fp);
        }

        fp = fopen("test_buffering.txt", "w");
        if (fp != NULL)
        {
            // Line buffered
            setvbuf(fp, NULL, _IOLBF, 0);
            fprintf(fp, "Line buffered\n");
            printf("  _IOLBF: Line buffered, flush on newline\n");
            fclose(fp);
        }

        fp = fopen("test_buffering.txt", "w");
        if (fp != NULL)
        {
            // Fully buffered
            char buffer[BUFSIZ];
            setvbuf(fp, buffer, _IOFBF, BUFSIZ);
            fprintf(fp, "Fully buffered");
            printf("  _IOFBF: Fully buffered, flush when buffer fills\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 4: Default buffering behavior
    printf("Test 4: Default buffering behavior\n");
    {
        printf("  stdout: Usually line-buffered (if terminal)\n");
        fprintf(stderr, "  stderr: Usually unbuffered (immediate output)\n");
        printf("  files: Usually fully buffered\n");
        printf("\n");
    }

    // Test 5: fflush(NULL) - flush all streams
    printf("Test 5: fflush(NULL) - flush all output streams\n");
    {
        FILE *fp1 = fopen("flush1.txt", "w");
        FILE *fp2 = fopen("flush2.txt", "w");

        if (fp1 && fp2)
        {
            fprintf(fp1, "Data in file 1");
            fprintf(fp2, "Data in file 2");
            printf("  Data written to two files\n");

            fflush(NULL); // Flush all output streams
            printf("  ✓ fflush(NULL) flushed all streams\n");

            fclose(fp1);
            fclose(fp2);
        }
        printf("\n");
    }

    // Test 6: When to use fflush
    printf("Test 6: When to use fflush()\n");
    {
        printf("  Use cases for fflush():\n");
        printf("  1. Before reading after writing\n");
        printf("  2. To ensure prompt appears before input\n");
        printf("  3. Before long computations (show progress)\n");
        printf("  4. Before fork() to avoid duplicate output\n");
        printf("  5. In interactive programs\n");
        printf("  6. For critical logging/debugging output\n");
        printf("\n");
    }

    // Test 7: Interactive prompt example
    printf("Test 7: Interactive prompt (demonstration)\n");
    {
        printf("  Typical interactive pattern:\n");
        printf("    printf(\"Enter value: \");\n");
        printf("    fflush(stdout);  // Ensure prompt appears\n");
        printf("    scanf(\"%%d\", &value);\n");
        printf("\n");
    }

    // Test 8: fflush with input streams (undefined)
    printf("Test 8: fflush() with input streams\n");
    {
        printf("  ⚠ fflush() on input streams is undefined in C standard\n");
        printf("  ⚠ Some systems support it, some don't\n");
        printf("  ⚠ Use only with output streams for portability\n");
        printf("\n");
    }

    // Test 9: Performance considerations
    printf("Test 9: Performance impact of fflush()\n");
    {
        FILE *fp = fopen("test_performance.txt", "w");
        if (fp != NULL)
        {
            // Without fflush - buffered
            for (int i = 0; i < 1000; i++)
            {
                fprintf(fp, "Line %d\n", i);
            }
            printf("  Written 1000 lines (buffered, fast)\n");

            // Reopen for comparison
            fclose(fp);
            fp = fopen("test_performance2.txt", "w");

            // With fflush after each write - slower
            for (int i = 0; i < 100; i++)
            {
                fprintf(fp, "Line %d\n", i);
                fflush(fp); // Forces disk write each time
            }
            printf("  Written 100 lines with fflush each time (slower)\n");
            printf("  ⚠ Excessive fflush() can hurt performance\n");

            fclose(fp);
        }
        printf("\n");
    }

    // Test 10: Custom buffer with setbuf
    printf("Test 10: setbuf() - set buffer\n");
    {
        FILE *fp = fopen("test_setbuf.txt", "w");
        if (fp != NULL)
        {
            char buffer[BUFSIZ];

            // Set custom buffer
            setbuf(fp, buffer);
            printf("  ✓ Set custom buffer of size %d\n", BUFSIZ);

            // Disable buffering
            FILE *fp2 = fopen("test_nobuf.txt", "w");
            if (fp2 != NULL)
            {
                setbuf(fp2, NULL); // Disable buffering
                printf("  ✓ Disabled buffering with setbuf(fp, NULL)\n");
                fclose(fp2);
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 11: Checking if flush succeeded
    printf("Test 11: Error checking with fflush()\n");
    {
        FILE *fp = fopen("test_flush_check.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Important data\n");

            if (fflush(fp) == EOF)
            {
                printf("  ✗ fflush() failed\n");
            }
            else
            {
                printf("  ✓ fflush() succeeded\n");
            }

            fclose(fp);
        }
        printf("\n");
    }

    printf("=== Buffering Modes Summary ===\n\n");
    printf("Mode    | Constant | Behavior\n");
    printf("--------|----------|------------------------------------------\n");
    printf("Unbuf   | _IONBF   | No buffering, immediate write\n");
    printf("Line    | _IOLBF   | Buffer flushed on newline or full\n");
    printf("Full    | _IOFBF   | Buffer flushed when full or explicitly\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. fflush() forces buffered data to be written\n");
    printf("2. Returns 0 on success, EOF on error\n");
    printf("3. fflush(NULL) flushes all output streams\n");
    printf("4. fflush() on input streams is undefined behavior\n");
    printf("5. fclose() automatically flushes the stream\n");
    printf("6. Excessive fflush() can hurt performance\n");
    printf("7. Use fflush(stdout) before interactive input\n");
    printf("8. stderr is usually unbuffered by default\n");
    printf("9. stdout is line-buffered if connected to terminal\n");
    printf("10. Files are fully buffered by default\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Flush stdout before long computations\n");
    printf("✓ Flush before fork() in Unix programs\n");
    printf("✓ Use for critical logging/debugging output\n");
    printf("✓ Let fclose() handle normal flushing\n");
    printf("✓ Check fflush() return value for critical data\n");
    printf("✗ Don't flush unnecessarily (performance)\n");
    printf("✗ Don't assume fflush() works on input streams\n");

    return EXIT_SUCCESS;
}
