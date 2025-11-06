#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dmalloc - Debug malloc library
// This example demonstrates common memory errors that Dmalloc can detect
//
// To use Dmalloc:
// 1. Install: brew install dmalloc (macOS) or apt-get install libdmalloc-dev (Linux)
// 2. Compile with: gcc -DDMALLOC -ldmalloc program.c
// 3. Set environment: export DMALLOC_OPTIONS=debug=0x4f47d03,log=dmalloc.log
// 4. Run program and check dmalloc.log for errors

#ifdef DMALLOC
#include <dmalloc.h>
#endif

// Example 1: Memory leak
void example_memory_leak(void)
{
    printf("\n=== Example 1: Memory Leak ===\n");

    char *ptr = malloc(100);
    if (ptr)
    {
        strcpy(ptr, "This memory will leak!");
        printf("Allocated: %s\n", ptr);
        // BUG: Forgot to free(ptr)
    }

    printf("Function ends - memory leaked!\n");
    printf("Dmalloc will report: 100 bytes not freed\n");
}

// Example 2: Double free
void example_double_free(void)
{
    printf("\n=== Example 2: Double Free ===\n");

    char *ptr = malloc(50);
    if (ptr)
    {
        strcpy(ptr, "Test data");
        printf("Allocated: %s\n", ptr);

        free(ptr);
        printf("First free: OK\n");

        // BUG: Freeing again
        // Uncomment to trigger error (will crash or corrupt heap)
        // free(ptr);
        // printf("Second free: ERROR!\n");

        printf("Dmalloc would detect: double free error\n");
    }
}

// Example 3: Using freed memory (dangling pointer)
void example_use_after_free(void)
{
    printf("\n=== Example 3: Use After Free ===\n");

    int *ptr = malloc(sizeof(int) * 5);
    if (ptr)
    {
        ptr[0] = 42;
        printf("Before free: ptr[0] = %d\n", ptr[0]);

        free(ptr);
        printf("Memory freed\n");

        // BUG: Using freed memory
        // Uncomment to trigger error
        // printf("After free: ptr[0] = %d\n", ptr[0]);

        printf("Dmalloc would detect: access to freed memory\n");
    }
}

// Example 4: Buffer overflow
void example_buffer_overflow(void)
{
    printf("\n=== Example 4: Buffer Overflow ===\n");

    char *buffer = malloc(10);
    if (buffer)
    {
        printf("Allocated 10 bytes\n");

        // BUG: Writing beyond allocated space
        // Uncomment to trigger error
        // strcpy(buffer, "This string is too long for the buffer!");

        strcpy(buffer, "Safe");
        printf("Safe write: %s\n", buffer);

        printf("Dmalloc would detect: heap corruption from overflow\n");
        free(buffer);
    }
}

// Example 5: Buffer underflow
void example_buffer_underflow(void)
{
    printf("\n=== Example 5: Buffer Underflow ===\n");

    char *buffer = malloc(20);
    if (buffer)
    {
        strcpy(buffer, "Hello");
        printf("Allocated buffer: %s\n", buffer);

        // BUG: Writing before allocated region
        // Uncomment to trigger error
        // buffer[-1] = 'X';

        printf("Dmalloc would detect: write before allocated region\n");
        free(buffer);
    }
}

// Example 6: Freeing non-heap memory
void example_free_non_heap(void)
{
    printf("\n=== Example 6: Freeing Non-Heap Memory ===\n");

    int stack_var = 42;
    int *ptr = &stack_var;

    printf("Stack variable: %d\n", *ptr);

    // BUG: Trying to free stack memory
    // Uncomment to trigger error
    // free(ptr);

    printf("Dmalloc would detect: attempt to free non-heap memory\n");
}

// Example 7: Memory allocation without NULL check
void example_no_null_check(void)
{
    printf("\n=== Example 7: No NULL Check ===\n");

    size_t huge_size = (size_t)-1; // Very large size
    char *ptr = malloc(huge_size);

    // BUG: Not checking if malloc succeeded
    if (ptr == NULL)
    {
        printf("Allocation failed (expected for huge size)\n");
    }
    else
    {
        // This would be a bug - using ptr without checking
        strcpy(ptr, "data");
        free(ptr);
    }

    printf("Always check malloc return value!\n");
}

// Example 8: Correct usage with proper cleanup
void example_correct_usage(void)
{
    printf("\n=== Example 8: Correct Usage ===\n");

    size_t size = 100;
    char *buffer = malloc(size);

    if (buffer == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return;
    }

    // Use the memory safely
    snprintf(buffer, size, "Safe usage of %zu bytes", size);
    printf("Buffer: %s\n", buffer);

    // Clean up
    free(buffer);
    buffer = NULL; // Good practice: prevent dangling pointer

    printf("Dmalloc will report: No errors!\n");
}

// Helper function to demonstrate Dmalloc integration
void print_dmalloc_info(void)
{
    printf("\n=== Dmalloc Integration ===\n\n");

    printf("To use Dmalloc for debugging:\n\n");

    printf("1. Install Dmalloc:\n");
    printf("   macOS:  brew install dmalloc\n");
    printf("   Linux:  sudo apt-get install libdmalloc-dev\n\n");

    printf("2. Compile with Dmalloc:\n");
    printf("   gcc -DDMALLOC -o program program.c -ldmalloc\n\n");

    printf("3. Set environment variables:\n");
    printf("   export DMALLOC_OPTIONS=debug=0x4f47d03,log=dmalloc.log\n");
    printf("   (or use dmalloc utility: eval `dmalloc -b -l logfile low`)\n\n");

    printf("4. Run your program:\n");
    printf("   ./program\n\n");

    printf("5. Check the log file:\n");
    printf("   cat dmalloc.log\n\n");

    printf("Dmalloc can detect:\n");
    printf("  ✓ Memory leaks\n");
    printf("  ✓ Double frees\n");
    printf("  ✓ Use after free\n");
    printf("  ✓ Buffer overflows/underflows\n");
    printf("  ✓ Freeing non-heap memory\n");
    printf("  ✓ Uninitialized memory reads\n");
    printf("  ✓ Invalid pointers\n\n");

    printf("Alternative tools:\n");
    printf("  • Valgrind (valgrind --leak-check=full ./program)\n");
    printf("  • AddressSanitizer (-fsanitize=address)\n");
    printf("  • Electric Fence (libefence)\n");
    printf("  • Memcheck\n");
}

int main(void)
{
    printf("=== Dmalloc - Debug Malloc Library Examples ===\n");

    print_dmalloc_info();

    printf("\n=== Running Examples (Safe Mode) ===\n");
    printf("Note: Dangerous code is commented out to prevent crashes\n");
    printf("Compile with -DDMALLOC and uncomment bugs to test detection\n");

    example_memory_leak();
    example_double_free();
    example_use_after_free();
    example_buffer_overflow();
    example_buffer_underflow();
    example_free_non_heap();
    example_no_null_check();
    example_correct_usage();

    printf("\n=== Summary ===\n");
    printf("This program demonstrates common memory errors.\n");
    printf("When compiled with Dmalloc, it will detect and report:\n");
    printf("  - 1 memory leak (Example 1: 100 bytes)\n");
    printf("  - Other bugs are commented out to prevent crashes\n\n");

    printf("To see Dmalloc in action:\n");
    printf("  1. Uncomment the buggy code\n");
    printf("  2. Compile: gcc -DDMALLOC -o dmalloc_example dmalloc_example.c -ldmalloc\n");
    printf("  3. Run with: eval `dmalloc -b low` && ./dmalloc_example\n");
    printf("  4. Check: dmalloc -l dmalloc.log\n\n");

#ifdef DMALLOC
    printf("✓ Compiled with DMALLOC support\n");
    printf("Check dmalloc.log for detailed error reports\n");
#else
    printf("✗ Not compiled with DMALLOC support\n");
    printf("Recompile with -DDMALLOC -ldmalloc to enable\n");
#endif

    return EXIT_SUCCESS;
}
