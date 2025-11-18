#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Variable-Length Arrays (VLAs) - C99 feature
// Arrays whose size is determined at runtime

// Function demonstrating basic VLA usage
void print_matrix(size_t rows, size_t cols, int matrix[rows][cols])
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function that returns size of VLA in its scope
void demonstrate_sizeof_vla(size_t n)
{
    int vla[n];
    printf("  VLA of size %zu: sizeof(vla) = %zu bytes\n", n, sizeof(vla));
    printf("  Each element: %zu bytes\n", sizeof(vla[0]));
    printf("  Total elements: %zu\n", sizeof(vla) / sizeof(vla[0]));
}

// Function using VLA for temporary computation
double compute_average(size_t count, const int *values)
{
    // Create a VLA to store squared values
    int squares[count];

    for (size_t i = 0; i < count; i++)
    {
        squares[i] = values[i] * values[i];
    }

    double sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += squares[i];
    }

    return sum / count;
}

// Multidimensional VLA example
void process_3d_data(size_t x, size_t y, size_t z)
{
    int data[x][y][z];

    printf("Created 3D VLA: %zu x %zu x %zu\n", x, y, z);
    printf("Total size: %zu bytes\n", sizeof(data));

    // Initialize with pattern
    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < y; j++)
        {
            for (size_t k = 0; k < z; k++)
            {
                data[i][j][k] = (int)(i * 100 + j * 10 + k);
            }
        }
    }

    // Print a slice
    printf("Slice [0][*][*]:\n");
    for (size_t j = 0; j < y; j++)
    {
        for (size_t k = 0; k < z; k++)
        {
            printf("%4d ", data[0][j][k]);
        }
        printf("\n");
    }
}

int main(void)
{
    printf("=== Variable-Length Arrays (VLAs) Examples ===\n\n");

    // Test 1: Basic VLA
    printf("Test 1: Basic VLA usage\n");
    {
        size_t n = 5;
        int arr[n]; // VLA - size determined at runtime

        printf("Created VLA with %zu elements\n", n);

        // Initialize
        for (size_t i = 0; i < n; i++)
        {
            arr[i] = (int)(i * 10);
        }

        // Print
        printf("Array: ");
        for (size_t i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // sizeof works with VLAs!
        printf("sizeof(arr) = %zu bytes\n", sizeof(arr));
        printf("Number of elements: %zu\n", sizeof(arr) / sizeof(arr[0]));
    }
    printf("\n");

    // Test 2: VLA with user input simulation
    printf("Test 2: VLA size from runtime value\n");
    {
        // Simulate getting size at runtime
        size_t size = 3 + (size_t)(rand() % 5); // Random size 3-7
        printf("Dynamically determined size: %zu\n", size);

        double values[size];

        for (size_t i = 0; i < size; i++)
        {
            values[i] = (double)i * 1.5;
        }

        printf("Values: ");
        for (size_t i = 0; i < size; i++)
        {
            printf("%.1f ", values[i]);
        }
        printf("\n");
    }
    printf("\n");

    // Test 3: 2D VLA (matrix)
    printf("Test 3: 2D VLA (matrix)\n");
    {
        size_t rows = 3, cols = 4;
        int matrix[rows][cols]; // 2D VLA

        // Initialize
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix[i][j] = (int)(i * cols + j);
            }
        }

        printf("Matrix (%zu x %zu):\n", rows, cols);
        print_matrix(rows, cols, matrix);

        printf("sizeof(matrix) = %zu bytes\n", sizeof(matrix));
    }
    printf("\n");

    // Test 4: VLA in function parameter
    printf("Test 4: VLA as function parameter\n");
    {
        int data[] = {1, 2, 3, 4, 5};
        size_t count = sizeof(data) / sizeof(data[0]);

        double avg = compute_average(count, data);
        printf("Average of squares: %.2f\n", avg);
    }
    printf("\n");

    // Test 5: sizeof with different VLA sizes
    printf("Test 5: sizeof with VLAs of different sizes\n");
    demonstrate_sizeof_vla(5);
    demonstrate_sizeof_vla(10);
    demonstrate_sizeof_vla(100);
    printf("\n");

    // Test 6: 3D VLA
    printf("Test 6: 3D VLA\n");
    process_3d_data(2, 3, 4);
    printf("\n");

    // Test 7: VLA vs malloc comparison
    printf("Test 7: VLA vs malloc/free\n");
    {
        size_t n = 1000;

        // VLA approach
        clock_t start = clock();
        {
            int vla[n];
            for (size_t i = 0; i < n; i++)
            {
                vla[i] = (int)i;
            }
            // Automatic cleanup when leaving scope
        }
        clock_t end = clock();
        double vla_time = (double)(end - start) / CLOCKS_PER_SEC;

        // malloc approach
        start = clock();
        {
            int *heap = malloc(n * sizeof(int));
            if (heap)
            {
                for (size_t i = 0; i < n; i++)
                {
                    heap[i] = (int)i;
                }
                free(heap);
            }
        }
        end = clock();
        double malloc_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Performance comparison for %zu elements:\n", n);
        printf("  VLA time:    %.6f seconds\n", vla_time);
        printf("  malloc time: %.6f seconds\n", malloc_time);
        printf("  VLA is typically faster (no heap allocation overhead)\n");
    }
    printf("\n");

    // Test 8: VLA scope and lifetime
    printf("Test 8: VLA scope and lifetime\n");
    {
        printf("Entering outer scope\n");
        int outer[5];
        outer[0] = 100;

        {
            printf("  Entering inner scope\n");
            int inner[3];
            inner[0] = 200;
            printf("  inner[0] = %d\n", inner[0]);
            printf("  Leaving inner scope (inner VLA destroyed)\n");
        }

        printf("outer[0] = %d (still valid)\n", outer[0]);
        printf("Leaving outer scope (outer VLA destroyed)\n");
    }
    printf("\n");

    // Test 9: VLA with typedef (C11 feature)
    printf("Test 9: VLA with typedef\n");
    {
        size_t n = 4;
        typedef int vector[n]; // VLA typedef

        vector v1, v2;

        for (size_t i = 0; i < n; i++)
        {
            v1[i] = (int)i;
            v2[i] = (int)(i * 2);
        }

        printf("v1: ");
        for (size_t i = 0; i < n; i++)
            printf("%d ", v1[i]);
        printf("\n");

        printf("v2: ");
        for (size_t i = 0; i < n; i++)
            printf("%d ", v2[i]);
        printf("\n");
    }
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. VLAs introduced in C99, made optional in C11\n");
    printf("2. Size determined at runtime, but fixed for lifetime of array\n");
    printf("3. Allocated on the STACK, not the heap\n");
    printf("4. Automatically deallocated when leaving scope\n");
    printf("5. sizeof() works correctly with VLAs\n");
    printf("6. Cannot be initialized with {...} syntax\n");
    printf("7. Cannot be static or extern\n");
    printf("8. Cannot have linkage outside their scope\n");
    printf("9. Faster than malloc (no heap allocation)\n");
    printf("10. Risk of stack overflow with large sizes\n");

    printf("\n=== Advantages ===\n");
    printf("✓ Automatic memory management (no free needed)\n");
    printf("✓ Faster than heap allocation\n");
    printf("✓ Natural syntax for multidimensional arrays\n");
    printf("✓ sizeof works correctly\n");
    printf("✓ Good for small, temporary arrays\n");

    printf("\n=== Disadvantages ===\n");
    printf("✗ Limited by stack size (typically 1-8 MB)\n");
    printf("✗ Cannot detect allocation failure (will crash)\n");
    printf("✗ Size cannot change after creation\n");
    printf("✗ Not all compilers support them (optional in C11)\n");
    printf("✗ Cannot return VLA from function (returns pointer to stack)\n");

    printf("\n=== When to Use VLAs ===\n");
    printf("✓ Small arrays (< 1KB)\n");
    printf("✓ Temporary computations\n");
    printf("✓ Size known at runtime but fixed during use\n");
    printf("✓ Performance-critical code\n");
    printf("✗ Large arrays (use malloc)\n");
    printf("✗ Long-lived data (use malloc)\n");
    printf("✗ Recursive functions (stack overflow risk)\n");

    return EXIT_SUCCESS;
}
