#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== malloc - Memory Allocation ===\n\n");

    // Basic malloc usage
    printf("Test 1: Allocating single integer\n");
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    *ptr = 42;
    printf("Allocated integer: %d\n", *ptr);
    printf("Address: %p\n", (void *)ptr);
    free(ptr);
    printf("Memory freed\n\n");

    // Allocating array
    printf("Test 2: Allocating array of integers\n");
    int n = 5;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Allocated array of %d integers\n", n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = i * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    printf("Array freed\n\n");

    // Allocating struct
    typedef struct
    {
        int id;
        double value;
        char name[20];
    } Record;

    printf("Test 3: Allocating struct\n");
    Record *rec = (Record *)malloc(sizeof(Record));
    if (rec == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    rec->id = 100;
    rec->value = 3.14159;
    snprintf(rec->name, sizeof(rec->name), "Test Record");

    printf("Record ID: %d\n", rec->id);
    printf("Record Value: %.5f\n", rec->value);
    printf("Record Name: %s\n", rec->name);

    free(rec);
    printf("Struct freed\n\n");

    // malloc with zero size (implementation-defined)
    printf("Test 4: malloc with zero size\n");
    void *zero_ptr = malloc(0);
    if (zero_ptr != NULL)
    {
        printf("malloc(0) returned non-NULL: %p\n", zero_ptr);
        free(zero_ptr);
    }
    else
    {
        printf("malloc(0) returned NULL\n");
    }
    printf("\n");

    // Demonstrating uninitialized memory
    printf("Test 5: Uninitialized memory (garbage values)\n");
    int *uninit = (int *)malloc(5 * sizeof(int));
    if (uninit == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Uninitialized values (may contain garbage):\n");
    for (int i = 0; i < 5; i++)
    {
        printf("uninit[%d] = %d\n", i, uninit[i]);
    }

    free(uninit);
    printf("\n");

    // Common mistake - forgetting to check return value
    printf("=== Important Notes ===\n");
    printf("1. ALWAYS check if malloc returns NULL\n");
    printf("2. malloc does NOT initialize memory (contains garbage)\n");
    printf("3. sizeof(type) ensures correct size calculation\n");
    printf("4. Cast result to appropriate pointer type (optional in C)\n");
    printf("5. ALWAYS free allocated memory to avoid leaks\n");

    return EXIT_SUCCESS;
}
