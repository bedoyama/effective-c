#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(void)
{
    printf("=== POSIX File I/O Functions ===\n\n");
    printf("Note: POSIX I/O is unbuffered, unlike stdio.h functions\n\n");

    // Test 1: open() - create and open file
    printf("Test 1: open() - create and open file\n");
    {
        int fd = open("posix_test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("  ✗ open failed");
        }
        else
        {
            printf("  ✓ File opened with file descriptor: %d\n", fd);
            close(fd);
        }
        printf("\n");
    }

    // Test 2: write() - write data to file
    printf("Test 2: write() - write data to file\n");
    {
        int fd = open("posix_test.txt", O_WRONLY | O_TRUNC);
        if (fd != -1)
        {
            const char *text = "Hello from POSIX I/O!\n";
            ssize_t bytes_written = write(fd, text, strlen(text));

            if (bytes_written == -1)
            {
                perror("  ✗ write failed");
            }
            else
            {
                printf("  ✓ Wrote %zd bytes\n", bytes_written);
            }

            close(fd);
        }
        printf("\n");
    }

    // Test 3: read() - read data from file
    printf("Test 3: read() - read data from file\n");
    {
        int fd = open("posix_test.txt", O_RDONLY);
        if (fd != -1)
        {
            char buffer[100];
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

            if (bytes_read == -1)
            {
                perror("  ✗ read failed");
            }
            else
            {
                buffer[bytes_read] = '\0';
                printf("  ✓ Read %zd bytes:\n", bytes_read);
                printf("  \"%s\"\n", buffer);
            }

            close(fd);
        }
        printf("\n");
    }

    // Test 4: lseek() - file positioning
    printf("Test 4: lseek() - file positioning\n");
    {
        int fd = open("posix_test.txt", O_WRONLY);
        if (fd != -1)
        {
            // Write at beginning
            write(fd, "START", 5);

            // Seek to position 10
            off_t pos = lseek(fd, 10, SEEK_SET);
            printf("  Seeked to position: %lld\n", (long long)pos);

            // Write at new position
            write(fd, "MIDDLE", 6);

            // Seek to end
            pos = lseek(fd, 0, SEEK_END);
            printf("  File size: %lld bytes\n", (long long)pos);

            // Write at end
            write(fd, " END", 4);

            close(fd);
        }

        // Read back to see the result
        fd = open("posix_test.txt", O_RDONLY);
        if (fd != -1)
        {
            char buffer[100];
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
            buffer[bytes_read] = '\0';
            printf("  Content: ");
            for (ssize_t i = 0; i < bytes_read; i++)
            {
                char c = buffer[i];
                printf("%c", (c >= 32 && c <= 126) ? c : '.');
            }
            printf("\n");
            close(fd);
        }
        printf("\n");
    }

    // Test 5: O_APPEND flag
    printf("Test 5: O_APPEND - append to file\n");
    {
        int fd = open("posix_test.txt", O_WRONLY | O_APPEND);
        if (fd != -1)
        {
            const char *text = "\nAppended line\n";
            write(fd, text, strlen(text));
            printf("  ✓ Appended data to file\n");
            close(fd);
        }

        // Read entire file
        fd = open("posix_test.txt", O_RDONLY);
        if (fd != -1)
        {
            char buffer[200];
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
            buffer[bytes_read] = '\0';
            printf("  File content:\n%s", buffer);
            close(fd);
        }
        printf("\n");
    }

    // Test 6: open() flags comparison
    printf("Test 6: open() flags summary\n");
    {
        printf("  Access modes (mutually exclusive):\n");
        printf("    O_RDONLY  - Read only\n");
        printf("    O_WRONLY  - Write only\n");
        printf("    O_RDWR    - Read and write\n");
        printf("\n");

        printf("  Creation flags:\n");
        printf("    O_CREAT   - Create if doesn't exist\n");
        printf("    O_EXCL    - With O_CREAT, fail if exists\n");
        printf("    O_TRUNC   - Truncate to zero length\n");
        printf("\n");

        printf("  Status flags:\n");
        printf("    O_APPEND  - Append mode\n");
        printf("    O_NONBLOCK - Non-blocking I/O\n");
        printf("    O_SYNC    - Synchronous writes\n");
        printf("\n");
    }

    // Test 7: File permissions with open()
    printf("Test 7: File permissions (mode)\n");
    {
        // Create file with specific permissions: rw-r--r--
        int fd = open("posix_perms.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd != -1)
        {
            write(fd, "Test\n", 5);
            close(fd);
            printf("  ✓ Created file with mode 0644 (rw-r--r--)\n");
        }

        // Create file with different permissions: rwx------
        fd = open("posix_private.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700);
        if (fd != -1)
        {
            write(fd, "Private\n", 8);
            close(fd);
            printf("  ✓ Created file with mode 0700 (rwx------)\n");
        }

        printf("\n");
    }

    // Test 8: pread() and pwrite() - positioned I/O
    printf("Test 8: pread() and pwrite() - positioned I/O\n");
    {
        int fd = open("posix_test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd != -1)
        {
            // Write some data
            write(fd, "0123456789ABCDEF", 16);

            // Read from position 5 without changing file offset
            char buffer[5];
            ssize_t bytes = pread(fd, buffer, 4, 5);
            buffer[bytes] = '\0';
            printf("  pread at offset 5: \"%s\"\n", buffer);

            // Write at position 10 without changing file offset
            pwrite(fd, "XXX", 3, 10);
            printf("  pwrite at offset 10: \"XXX\"\n");

            // Current position is still at 16 (end of initial write)
            off_t pos = lseek(fd, 0, SEEK_CUR);
            printf("  Current file offset: %lld\n", (long long)pos);

            // Read entire file to see result
            lseek(fd, 0, SEEK_SET);
            read(fd, buffer, sizeof(buffer));
            char full[20];
            lseek(fd, 0, SEEK_SET);
            bytes = read(fd, full, sizeof(full) - 1);
            full[bytes] = '\0';
            printf("  Final content: \"%s\"\n", full);

            close(fd);
        }
        printf("\n");
    }

    // Test 9: dup() and dup2() - duplicate file descriptors
    printf("Test 9: dup() and dup2() - duplicate file descriptors\n");
    {
        int fd = open("posix_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd != -1)
        {
            // Duplicate the file descriptor
            int fd2 = dup(fd);
            printf("  Original fd: %d, Duplicated fd: %d\n", fd, fd2);

            // Both refer to same file
            write(fd, "Hello ", 6);
            write(fd2, "World\n", 6);

            close(fd);
            close(fd2);

            // Read back
            fd = open("posix_test.txt", O_RDONLY);
            char buffer[20];
            ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
            buffer[bytes] = '\0';
            printf("  Content: \"%s\"\n", buffer);
            close(fd);
        }
        printf("\n");
    }

    // Test 10: fcntl() - file control operations
    printf("Test 10: fcntl() - file control\n");
    {
        int fd = open("posix_test.txt", O_RDONLY);
        if (fd != -1)
        {
            // Get file status flags
            int flags = fcntl(fd, F_GETFL);
            printf("  File status flags: 0x%x\n", flags);

            // Check access mode
            int access_mode = flags & O_ACCMODE;
            if (access_mode == O_RDONLY)
                printf("  Access mode: O_RDONLY\n");
            else if (access_mode == O_WRONLY)
                printf("  Access mode: O_WRONLY\n");
            else if (access_mode == O_RDWR)
                printf("  Access mode: O_RDWR\n");

            close(fd);
        }
        printf("\n");
    }

    // Test 11: fsync() - synchronize file data
    printf("Test 11: fsync() - synchronize file to disk\n");
    {
        int fd = open("posix_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd != -1)
        {
            write(fd, "Important data\n", 15);

            // Force write to disk
            if (fsync(fd) == 0)
            {
                printf("  ✓ Data synchronized to disk\n");
            }
            else
            {
                perror("  ✗ fsync failed");
            }

            close(fd);
        }
        printf("\n");
    }

    // Test 12: fstat() - get file information
    printf("Test 12: fstat() - get file statistics\n");
    {
        int fd = open("posix_test.txt", O_RDONLY);
        if (fd != -1)
        {
            struct stat st;
            if (fstat(fd, &st) == 0)
            {
                printf("  File size: %lld bytes\n", (long long)st.st_size);
                printf("  Inode number: %llu\n", (unsigned long long)st.st_ino);
                printf("  Number of links: %d\n", (int)st.st_nlink);
                printf("  Permissions: 0%o\n", st.st_mode & 0777);
                printf("  UID: %d, GID: %d\n", st.st_uid, st.st_gid);
            }

            close(fd);
        }
        printf("\n");
    }

    // Test 13: unlink() - remove file
    printf("Test 13: unlink() - remove file\n");
    {
        // Create a temporary file
        int fd = open("temp_unlink.txt", O_CREAT | O_WRONLY, 0644);
        if (fd != -1)
        {
            write(fd, "Temporary\n", 10);
            close(fd);
            printf("  ✓ Created temp_unlink.txt\n");
        }

        // Remove it
        if (unlink("temp_unlink.txt") == 0)
        {
            printf("  ✓ Removed temp_unlink.txt\n");
        }
        else
        {
            perror("  ✗ unlink failed");
        }
        printf("\n");
    }

    // Test 14: Comparing stdio vs POSIX I/O
    printf("Test 14: Standard I/O vs POSIX I/O comparison\n");
    {
        printf("  Standard I/O (stdio.h):\n");
        printf("    • Buffered (more efficient for small I/O)\n");
        printf("    • Higher level, portable (FILE *)\n");
        printf("    • Functions: fopen, fread, fwrite, fclose\n");
        printf("    • Automatic newline conversion (text mode)\n");
        printf("    • Easy formatted I/O (fprintf, fscanf)\n");
        printf("\n");

        printf("  POSIX I/O (unistd.h, fcntl.h):\n");
        printf("    • Unbuffered (direct system calls)\n");
        printf("    • Lower level, Unix/POSIX specific (int fd)\n");
        printf("    • Functions: open, read, write, close\n");
        printf("    • No automatic conversions\n");
        printf("    • More control (locks, non-blocking, etc.)\n");
        printf("    • Can use with pipes, sockets, devices\n");
        printf("\n");
    }

    // Clean up test files
    unlink("posix_test.txt");
    unlink("posix_perms.txt");
    unlink("posix_private.txt");

    printf("=== Function Summary ===\n\n");
    printf("File Operations:\n");
    printf("  open(path, flags, mode)  - Open/create file, returns fd\n");
    printf("  close(fd)                - Close file descriptor\n");
    printf("  read(fd, buf, count)     - Read bytes, returns count read\n");
    printf("  write(fd, buf, count)    - Write bytes, returns count written\n");
    printf("  lseek(fd, offset, whence) - Reposition file offset\n");
    printf("  pread(fd, buf, count, offset)  - Read at offset\n");
    printf("  pwrite(fd, buf, count, offset) - Write at offset\n");
    printf("  unlink(path)             - Remove file\n");
    printf("\n");

    printf("File Descriptor Operations:\n");
    printf("  dup(fd)                  - Duplicate file descriptor\n");
    printf("  dup2(fd, newfd)          - Duplicate to specific fd\n");
    printf("  fcntl(fd, cmd, ...)      - File control operations\n");
    printf("\n");

    printf("File Information:\n");
    printf("  fstat(fd, &stat)         - Get file status\n");
    printf("  fsync(fd)                - Sync file to disk\n");
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. File descriptors are small non-negative integers\n");
    printf("2. open() returns -1 on error, check errno\n");
    printf("3. read() may return less than requested (not an error)\n");
    printf("4. write() may write less than requested (check return)\n");
    printf("5. Always close file descriptors\n");
    printf("6. POSIX I/O is unbuffered (each call = system call)\n");
    printf("7. File descriptor 0 = stdin, 1 = stdout, 2 = stderr\n");
    printf("8. Use O_CREAT with mode parameter\n");
    printf("9. pread/pwrite don't change file offset (thread-safe)\n");
    printf("10. lseek returns new offset or -1 on error\n");

    printf("\n=== Best Practices ===\n");
    printf("✓ Check return values for all operations\n");
    printf("✓ Use POSIX I/O for performance-critical unbuffered I/O\n");
    printf("✓ Use stdio for most application-level file I/O\n");
    printf("✓ Always close file descriptors (or use dup2 to close)\n");
    printf("✓ Use O_CLOEXEC flag to prevent fd leaks across exec\n");
    printf("✓ Use pread/pwrite for thread-safe positioned I/O\n");
    printf("✓ Use fsync() for critical data that must reach disk\n");
    printf("✗ Don't mix POSIX I/O and stdio on same file\n");
    printf("✗ Don't assume read/write complete requested operation\n");

    return EXIT_SUCCESS;
}
