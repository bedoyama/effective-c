#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    printf("=== unlink() Examples ===\n\n");
    printf("Function: int unlink(const char *path)\n");
    printf("Purpose: Remove/delete a file from the filesystem\n");
    printf("Returns: 0 on success, -1 on error (sets errno)\n\n");

    // Example 1: Basic unlink usage
    printf("Example 1: Basic unlink() to delete a file\n");
    {
        // Create a test file
        FILE *fp = fopen("test_unlink.txt", "w");
        if (fp != NULL)
        {
            fputs("This file will be deleted\n", fp);
            fclose(fp);
            printf("  ✓ Created test_unlink.txt\n");
        }

        // Delete the file
        if (unlink("test_unlink.txt") == 0)
        {
            printf("  ✓ Successfully deleted test_unlink.txt\n");
        }
        else
        {
            perror("  ✗ unlink failed");
        }
    }
    printf("\n");

    // Example 2: Error handling - file doesn't exist
    printf("Example 2: Error handling - file doesn't exist\n");
    {
        if (unlink("nonexistent_file.txt") == -1)
        {
            printf("  ✗ unlink failed (expected)\n");
            printf("  errno = %d\n", errno);
            perror("  Error");
        }
    }
    printf("\n");

    // Example 3: Deleting after closing file
    printf("Example 3: Proper pattern - close before unlink\n");
    {
        FILE *fp = fopen("temp_file.txt", "w");
        if (fp != NULL)
        {
            fputs("Temporary data\n", fp);

            // Always close before unlinking
            if (fclose(fp) == EOF)
            {
                fputs("  ✗ Failed to close file\n", stderr);
            }
            else
            {
                printf("  ✓ File closed\n");
            }

            // Now safe to unlink
            if (unlink("temp_file.txt") == 0)
            {
                printf("  ✓ File deleted\n");
            }
        }
    }
    printf("\n");

    // Example 4: Deleting while file is open (POSIX behavior)
    printf("Example 4: Deleting while file is still open\n");
    {
        FILE *fp = fopen("open_unlink.txt", "w");
        if (fp != NULL)
        {
            fputs("Data in file\n", fp);
            fflush(fp);

            // Unlink while file is still open
            if (unlink("open_unlink.txt") == 0)
            {
                printf("  ✓ File unlinked (directory entry removed)\n");
                printf("  Note: File descriptor still valid\n");

                // Can still write to the file!
                fputs("More data after unlink\n", fp);
                printf("  ✓ Can still write to open file\n");

                // File is actually deleted when closed
                fclose(fp);
                printf("  ✓ File physically deleted on close\n");
            }
        }
    }
    printf("\n");

    // Example 5: unlink vs remove
    printf("Example 5: unlink() vs remove()\n");
    {
        printf("  unlink():\n");
        printf("    • POSIX function (not standard C)\n");
        printf("    • Only works on files\n");
        printf("    • Returns -1 on error, sets errno\n");
        printf("\n");

        printf("  remove():\n");
        printf("    • Standard C function\n");
        printf("    • Works on files and empty directories\n");
        printf("    • More portable\n");
        printf("    • Returns non-zero on error\n");
    }
    printf("\n");

    // Example 6: Checking if file exists before unlink
    printf("Example 6: Check file existence before unlink\n");
    {
        const char *filename = "check_before_delete.txt";

        // Create file
        FILE *fp = fopen(filename, "w");
        if (fp != NULL)
        {
            fputs("Test\n", fp);
            fclose(fp);
        }

        // Try to open for reading to check existence
        fp = fopen(filename, "r");
        if (fp != NULL)
        {
            fclose(fp);
            printf("  File exists, deleting...\n");

            if (unlink(filename) == 0)
            {
                printf("  ✓ File deleted successfully\n");
            }
        }
        else
        {
            printf("  File doesn't exist\n");
        }
    }
    printf("\n");

    // Example 7: Multiple unlink attempts
    printf("Example 7: Attempting to delete same file twice\n");
    {
        // Create file
        FILE *fp = fopen("double_delete.txt", "w");
        if (fp != NULL)
        {
            fclose(fp);
        }

        // First unlink - should succeed
        if (unlink("double_delete.txt") == 0)
        {
            printf("  ✓ First unlink succeeded\n");
        }

        // Second unlink - should fail
        if (unlink("double_delete.txt") == -1)
        {
            printf("  ✗ Second unlink failed (expected)\n");
            perror("  Error");
        }
    }
    printf("\n");

    // Example 8: Unlinking with relative and absolute paths
    printf("Example 8: Path handling\n");
    {
        // Relative path
        FILE *fp = fopen("relative_path.txt", "w");
        if (fp != NULL)
        {
            fclose(fp);
            if (unlink("relative_path.txt") == 0)
            {
                printf("  ✓ Deleted with relative path\n");
            }
        }

        // Path with directory
        fp = fopen("./another_file.txt", "w");
        if (fp != NULL)
        {
            fclose(fp);
            if (unlink("./another_file.txt") == 0)
            {
                printf("  ✓ Deleted with ./ prefix\n");
            }
        }
    }
    printf("\n");

    // Example 9: Common error codes
    printf("Example 9: Common errno values\n");
    {
        printf("  EACCES  - Permission denied\n");
        printf("  ENOENT  - File doesn't exist\n");
        printf("  EISDIR  - Path is a directory (use rmdir)\n");
        printf("  EROFS   - Read-only filesystem\n");
        printf("  EBUSY   - File is in use\n");
    }
    printf("\n");

    // Example 10: Use cases
    printf("Example 10: Common use cases\n");
    {
        printf("  Use cases:\n");
        printf("  1. Deleting temporary files\n");
        printf("  2. Cleaning up after error conditions\n");
        printf("  3. Removing old log files\n");
        printf("  4. Implementing file rotation\n");
        printf("  5. Atomic file replacement (unlink old after rename)\n");
    }
    printf("\n");

    printf("=== Summary ===\n\n");
    printf("Prototype:\n");
    printf("  int unlink(const char *path);\n");
    printf("  Header: <unistd.h>\n\n");

    printf("Parameters:\n");
    printf("  path - pathname of file to remove\n\n");

    printf("Return Value:\n");
    printf("  0 on success\n");
    printf("  -1 on error (errno set)\n\n");

    printf("Important Notes:\n");
    printf("  1. POSIX function, not standard C (use remove() for portability)\n");
    printf("  2. Only works on files, not directories (use rmdir() for directories)\n");
    printf("  3. Removes directory entry, not necessarily the file data\n");
    printf("  4. File data deleted when last file descriptor is closed\n");
    printf("  5. Can unlink open files (deleted on close)\n");
    printf("  6. Requires write permission on directory, not file\n");
    printf("  7. Check errno for error details\n");
    printf("  8. Not atomic with other operations\n\n");

    printf("Best Practices:\n");
    printf("  ✓ Close files before unlinking when possible\n");
    printf("  ✓ Check return value and errno\n");
    printf("  ✓ Use remove() for portable code\n");
    printf("  ✓ Handle permission and existence errors gracefully\n");
    printf("  ✗ Don't assume file is immediately deleted\n");
    printf("  ✗ Don't use on directories (use rmdir() instead)\n");

    return EXIT_SUCCESS;
}
