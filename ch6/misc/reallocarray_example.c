#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

// OpenBSD's reallocarray - safer realloc that checks for overflow
// Portable implementation for systems that don't have it
#ifndef HAVE_REALLOCARRAY
void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    // Check for multiplication overflow
    if (size != 0 && nmemb > SIZE_MAX / size)
    {
        errno = ENOMEM;
        return NULL;
    }
    return realloc(ptr, nmemb * size);
}
#endif

int main(void)
{
    printf("=== OpenBSD reallocarray Examples ===\n\n");

    // Test 1: Basic usage - growing an array safely
    printf("Test 1: Basic array growth\n");
    int *arr = NULL;
    size_t count = 5;

    arr = reallocarray(NULL, count, sizeof(int));
    if (!arr)
    {
        fprintf(stderr, "Failed to allocate array\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++)
    {
        arr[i] = (int)i * 10;
    }

    printf("Initial array (%zu elements): ", count);
    for (size_t i = 0; i < count; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Grow the array
    count = 10;
    int *new_arr = reallocarray(arr, count, sizeof(int));
    if (!new_arr)
    {
        fprintf(stderr, "Failed to reallocate array\n");
        free(arr);
        return EXIT_FAILURE;
    }
    arr = new_arr;

    // Initialize new elements
    for (size_t i = 5; i < count; i++)
    {
        arr[i] = (int)i * 10;
    }

    printf("Grown array (%zu elements): ", count);
    for (size_t i = 0; i < count; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    free(arr);

    // Test 2: Overflow protection - reallocarray vs realloc
    printf("Test 2: Overflow protection\n");
    size_t huge_nmemb = SIZE_MAX / 2;
    size_t huge_size = 4;

    printf("Attempting to allocate %zu elements of %zu bytes each\n", huge_nmemb, huge_size);
    printf("Would overflow: %zu * %zu > SIZE_MAX\n", huge_nmemb, huge_size);

    // reallocarray will catch the overflow and return NULL
    void *ptr = reallocarray(NULL, huge_nmemb, huge_size);
    if (ptr == NULL)
    {
        printf("✓ reallocarray correctly detected overflow and returned NULL\n");
    }
    else
    {
        printf("✗ Unexpected: allocation succeeded (should have failed)\n");
        free(ptr);
    }
    printf("\n");

    // Test 3: 2D array allocation
    printf("Test 3: 2D array allocation\n");
    size_t rows = 3, cols = 4;

    int **matrix = reallocarray(NULL, rows, sizeof(int *));
    if (!matrix)
    {
        fprintf(stderr, "Failed to allocate matrix rows\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = reallocarray(NULL, cols, sizeof(int));
        if (!matrix[i])
        {
            fprintf(stderr, "Failed to allocate matrix columns\n");
            // Cleanup previously allocated rows
            for (size_t j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    // Initialize and print matrix
    printf("Matrix (%zu x %zu):\n", rows, cols);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] = (int)(i * cols + j);
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Cleanup
    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    printf("\n");

    // Test 4: Growing a structure array
    printf("Test 4: Structure array\n");
    typedef struct
    {
        int id;
        double value;
    } Record;

    size_t record_count = 2;
    Record *records = reallocarray(NULL, record_count, sizeof(Record));
    if (!records)
    {
        fprintf(stderr, "Failed to allocate records\n");
        return EXIT_FAILURE;
    }

    records[0] = (Record){1, 3.14};
    records[1] = (Record){2, 2.71};

    printf("Initial records:\n");
    for (size_t i = 0; i < record_count; i++)
    {
        printf("  Record %d: id=%d, value=%.2f\n", (int)i, records[i].id, records[i].value);
    }

    // Grow to 4 records
    record_count = 4;
    Record *new_records = reallocarray(records, record_count, sizeof(Record));
    if (!new_records)
    {
        fprintf(stderr, "Failed to reallocate records\n");
        free(records);
        return EXIT_FAILURE;
    }
    records = new_records;

    records[2] = (Record){3, 1.41};
    records[3] = (Record){4, 1.73};

    printf("After growth:\n");
    for (size_t i = 0; i < record_count; i++)
    {
        printf("  Record %d: id=%d, value=%.2f\n", (int)i, records[i].id, records[i].value);
    }

    free(records);

    printf("\n=== Important Notes ===\n");
    printf("1. reallocarray(ptr, nmemb, size) is equivalent to realloc(ptr, nmemb * size)\n");
    printf("   but with overflow checking\n");
    printf("2. Available on OpenBSD, FreeBSD, and some Linux systems (glibc 2.26+)\n");
    printf("3. Prevents integer overflow vulnerabilities in size calculations\n");
    printf("4. Returns NULL and sets errno to ENOMEM on overflow\n");
    printf("5. More secure alternative to manual multiplication with realloc\n");

    return EXIT_SUCCESS;
}
