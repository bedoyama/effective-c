#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== Setting the Position in a File ===\n\n");

    // Create a test file
    FILE *fp = fopen("test_position.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to create test file\n");
        return EXIT_FAILURE;
    }
    fprintf(fp, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    fclose(fp);

    // Test 1: ftell - get current position
    printf("Test 1: ftell() - get current file position\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            long pos = ftell(fp);
            printf("  Initial position: %ld\n", pos);

            fgetc(fp);
            fgetc(fp);
            fgetc(fp);

            pos = ftell(fp);
            printf("  After reading 3 chars: %ld\n", pos);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 2: fseek - set position
    printf("Test 2: fseek() - set file position\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            // Seek to position 10
            fseek(fp, 10, SEEK_SET);
            int ch = fgetc(fp);
            printf("  Character at position 10: '%c'\n", ch);

            // Seek 5 bytes forward from current position
            fseek(fp, 5, SEEK_CUR);
            ch = fgetc(fp);
            printf("  Character 5 bytes forward: '%c'\n", ch);

            // Seek to 5 bytes before end
            fseek(fp, -5, SEEK_END);
            ch = fgetc(fp);
            printf("  Character 5 bytes from end: '%c'\n", ch);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 3: SEEK constants
    printf("Test 3: fseek() whence parameters\n");
    {
        printf("  SEEK_SET (0): Offset from beginning of file\n");
        printf("  SEEK_CUR (1): Offset from current position\n");
        printf("  SEEK_END (2): Offset from end of file\n");
        printf("\n");

        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            // Beginning
            fseek(fp, 0, SEEK_SET);
            printf("  SEEK_SET(0): '%c' (first char)\n", fgetc(fp));

            // Current + 5
            fseek(fp, 5, SEEK_CUR);
            printf("  SEEK_CUR(5): '%c'\n", fgetc(fp));

            // End - 1
            fseek(fp, -1, SEEK_END);
            printf("  SEEK_END(-1): '%c' (last char)\n", fgetc(fp));

            fclose(fp);
        }
        printf("\n");
    }

    // Test 4: rewind - go to beginning
    printf("Test 4: rewind() - reset to beginning\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            // Read some data
            char buffer[10];
            fgets(buffer, sizeof(buffer), fp);
            printf("  First read: %s\n", buffer);
            printf("  Position: %ld\n", ftell(fp));

            // Rewind to beginning
            rewind(fp);
            printf("  After rewind: %ld\n", ftell(fp));

            // Read again
            fgets(buffer, sizeof(buffer), fp);
            printf("  Second read: %s\n", buffer);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 5: fgetpos and fsetpos
    printf("Test 5: fgetpos() and fsetpos() - save/restore position\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            fpos_t saved_pos;

            // Read some data
            char buffer[10];
            fgets(buffer, sizeof(buffer), fp);
            printf("  Read: %s\n", buffer);

            // Save current position
            fgetpos(fp, &saved_pos);
            printf("  ✓ Saved position\n");

            // Read more data
            fgets(buffer, sizeof(buffer), fp);
            printf("  Read more: %s\n", buffer);

            // Restore saved position
            fsetpos(fp, &saved_pos);
            printf("  ✓ Restored position\n");

            // Read again from saved position
            fgets(buffer, sizeof(buffer), fp);
            printf("  Read from saved pos: %s\n", buffer);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 6: File size using fseek
    printf("Test 6: Getting file size with fseek()\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            // Seek to end
            fseek(fp, 0, SEEK_END);

            // Get position (file size)
            long size = ftell(fp);
            printf("  File size: %ld bytes\n", size);

            // Go back to beginning
            rewind(fp);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 7: Random access example
    printf("Test 7: Random access to file\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            int positions[] = {0, 10, 20, 30, 5};

            for (int i = 0; i < 5; i++)
            {
                fseek(fp, positions[i], SEEK_SET);
                int ch = fgetc(fp);
                printf("  Position %d: '%c'\n", positions[i], ch);
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 8: Error handling with fseek
    printf("Test 8: fseek() error handling\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            // Valid seek
            if (fseek(fp, 0, SEEK_SET) == 0)
            {
                printf("  ✓ fseek() succeeded\n");
            }

            // May fail on some streams (pipes, terminals)
            if (fseek(fp, -1000, SEEK_SET) != 0)
            {
                printf("  ⚠ fseek() failed (negative position)\n");
            }

            fclose(fp);
        }
        printf("\n");
    }

    // Test 9: Binary file positioning
    printf("Test 9: Binary file positioning\n");
    {
        // Create binary file
        FILE *fp = fopen("test_binary_pos.dat", "wb");
        if (fp != NULL)
        {
            int data[] = {10, 20, 30, 40, 50};
            fwrite(data, sizeof(int), 5, fp);
            fclose(fp);
        }

        // Read with positioning
        fp = fopen("test_binary_pos.dat", "rb");
        if (fp != NULL)
        {
            // Read third integer
            fseek(fp, 2 * sizeof(int), SEEK_SET);
            int value;
            fread(&value, sizeof(int), 1, fp);
            printf("  Third integer: %d\n", value);

            // Go to first integer
            rewind(fp);
            fread(&value, sizeof(int), 1, fp);
            printf("  First integer: %d\n", value);

            fclose(fp);
        }
        printf("\n");
    }

    // Test 10: Text vs binary mode positioning
    printf("Test 10: Text vs binary mode positioning\n");
    {
        printf("  Text mode:\n");
        printf("    • Position may not be byte offset (newline conversion)\n");
        printf("    • Use fgetpos/fsetpos for portability\n");
        printf("    • ftell/fseek may give unexpected results\n");
        printf("\n");

        printf("  Binary mode:\n");
        printf("    • Position is always byte offset\n");
        printf("    • ftell/fseek work as expected\n");
        printf("    • More predictable behavior\n");
        printf("\n");
    }

    // Test 11: Clearing EOF and error indicators
    printf("Test 11: clearerr() - clear EOF and error indicators\n");
    {
        FILE *fp = fopen("test_position.txt", "r");
        if (fp != NULL)
        {
            // Read to EOF
            while (fgetc(fp) != EOF)
                ;

            if (feof(fp))
            {
                printf("  ✓ EOF reached\n");
            }

            // Clear EOF indicator
            clearerr(fp);
            printf("  ✓ clearerr() called\n");

            if (!feof(fp))
            {
                printf("  ✓ EOF indicator cleared\n");
            }

            // Now we can seek and read again
            rewind(fp);
            printf("  First char after rewind: '%c'\n", fgetc(fp));

            fclose(fp);
        }
        printf("\n");
    }

    printf("=== Function Summary ===\n\n");
    printf("Get Position:\n");
    printf("  ftell(fp)           - Returns current position (long)\n");
    printf("  fgetpos(fp, &pos)   - Saves position to fpos_t\n");
    printf("\n");

    printf("Set Position:\n");
    printf("  fseek(fp, off, whence) - Set position, returns 0 on success\n");
    printf("  fsetpos(fp, &pos)      - Restore saved position\n");
    printf("  rewind(fp)             - Go to beginning (= fseek(fp,0,SEEK_SET))\n");
    printf("\n");

    printf("Whence Values:\n");
    printf("  SEEK_SET - Beginning of file\n");
    printf("  SEEK_CUR - Current position\n");
    printf("  SEEK_END - End of file\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. ftell() returns -1L on error\n");
    printf("2. fseek() returns 0 on success, non-zero on error\n");
    printf("3. rewind() also clears error indicators\n");
    printf("4. Use fgetpos/fsetpos for large files (> 2GB)\n");
    printf("5. Binary mode positioning is more predictable\n");
    printf("6. Text mode may have newline conversion issues\n");
    printf("7. fseek() may not work on all stream types\n");
    printf("8. clearerr() clears EOF and error indicators\n");
    printf("9. Position 0 is the beginning of the file\n");
    printf("10. Negative offsets with SEEK_END work backward\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Use fgetpos/fsetpos for text files\n");
    printf("✓ Use ftell/fseek for binary files\n");
    printf("✓ Always check return values\n");
    printf("✓ Open files in binary mode for precise positioning\n");
    printf("✓ Call clearerr() after reaching EOF if continuing\n");
    printf("✓ Use rewind() instead of fseek(fp, 0, SEEK_SET)\n");

    return EXIT_SUCCESS;
}
