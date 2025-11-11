#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("=== Removing and Renaming Files ===\n\n");

    // Test 1: Creating files for demonstration
    printf("Test 1: Creating test files\n");
    {
        FILE *fp1 = fopen("file_to_remove.txt", "w");
        FILE *fp2 = fopen("file_to_rename.txt", "w");
        FILE *fp3 = fopen("rename_target.txt", "w");

        if (fp1 && fp2 && fp3)
        {
            fprintf(fp1, "This file will be removed\n");
            fprintf(fp2, "This file will be renamed\n");
            fprintf(fp3, "This is the rename target\n");
            fclose(fp1);
            fclose(fp2);
            fclose(fp3);
            printf("  ✓ Created test files\n");
        }
        printf("\n");
    }

    // Test 2: remove - delete a file
    printf("Test 2: remove() - delete a file\n");
    {
        if (remove("file_to_remove.txt") == 0)
        {
            printf("  ✓ File removed successfully\n");
        }
        else
        {
            printf("  ✗ Failed to remove file\n");
            perror("  Error");
        }

        // Try to open the removed file
        FILE *fp = fopen("file_to_remove.txt", "r");
        if (fp == NULL)
        {
            printf("  ✓ Confirmed: file no longer exists\n");
        }
        else
        {
            printf("  ✗ File still exists!\n");
            fclose(fp);
        }
        printf("\n");
    }

    // Test 3: remove - trying to remove non-existent file
    printf("Test 3: remove() on non-existent file\n");
    {
        if (remove("nonexistent_file.txt") != 0)
        {
            printf("  ✓ remove() failed as expected\n");
            perror("  Error");
        }
        printf("\n");
    }

    // Test 4: rename - rename a file
    printf("Test 4: rename() - rename a file\n");
    {
        if (rename("file_to_rename.txt", "renamed_file.txt") == 0)
        {
            printf("  ✓ File renamed successfully\n");
            printf("    file_to_rename.txt -> renamed_file.txt\n");

            // Verify old name doesn't exist
            FILE *fp = fopen("file_to_rename.txt", "r");
            if (fp == NULL)
            {
                printf("  ✓ Old filename no longer exists\n");
            }
            else
            {
                fclose(fp);
            }

            // Verify new name exists
            fp = fopen("renamed_file.txt", "r");
            if (fp != NULL)
            {
                printf("  ✓ New filename exists\n");
                fclose(fp);
            }
        }
        else
        {
            printf("  ✗ Failed to rename file\n");
            perror("  Error");
        }
        printf("\n");
    }

    // Test 5: rename - moving a file (same filesystem)
    printf("Test 5: rename() - moving a file\n");
    {
        // Create a file to move
        FILE *fp = fopen("file_to_move.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "Moving this file\n");
            fclose(fp);
        }

        // Note: On Unix, can move to different directory if same filesystem
        // This is a simple rename in the same directory
        if (rename("file_to_move.txt", "moved_file.txt") == 0)
        {
            printf("  ✓ File moved/renamed\n");
        }
        else
        {
            printf("  ✗ Failed to move file\n");
            perror("  Error");
        }
        printf("\n");
    }

    // Test 6: rename with existing target
    printf("Test 6: rename() - target file exists\n");
    {
        // This will overwrite rename_target.txt (platform-dependent behavior)
        printf("  Attempting to rename to existing file...\n");
        if (rename("renamed_file.txt", "rename_target.txt") == 0)
        {
            printf("  ✓ Target file was overwritten (Unix behavior)\n");
        }
        else
        {
            printf("  ✗ rename() failed (Windows may prevent overwrite)\n");
            perror("  Error");
        }
        printf("\n");
    }

    // Test 7: Removing a file that's open
    printf("Test 7: Removing an open file\n");
    {
        FILE *fp = fopen("open_file.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "This file is open\n");
            fflush(fp);

            // On Unix: remove succeeds, file deleted after close
            // On Windows: remove may fail
            printf("  Attempting to remove open file...\n");
            if (remove("open_file.txt") == 0)
            {
                printf("  ✓ remove() succeeded (Unix: file marked for deletion)\n");
            }
            else
            {
                printf("  ✗ remove() failed (Windows: file is locked)\n");
                perror("  Error");
            }

            fclose(fp);
            printf("  ✓ File closed\n");
        }
        printf("\n");
    }

    // Test 8: rename - error cases
    printf("Test 8: rename() error cases\n");
    {
        printf("  Common rename() failures:\n");
        printf("  • Source file doesn't exist\n");
        printf("  • Insufficient permissions\n");
        printf("  • Target is in different filesystem (some systems)\n");
        printf("  • Target is a directory (some systems)\n");
        printf("  • File is open/locked\n");
        printf("\n");
    }

    // Test 9: Safe file replacement pattern
    printf("Test 9: Safe file replacement pattern\n");
    {
        const char *original = "important.txt";
        const char *temp = "important.txt.tmp";
        const char *backup = "important.txt.bak";

        // Create original file
        FILE *fp = fopen(original, "w");
        if (fp != NULL)
        {
            fprintf(fp, "Important original data\n");
            fclose(fp);
        }

        // Write new content to temporary file
        fp = fopen(temp, "w");
        if (fp != NULL)
        {
            fprintf(fp, "New important data\n");
            fclose(fp);
            printf("  ✓ Wrote new data to temporary file\n");
        }

        // Backup original
        if (rename(original, backup) == 0)
        {
            printf("  ✓ Backed up original file\n");

            // Move temp to original
            if (rename(temp, original) == 0)
            {
                printf("  ✓ Replaced with new file\n");
                printf("  ✓ Safe replacement complete\n");

                // Can now remove backup if desired
                // remove(backup);
            }
            else
            {
                // Restore backup if replacement failed
                rename(backup, original);
                printf("  ✗ Replacement failed, restored backup\n");
            }
        }
        printf("\n");
    }

    // Test 10: Checking if file exists before operations
    printf("Test 10: Checking file existence\n");
    {
        const char *filename = "check_exists.txt";

        // Create file
        FILE *fp = fopen(filename, "w");
        if (fp != NULL)
        {
            fprintf(fp, "Test\n");
            fclose(fp);
        }

        // Check if file exists
        fp = fopen(filename, "r");
        if (fp != NULL)
        {
            printf("  ✓ File exists\n");
            fclose(fp);

            // Now safe to remove
            if (remove(filename) == 0)
            {
                printf("  ✓ File removed\n");
            }
        }
        else
        {
            printf("  ✗ File doesn't exist\n");
        }
        printf("\n");
    }

    // Test 11: Platform differences
    printf("Test 11: Platform differences\n");
    {
        printf("  Unix/Linux/macOS:\n");
        printf("  • remove() works on open files (deleted after close)\n");
        printf("  • rename() can move across directories (same filesystem)\n");
        printf("  • rename() overwrites target file atomically\n");
        printf("\n");

        printf("  Windows:\n");
        printf("  • remove() fails on open files\n");
        printf("  • rename() may fail if target exists\n");
        printf("  • File locking is more restrictive\n");
        printf("\n");
    }

    printf("=== Function Summary ===\n\n");
    printf("remove(filename):\n");
    printf("  • Deletes the named file\n");
    printf("  • Returns 0 on success, non-zero on error\n");
    printf("  • Sets errno on error\n");
    printf("\n");

    printf("rename(oldname, newname):\n");
    printf("  • Renames/moves a file\n");
    printf("  • Returns 0 on success, non-zero on error\n");
    printf("  • May overwrite target (platform-dependent)\n");
    printf("  • Sets errno on error\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. Always check return values (0 = success)\n");
    printf("2. Use perror() or strerror(errno) for error messages\n");
    printf("3. Close files before removing/renaming when possible\n");
    printf("4. rename() behavior with existing target varies by OS\n");
    printf("5. remove() on open files is platform-dependent\n");
    printf("6. Can't remove directories with remove() (use rmdir)\n");
    printf("7. rename() may fail across filesystems\n");
    printf("8. File permissions affect both operations\n");
    printf("9. Use temp file + rename for atomic updates\n");
    printf("10. Always have a backup strategy for important files\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Check return values\n");
    printf("✓ Close files before remove/rename\n");
    printf("✓ Use temp files for safe replacements\n");
    printf("✓ Keep backups of important files\n");
    printf("✓ Use perror() for meaningful error messages\n");
    printf("✓ Test error paths in your code\n");
    printf("✓ Be aware of platform differences\n");

    return EXIT_SUCCESS;
}
