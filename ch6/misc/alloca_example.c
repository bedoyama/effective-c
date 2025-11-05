#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// alloca is not part of standard C but widely available
// On most systems: #include <alloca.h>
// On some systems it's in <malloc.h> or <stdlib.h>
#ifdef __GNUC__
// GCC provides alloca as a built-in
#define USE_ALLOCA 1
#else
#include <alloca.h>
#define USE_ALLOCA 1
#endif

// Helper function to demonstrate stack allocation scope
void process_data(const char *input)
{
    size_t len = strlen(input);

    // Allocate on the stack - automatically freed when function returns
    char *buffer = (char *)alloca(len + 1);

    strcpy(buffer, input);
    printf("  Processing: %s (length: %zu)\n", buffer, len);

    // No need to free - buffer is automatically deallocated when function returns
}

// Function to demonstrate alloca in loops (dangerous!)
void dangerous_loop_example(void)
{
    printf("\nTest: alloca in a loop (DANGEROUS - for demonstration only)\n");

    // WARNING: This can blow the stack!
    // Each iteration allocates MORE stack space that isn't freed until function returns
    for (int i = 0; i < 5; i++)
    {
        int *arr = (int *)alloca(100 * sizeof(int));
        arr[0] = i;
        printf("  Iteration %d: allocated %zu bytes on stack\n", i, 100 * sizeof(int));
    }
    // All allocations are still on the stack here!
    printf("  All %d allocations still on stack until function returns\n", 5);
}

int main(void)
{
#ifdef USE_ALLOCA
    printf("=== alloca (Stack Allocation) Examples ===\n\n");

    // Test 1: Basic stack allocation
    printf("Test 1: Basic stack allocation\n");
    {
        size_t size = 10;
        int *stack_array = (int *)alloca(size * sizeof(int));

        printf("Allocated %zu ints on the stack\n", size);
        for (size_t i = 0; i < size; i++)
        {
            stack_array[i] = (int)(i * i);
        }

        printf("Stack array: ");
        for (size_t i = 0; i < size; i++)
        {
            printf("%d ", stack_array[i]);
        }
        printf("\n");
        // No free() needed - automatic cleanup
    }
    printf("\n");

    // Test 2: String manipulation
    printf("Test 2: Temporary string buffer\n");
    {
        const char *name = "World";
        size_t buffer_size = strlen("Hello, ") + strlen(name) + 1;

        char *greeting = (char *)alloca(buffer_size);
        snprintf(greeting, buffer_size, "Hello, %s", name);

        printf("Greeting: %s\n", greeting);
        // Automatically freed when leaving this scope
    }
    printf("\n");

    // Test 3: Function calls with stack allocation
    printf("Test 3: Stack allocation in function calls\n");
    process_data("First message");
    process_data("Second message with more text");
    process_data("Third");
    printf("\n");

    // Test 4: Variable-length arrays comparison
    printf("Test 4: alloca vs VLA (Variable Length Array)\n");
    {
        size_t n = 5;

        // Using alloca
        int *alloca_array = (int *)alloca(n * sizeof(int));
        for (size_t i = 0; i < n; i++)
        {
            alloca_array[i] = (int)i;
        }

        // Using VLA (C99 feature)
        int vla_array[n];
        for (size_t i = 0; i < n; i++)
        {
            vla_array[i] = (int)i;
        }

        printf("alloca array: ");
        for (size_t i = 0; i < n; i++)
            printf("%d ", alloca_array[i]);
        printf("\n");

        printf("VLA array:    ");
        for (size_t i = 0; i < n; i++)
            printf("%d ", vla_array[i]);
        printf("\n");
    }
    printf("\n");

    // Test 5: Nested scope allocation
    printf("Test 5: Nested scope allocations\n");
    {
        char *outer = (char *)alloca(20);
        strcpy(outer, "Outer scope");
        printf("Outer: %s\n", outer);

        {
            char *inner = (char *)alloca(20);
            strcpy(inner, "Inner scope");
            printf("  Inner: %s\n", inner);
            // inner is still valid here
        }
        // inner is technically still on the stack but shouldn't be used
        printf("Outer still valid: %s\n", outer);
    }
    printf("\n");

    // Test 6: Dangerous usage
    dangerous_loop_example();
    printf("\n");

    // Test 7: Use case - temporary path building
    printf("Test 7: Practical use - path building\n");
    {
        const char *dir = "/usr/local";
        const char *subdir = "bin";
        const char *file = "program";

        size_t path_len = strlen(dir) + 1 + strlen(subdir) + 1 + strlen(file) + 1;
        char *path = (char *)alloca(path_len);

        snprintf(path, path_len, "%s/%s/%s", dir, subdir, file);
        printf("Built path: %s\n", path);
        // No cleanup needed
    }

    printf("\n=== Important Notes ===\n");
    printf("1. alloca allocates memory on the STACK, not the heap\n");
    printf("2. Memory is automatically freed when the function returns\n");
    printf("3. NO free() call needed (and calling free() is an ERROR)\n");
    printf("4. NOT part of standard C (but widely available)\n");
    printf("5. Cannot detect allocation failure - will crash if stack overflows\n");
    printf("6. DANGEROUS in loops - each iteration adds to the stack\n");
    printf("7. Size is limited by stack size (typically 1-8 MB)\n");
    printf("8. Faster than malloc (no heap allocation overhead)\n");
    printf("9. Consider VLAs (C99) as a standard alternative\n");
    printf("10. Use for small, temporary buffers in performance-critical code\n");
    printf("\n=== When to Use ===\n");
    printf("✓ Small temporary buffers (< 1KB)\n");
    printf("✓ Known small sizes at compile time\n");
    printf("✓ Performance-critical code\n");
    printf("✗ Large allocations\n");
    printf("✗ Unknown/variable sizes\n");
    printf("✗ Inside loops\n");
    printf("✗ Recursive functions\n");

#else
    printf("alloca is not available on this system\n");
    printf("Consider using VLAs (Variable Length Arrays) or malloc instead\n");
#endif

    return EXIT_SUCCESS;
}
