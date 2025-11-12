#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main(void)
{
    printf("=== mkstemp() Examples ===\n\n");
    printf("Function: int mkstemp(char *template)\n");
    printf("Purpose: Create a unique temporary file securely\n");
    printf("Returns: File descriptor on success, -1 on error\n\n");

    // Example 1: Basic mkstemp usage
    printf("Example 1: Basic mkstemp() usage\n");
    {
        char template[] = "/tmp/tempfile_XXXXXX";
        int fd = mkstemp(template);

        if (fd == -1)
        {
            perror("  ✗ mkstemp failed");
        }
        else
        {
            printf("  ✓ Created temporary file: %s\n", template);
            printf("  File descriptor: %d\n", fd);

            // Write some data
            const char *data = "Hello from mkstemp\n";
            write(fd, data, strlen(data));

            // Close the file
            close(fd);

            // Clean up
            unlink(template);
        }
    }
    printf("\n");

    // Example 2: Template pattern requirements
    printf("Example 2: Template must end with XXXXXX\n");
    {
        // Valid template
        char template1[] = "/tmp/myfile_XXXXXX";
        int fd1 = mkstemp(template1);
        if (fd1 != -1)
        {
            printf("  ✓ Valid template: %s\n", template1);
            close(fd1);
            unlink(template1);
        }

        // Invalid template - not enough X's (must be exactly 6)
        char template2[] = "/tmp/badfile_XXX";
        int fd2 = mkstemp(template2);
        if (fd2 == -1)
        {
            printf("  ✗ Invalid template (only 3 X's): %s\n", template2);
            perror("  Error");
        }
    }
    printf("\n");

    // Example 3: Using fdopen to get FILE pointer
    printf("Example 3: Converting file descriptor to FILE pointer\n");
    {
        char template[] = "/tmp/fdopen_test_XXXXXX";
        int fd = mkstemp(template);

        if (fd != -1)
        {
            printf("  ✓ Created: %s\n", template);

            // Convert fd to FILE* for easier I/O
            FILE *fp = fdopen(fd, "w+");
            if (fp != NULL)
            {
                fprintf(fp, "Line 1\n");
                fprintf(fp, "Line 2\n");
                fprintf(fp, "Line 3\n");
                printf("  ✓ Wrote data using fprintf()\n");

                // Read it back
                rewind(fp);
                char buffer[100];
                if (fgets(buffer, sizeof(buffer), fp) != NULL)
                {
                    printf("  Read back: %s", buffer);
                }

                fclose(fp); // This also closes fd
            }

            unlink(template);
        }
    }
    printf("\n");

    // Example 4: Multiple temporary files
    printf("Example 4: Creating multiple unique temporary files\n");
    {
        char template1[] = "/tmp/temp1_XXXXXX";
        char template2[] = "/tmp/temp2_XXXXXX";
        char template3[] = "/tmp/temp3_XXXXXX";

        int fd1 = mkstemp(template1);
        int fd2 = mkstemp(template2);
        int fd3 = mkstemp(template3);

        if (fd1 != -1 && fd2 != -1 && fd3 != -1)
        {
            printf("  ✓ File 1: %s\n", template1);
            printf("  ✓ File 2: %s\n", template2);
            printf("  ✓ File 3: %s\n", template3);
            printf("  All three files have unique names\n");

            close(fd1);
            close(fd2);
            close(fd3);
            unlink(template1);
            unlink(template2);
            unlink(template3);
        }
    }
    printf("\n");

    // Example 5: Custom directory location
    printf("Example 5: Temporary files in custom directory\n");
    {
        // Current directory
        char template1[] = "./mytemp_XXXXXX";
        int fd1 = mkstemp(template1);
        if (fd1 != -1)
        {
            printf("  ✓ Created in current dir: %s\n", template1);
            close(fd1);
            unlink(template1);
        }

        // /tmp directory (common for temp files)
        char template2[] = "/tmp/mytemp_XXXXXX";
        int fd2 = mkstemp(template2);
        if (fd2 != -1)
        {
            printf("  ✓ Created in /tmp: %s\n", template2);
            close(fd2);
            unlink(template2);
        }
    }
    printf("\n");

    // Example 6: mkstemp vs tmpfile comparison
    printf("Example 6: mkstemp() vs tmpfile()\n");
    {
        printf("  mkstemp():\n");
        printf("    • Returns file descriptor (int)\n");
        printf("    • File has a name (visible in filesystem)\n");
        printf("    • Must manually unlink()\n");
        printf("    • More control over file location\n");
        printf("    • POSIX function\n");
        printf("\n");

        printf("  tmpfile():\n");
        printf("    • Returns FILE pointer\n");
        printf("    • File is anonymous (unlinked immediately)\n");
        printf("    • Auto-deleted on close or exit\n");
        printf("    • Less control\n");
        printf("    • Standard C function\n");
    }
    printf("\n");

    // Example 7: Error handling
    printf("Example 7: Error handling\n");
    {
        // Try to create in non-existent directory
        char template[] = "/nonexistent/dir/temp_XXXXXX";
        int fd = mkstemp(template);

        if (fd == -1)
        {
            printf("  ✗ mkstemp failed (expected)\n");
            printf("  errno = %d\n", errno);
            perror("  Error");
        }
        else
        {
            close(fd);
            unlink(template);
        }
    }
    printf("\n");

    // Example 8: File permissions
    printf("Example 8: File permissions\n");
    {
        char template[] = "/tmp/perms_XXXXXX";
        int fd = mkstemp(template);

        if (fd != -1)
        {
            printf("  ✓ Created: %s\n", template);
            printf("  Default permissions: 0600 (rw-------)\n");
            printf("  Only the owner can read/write\n");
            printf("  More secure than tmpnam()\n");

            close(fd);
            unlink(template);
        }
    }
    printf("\n");

    // Example 9: Writing and reading data
    printf("Example 9: Complete write/read cycle\n");
    {
        char template[] = "/tmp/data_XXXXXX";
        int fd = mkstemp(template);

        if (fd != -1)
        {
            // Write data
            const char *write_data = "Important data: 12345\n";
            ssize_t written = write(fd, write_data, strlen(write_data));
            printf("  ✓ Wrote %zd bytes\n", written);

            // Seek back to beginning
            lseek(fd, 0, SEEK_SET);

            // Read data back
            char buffer[100];
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
            buffer[bytes_read] = '\0';
            printf("  Read back: %s", buffer);

            close(fd);
            unlink(template);
        }
    }
    printf("\n");

    // Example 10: Keeping temporary file (not unlinking immediately)
    printf("Example 10: Keeping temporary file for later use\n");
    {
        char template[] = "/tmp/keep_XXXXXX";
        int fd = mkstemp(template);

        if (fd != -1)
        {
            write(fd, "Saved data\n", 11);
            close(fd);

            printf("  ✓ Created and closed: %s\n", template);
            printf("  File still exists on filesystem\n");
            printf("  Can reopen later with: fopen(\"%s\", \"r\")\n", template);

            // Reopen the file
            FILE *fp = fopen(template, "r");
            if (fp != NULL)
            {
                char buffer[50];
                fgets(buffer, sizeof(buffer), fp);
                printf("  Reopened and read: %s", buffer);
                fclose(fp);
            }

            // Clean up
            unlink(template);
            printf("  ✓ Cleaned up\n");
        }
    }
    printf("\n");

    printf("=== Summary ===\n\n");
    printf("Prototype:\n");
    printf("  int mkstemp(char *template);\n");
    printf("  Header: <stdlib.h>\n\n");

    printf("Parameters:\n");
    printf("  template - String ending with \"XXXXXX\" (modified in place)\n\n");

    printf("Return Value:\n");
    printf("  File descriptor (>= 0) on success\n");
    printf("  -1 on error (errno set)\n\n");

    printf("Important Notes:\n");
    printf("  1. POSIX function (not standard C)\n");
    printf("  2. Template MUST end with exactly 6 X characters\n");
    printf("  3. Template is modified to contain the actual filename\n");
    printf("  4. Returns file descriptor (use fdopen() to get FILE*)\n");
    printf("  5. File is created with permissions 0600 (secure)\n");
    printf("  6. File is NOT automatically deleted (must unlink())\n");
    printf("  7. Creates file atomically (race-condition free)\n");
    printf("  8. File is opened in O_RDWR | O_CREAT | O_EXCL mode\n");
    printf("  9. More secure than tmpnam() or tempnam()\n");
    printf("  10. Template can be on stack or heap\n\n");

    printf("Best Practices:\n");
    printf("  ✓ Always use mkstemp() instead of tmpnam() for security\n");
    printf("  ✓ Unlink the file when no longer needed\n");
    printf("  ✓ Check return value for errors\n");
    printf("  ✓ Close file descriptor when done\n");
    printf("  ✓ Use fdopen() if you need FILE* operations\n");
    printf("  ✓ Put temp files in /tmp or use P_tmpdir\n");
    printf("  ✗ Don't use template strings with less than 6 X's\n");
    printf("  ✗ Don't forget to unlink() to avoid leaving temp files\n");

    return EXIT_SUCCESS;
}
