#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== free - Deallocating Memory ===\n\n");

    // Basic free usage
    printf("Test 1: Basic malloc and free\n");
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    *ptr = 42;
    printf("Allocated and set value: %d\n", *ptr);
    printf("Address: %p\n", (void *)ptr);

    free(ptr);
    printf("Memory freed\n");
    // ptr is now a dangling pointer - DO NOT USE!
    printf("\n");

    // Free NULL (safe - does nothing)
    printf("Test 2: Freeing NULL pointer\n");
    int *null_ptr = NULL;
    free(null_ptr);
    printf("free(NULL) is safe - does nothing\n\n");

    // Setting pointer to NULL after free (good practice)
    printf("Test 3: Setting pointer to NULL after free\n");
    int *safe_ptr = (int *)malloc(sizeof(int));
    if (safe_ptr == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    *safe_ptr = 100;
    printf("Value: %d\n", *safe_ptr);

    free(safe_ptr);
    safe_ptr = NULL; // Good practice!
    printf("Freed and set to NULL\n");

    // Now we can safely check
    if (safe_ptr == NULL)
    {
        printf("Pointer is NULL, safe to check in conditionals\n");
    }
    printf("\n");

    // Memory leak example (commented to avoid leak)
    printf("Test 4: Memory leak demonstration\n");
    printf("Uncommenting this code would cause a leak:\n");
    printf("// int *leak = malloc(100);\n");
    printf("// leak = NULL;  // Lost reference, can't free!\n");
    printf("Always free before losing reference!\n\n");

    // Freeing array
    printf("Test 5: Freeing dynamically allocated array\n");
    size_t n = 10;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = (int)(i * i);
    }

    printf("Array allocated and initialized\n");
    printf("First 5 values: %d, %d, %d, %d, %d\n",
           arr[0], arr[1], arr[2], arr[3], arr[4]);

    free(arr);
    printf("Array freed (entire block freed at once)\n\n");

    // Multiple allocations and frees
    printf("Test 6: Multiple allocations\n");
    int *p1 = (int *)malloc(sizeof(int));
    int *p2 = (int *)malloc(sizeof(int));
    int *p3 = (int *)malloc(sizeof(int));

    if (p1 && p2 && p3)
    {
        *p1 = 10;
        *p2 = 20;
        *p3 = 30;
        printf("Allocated 3 integers: %d, %d, %d\n", *p1, *p2, *p3);

        // Free in any order (doesn't have to be reverse)
        free(p2);
        printf("Freed p2\n");
        free(p1);
        printf("Freed p1\n");
        free(p3);
        printf("Freed p3\n");
    }
    printf("\n");

    // Common errors (DO NOT DO THESE!)
    printf("=== Common Errors (DO NOT DO!) ===\n");

    printf("\n1. Double Free:\n");
    printf("   int *p = malloc(sizeof(int));\n");
    printf("   free(p);\n");
    printf("   free(p);  // UNDEFINED BEHAVIOR!\n");

    printf("\n2. Use After Free:\n");
    printf("   int *p = malloc(sizeof(int));\n");
    printf("   free(p);\n");
    printf("   *p = 42;  // UNDEFINED BEHAVIOR!\n");

    printf("\n3. Memory Leak:\n");
    printf("   int *p = malloc(sizeof(int));\n");
    printf("   p = NULL;  // Lost reference, can't free!\n");

    printf("\n4. Freeing Stack Memory:\n");
    printf("   int x = 42;\n");
    printf("   free(&x);  // WRONG! Only free malloc'd memory\n");

    printf("\n5. Freeing Part of Block:\n");
    printf("   int *arr = malloc(10 * sizeof(int));\n");
    printf("   free(&arr[5]);  // WRONG! Must free original pointer\n");

    printf("\n");

    // Proper cleanup pattern
    printf("=== Proper Cleanup Pattern ===\n");
    typedef struct
    {
        int *data;
        size_t size;
    } DynamicArray;

    DynamicArray da;
    da.size = 5;
    da.data = (int *)malloc(da.size * sizeof(int));

    if (da.data == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < da.size; i++)
    {
        da.data[i] = (int)i;
    }

    printf("Created dynamic array\n");
    printf("Values: ");
    for (size_t i = 0; i < da.size; i++)
    {
        printf("%d ", da.data[i]);
    }
    printf("\n");

    // Cleanup
    free(da.data);
    da.data = NULL; // Good practice
    da.size = 0;
    printf("Properly cleaned up\n\n");

    // Important notes
    printf("=== Important Notes ===\n");
    printf("1. Only free memory allocated by malloc/calloc/realloc\n");
    printf("2. free(NULL) is safe and does nothing\n");
    printf("3. Set pointer to NULL after free (good practice)\n");
    printf("4. Never use pointer after freeing it\n");
    printf("5. Never free same pointer twice\n");
    printf("6. Always free before program exits\n");
    printf("7. Free in error handling paths too!\n");

    return EXIT_SUCCESS;
}
