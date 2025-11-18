#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== Opening and Creating Files ===\n\n");

    // Test 1: Opening file for reading
    printf("Test 1: fopen() with \"r\" mode (read)\n");
    {
        FILE *fp = fopen("test_read.txt", "r");
        if (fp == NULL)
        {
            printf("  Failed to open test_read.txt for reading\n");
            printf("  Error: %s\n", strerror(errno));
            printf("  (File probably doesn't exist - this is expected)\n");
        }
        else
        {
            printf("  ✓ Successfully opened for reading\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 2: Opening file for writing (creates or truncates)
    printf("Test 2: fopen() with \"w\" mode (write)\n");
    {
        FILE *fp = fopen("test_write.txt", "w");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open file for writing\n");
            printf("  Error: %s\n", strerror(errno));
        }
        else
        {
            printf("  ✓ File opened for writing\n");
            fprintf(fp, "This is a test line.\n");
            printf("  ✓ Wrote data to file\n");
            fclose(fp);
            printf("  ✓ File closed (test_write.txt created)\n");
        }
        printf("\n");
    }

    // Test 3: Opening file for appending
    printf("Test 3: fopen() with \"a\" mode (append)\n");
    {
        FILE *fp = fopen("test_write.txt", "a");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open file for appending\n");
        }
        else
        {
            printf("  ✓ File opened for appending\n");
            fprintf(fp, "This line was appended.\n");
            printf("  ✓ Appended data to file\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 4: Opening file for reading and writing
    printf("Test 4: fopen() with \"r+\" mode (read and write)\n");
    {
        FILE *fp = fopen("test_write.txt", "r+");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open file for read/write\n");
        }
        else
        {
            printf("  ✓ File opened for read/write\n");
            char buffer[100];
            if (fgets(buffer, sizeof(buffer), fp))
            {
                printf("  Read: %s", buffer);
            }
            fprintf(fp, "Added with r+ mode.\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 5: Opening file with "w+" (write and read, truncate)
    printf("Test 5: fopen() with \"w+\" mode (write and read, truncate)\n");
    {
        FILE *fp = fopen("test_wplus.txt", "w+");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open file\n");
        }
        else
        {
            printf("  ✓ File opened (empty file created)\n");
            fprintf(fp, "Line 1\nLine 2\nLine 3\n");
            printf("  ✓ Wrote 3 lines\n");

            // Rewind to read what we wrote
            rewind(fp);
            char buffer[100];
            printf("  Reading back:\n");
            while (fgets(buffer, sizeof(buffer), fp))
            {
                printf("    %s", buffer);
            }
            fclose(fp);
        }
        printf("\n");
    }

    // Test 6: Opening file with "a+" (append and read)
    printf("Test 6: fopen() with \"a+\" mode (append and read)\n");
    {
        FILE *fp = fopen("test_aplus.txt", "a+");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open file\n");
        }
        else
        {
            printf("  ✓ File opened for append/read\n");
            fprintf(fp, "Appended line\n");

            // Rewind to read from beginning
            rewind(fp);
            char buffer[100];
            printf("  File contents:\n");
            while (fgets(buffer, sizeof(buffer), fp))
            {
                printf("    %s", buffer);
            }
            fclose(fp);
        }
        printf("\n");
    }

    // Test 7: Binary mode
    printf("Test 7: fopen() with binary mode \"wb\" and \"rb\"\n");
    {
        // Write binary data
        FILE *fp = fopen("test_binary.dat", "wb");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open binary file for writing\n");
        }
        else
        {
            int data[] = {10, 20, 30, 40, 50};
            size_t written = fwrite(data, sizeof(int), 5, fp);
            printf("  ✓ Wrote %zu integers in binary mode\n", written);
            fclose(fp);
        }

        // Read binary data
        fp = fopen("test_binary.dat", "rb");
        if (fp == NULL)
        {
            printf("  ✗ Failed to open binary file for reading\n");
        }
        else
        {
            int data[5];
            size_t read = fread(data, sizeof(int), 5, fp);
            printf("  ✓ Read %zu integers: ", read);
            for (size_t i = 0; i < read; i++)
            {
                printf("%d ", data[i]);
            }
            printf("\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 8: Error handling with ferror and feof
    printf("Test 8: Error checking with ferror() and feof()\n");
    {
        FILE *fp = fopen("test_write.txt", "r");
        if (fp != NULL)
        {
            char buffer[100];
            while (fgets(buffer, sizeof(buffer), fp))
            {
                // Reading...
            }

            if (ferror(fp))
            {
                printf("  ✗ Error occurred while reading\n");
            }
            else if (feof(fp))
            {
                printf("  ✓ Reached end of file normally\n");
            }
            fclose(fp);
        }
        printf("\n");
    }

    // Test 9: Standard streams
    printf("Test 9: Standard streams (stdin, stdout, stderr)\n");
    {
        printf("  stdout: Standard output stream (this message)\n");
        fprintf(stderr, "  stderr: Standard error stream (this error message)\n");
        printf("  stdin: Standard input stream (for reading user input)\n");
        printf("  All three are FILE* pointers automatically opened\n");
        printf("\n");
    }

    // Test 10: freopen - reopening a stream
    printf("Test 10: freopen() - redirect stream\n");
    {
        printf("  Before redirect: This goes to stdout\n");

        FILE *fp = freopen("test_redirect.txt", "w", stdout);
        if (fp == NULL)
        {
            fprintf(stderr, "  Failed to redirect stdout\n");
        }
        else
        {
            printf("This line goes to test_redirect.txt\n");
            printf("This line too!\n");

            // Restore stdout (on Unix-like systems)
            freopen("/dev/tty", "w", stdout);
            printf("  ✓ stdout redirected and restored\n");
        }
        printf("\n");
    }

    printf("=== File Open Modes Summary ===\n\n");
    printf("Mode  | Description                          | File Must Exist?\n");
    printf("------|--------------------------------------|------------------\n");
    printf("\"r\"   | Read only                            | Yes\n");
    printf("\"w\"   | Write only (truncate/create)         | No\n");
    printf("\"a\"   | Append only (create if needed)       | No\n");
    printf("\"r+\"  | Read and write                       | Yes\n");
    printf("\"w+\"  | Read and write (truncate/create)     | No\n");
    printf("\"a+\"  | Read and append (create if needed)   | No\n");
    printf("\n");
    printf("Add 'b' for binary mode: \"rb\", \"wb\", \"ab\", \"r+b\", \"w+b\", \"a+b\"\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. Always check if fopen() returns NULL\n");
    printf("2. Use strerror(errno) to get error description\n");
    printf("3. \"r\" fails if file doesn't exist\n");
    printf("4. \"w\" destroys existing file contents\n");
    printf("5. \"a\" always writes to end of file\n");
    printf("6. \"r+\" requires file to exist, doesn't truncate\n");
    printf("7. \"w+\" creates/truncates file\n");
    printf("8. \"a+\" creates file if needed, writes to end\n");
    printf("9. Binary mode ('b') is important on Windows\n");
    printf("10. Always fclose() when done\n");

    return EXIT_SUCCESS;
}
