#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>

int main()
{
    printf("=== aligned_alloc - Aligned Memory Allocation ===\n\n");

    // Check alignment requirements
    printf("Test 1: Basic type alignments\n");
    printf("alignof(char):   %zu\n", alignof(char));
    printf("alignof(int):    %zu\n", alignof(int));
    printf("alignof(double): %zu\n", alignof(double));
    printf("\n");

    // Allocate with specific alignment
    printf("Test 2: Allocate with 16-byte alignment\n");
    size_t alignment = 16;
    size_t size = 64;

    // Size must be a multiple of alignment
    void *ptr = aligned_alloc(alignment, size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Aligned allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Allocated %zu bytes with %zu-byte alignment\n", size, alignment);
    printf("Address: %p\n", ptr);
    printf("Address %% %zu = %zu (should be 0)\n",
           alignment, (size_t)ptr % alignment);

    // Use the memory
    int *arr = (int *)ptr;
    for (size_t i = 0; i < size / sizeof(int); i++)
    {
        arr[i] = (int)i;
    }

    printf("First few values: %d, %d, %d, %d\n", arr[0], arr[1], arr[2], arr[3]);

    free(ptr);
    printf("\n");

    // Different alignments
    printf("Test 3: Different alignment values\n");
    size_t alignments[] = {8, 16, 32, 64, 128};

    for (size_t i = 0; i < 5; i++)
    {
        size_t align = alignments[i];
        size_t alloc_size = 128; // Must be multiple of alignment

        void *p = aligned_alloc(align, alloc_size);
        if (p == NULL)
        {
            printf("  %zu-byte alignment: FAILED\n", align);
            continue;
        }

        printf("  %3zu-byte alignment: %p (offset: %zu)\n",
               align, p, (size_t)p % align);
        free(p);
    }
    printf("\n");

    // SIMD example (simplified)
    printf("Test 4: SIMD-friendly allocation\n");
    printf("(Useful for vectorized operations)\n");

    size = 256;
    alignment = 32; // AVX alignment
    float *simd_array = (float *)aligned_alloc(alignment, size * sizeof(float));
    if (simd_array == NULL)
    {
        fprintf(stderr, "SIMD allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Allocated %zu floats with %zu-byte alignment\n", size, alignment);
    printf("Address: %p\n", (void *)simd_array);
    printf("Properly aligned for SIMD operations\n");

    // Initialize some values
    for (size_t i = 0; i < 10; i++)
    {
        simd_array[i] = (float)i * 1.5f;
    }
    printf("Sample values: %.1f, %.1f, %.1f\n",
           simd_array[0], simd_array[1], simd_array[2]);

    free(simd_array);
    printf("\n");

    // Cache line alignment
    printf("Test 5: Cache line alignment\n");
    size_t cache_line_size = 64;

    typedef struct
    {
        int value;
        char padding[60]; // Pad to cache line size
    } CacheAligned;

    size_t num_items = 4;
    CacheAligned *cache_data = (CacheAligned *)aligned_alloc(
        cache_line_size,
        num_items * sizeof(CacheAligned));

    if (cache_data == NULL)
    {
        fprintf(stderr, "Cache-aligned allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Allocated %zu cache-aligned items\n", num_items);
    for (size_t i = 0; i < num_items; i++)
    {
        cache_data[i].value = (int)(i * 100);
        printf("Item %zu at %p (value: %d)\n",
               i, (void *)&cache_data[i], cache_data[i].value);
    }

    free(cache_data);
    printf("\n");

    // Incorrect usage - size not multiple of alignment
    printf("Test 6: Error case - size not multiple of alignment\n");
    alignment = 16;
    size = 33; // Not a multiple of 16
    printf("Attempting aligned_alloc(%zu, %zu)...\n", alignment, size);

    void *bad_ptr = aligned_alloc(alignment, size);
    if (bad_ptr == NULL)
    {
        printf("Failed: size must be multiple of alignment\n");
    }
    else
    {
        printf("Succeeded (implementation-dependent)\n");
        free(bad_ptr);
    }
    printf("\n");

    // Correct usage - round up size
    printf("Test 7: Correct - round up size to alignment\n");
    size_t requested_size = 33;
    size_t aligned_size = ((requested_size + alignment - 1) / alignment) * alignment;

    printf("Requested: %zu bytes\n", requested_size);
    printf("Aligned:   %zu bytes (rounded up)\n", aligned_size);

    void *good_ptr = aligned_alloc(alignment, aligned_size);
    if (good_ptr == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Success: allocated %zu bytes with %zu-byte alignment\n",
           aligned_size, alignment);
    free(good_ptr);
    printf("\n");

    // Important notes
    printf("=== Important Notes ===\n");
    printf("1. Size MUST be a multiple of alignment\n");
    printf("2. Alignment must be a power of 2\n");
    printf("3. Useful for SIMD, cache optimization, hardware requirements\n");
    printf("4. Free with regular free(), not a special function\n");
    printf("5. More expensive than regular malloc\n");
    printf("6. Not all platforms support aligned_alloc (C11)\n");

    return EXIT_SUCCESS;
}
