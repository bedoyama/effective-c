#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("=== realloc - Resizing Allocated Memory ===\n\n");

    // Basic realloc usage - growing array
    printf("Test 1: Growing an array\n");
    size_t size = 3;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Initial allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize array
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (int)(i * 10);
    }

    printf("Initial array (size %zu):\n", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    // Grow the array
    size = 6;
    int *temp = (int *)realloc(arr, size * sizeof(int));
    if (temp == NULL)
    {
        fprintf(stderr, "Reallocation failed\n");
        free(arr);
        return EXIT_FAILURE;
    }
    arr = temp;

    // Initialize new elements
    for (size_t i = 3; i < size; i++)
    {
        arr[i] = (int)(i * 10);
    }

    printf("\nResized array (size %zu):\n", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    free(arr);
    printf("\n");

    // Shrinking array
    printf("Test 2: Shrinking an array\n");
    size = 10;
    int *arr2 = (int *)malloc(size * sizeof(int));
    if (arr2 == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++)
    {
        arr2[i] = (int)(i + 1);
    }

    printf("Original array (size %zu): ", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // Shrink to 5 elements
    size = 5;
    temp = (int *)realloc(arr2, size * sizeof(int));
    if (temp == NULL)
    {
        fprintf(stderr, "Reallocation failed\n");
        free(arr2);
        return EXIT_FAILURE;
    }
    arr2 = temp;

    printf("Shrunk array (size %zu): ", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n\n");

    free(arr2);

    // realloc with NULL (equivalent to malloc)
    printf("Test 3: realloc with NULL pointer\n");
    int *arr3 = (int *)realloc(NULL, 3 * sizeof(int));
    if (arr3 == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("realloc(NULL, size) works like malloc\n");
    arr3[0] = 100;
    arr3[1] = 200;
    arr3[2] = 300;
    printf("Values: %d, %d, %d\n\n", arr3[0], arr3[1], arr3[2]);

    free(arr3);

    // realloc with zero size (equivalent to free)
    printf("Test 4: realloc with zero size\n");
    int *arr4 = (int *)malloc(5 * sizeof(int));
    if (arr4 != NULL)
    {
        printf("Allocated array\n");
        arr4 = (int *)realloc(arr4, 0);
        printf("realloc(ptr, 0) frees memory (implementation-defined)\n");
        // arr4 may be NULL now, don't use it
    }
    printf("\n");

    // Dynamic string manipulation
    printf("Test 5: Dynamic string building\n");
    char *str = (char *)malloc(10);
    if (str == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    strcpy(str, "Hello");
    printf("Initial string: '%s' (capacity: 10)\n", str);

    // Need more space
    char *new_str = (char *)realloc(str, 20);
    if (new_str == NULL)
    {
        fprintf(stderr, "Reallocation failed\n");
        free(str);
        return EXIT_FAILURE;
    }
    str = new_str;

    strcat(str, ", World!");
    printf("Extended string: '%s' (capacity: 20)\n\n", str);

    free(str);

    // Important: realloc may move memory
    printf("Test 6: realloc may change address\n");
    int *ptr1 = (int *)malloc(10 * sizeof(int));
    if (ptr1 == NULL)
    {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original address: %p\n", (void *)ptr1);

    int *ptr2 = (int *)realloc(ptr1, 1000 * sizeof(int));
    if (ptr2 == NULL)
    {
        fprintf(stderr, "Reallocation failed\n");
        free(ptr1);
        return EXIT_FAILURE;
    }

    printf("After realloc:    %p\n", (void *)ptr2);
    if (ptr1 == ptr2)
    {
        printf("Address stayed the same (resized in place)\n");
    }
    else
    {
        printf("Address changed (memory was moved)\n");
    }

    free(ptr2);
    printf("\n");

    // Important notes
    printf("=== Important Notes ===\n");
    printf("1. ALWAYS assign result to temp variable first\n");
    printf("2. Original pointer may be invalid after realloc\n");
    printf("3. realloc may move memory to new location\n");
    printf("4. Old data is preserved (up to smaller of old/new size)\n");
    printf("5. New memory beyond old size is uninitialized\n");
    printf("6. realloc(NULL, size) == malloc(size)\n");
    printf("7. realloc(ptr, 0) may act like free(ptr)\n");

    return EXIT_SUCCESS;
}
