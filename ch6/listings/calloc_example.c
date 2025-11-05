#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== calloc - Zero-Initialized Allocation ===\n\n");

    // Basic calloc usage
    printf("Test 1: Allocating array with calloc\n");
    int n = 5;
    int *arr = (int *)calloc(n, sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Allocated array of %d integers (zero-initialized):\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Now set values
    printf("\nSetting values:\n");
    for (int i = 0; i < n; i++)
    {
        arr[i] = i * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    printf("\n");

    // calloc vs malloc comparison
    printf("Test 2: calloc vs malloc\n");

    printf("\nWith malloc (uninitialized):\n");
    int *malloc_arr = (int *)malloc(5 * sizeof(int));
    if (malloc_arr == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 5; i++)
    {
        printf("malloc_arr[%d] = %d (garbage)\n", i, malloc_arr[i]);
    }
    free(malloc_arr);

    printf("\nWith calloc (zero-initialized):\n");
    int *calloc_arr = (int *)calloc(5, sizeof(int));
    if (calloc_arr == NULL)
    {
        fprintf(stderr, "calloc failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < 5; i++)
    {
        printf("calloc_arr[%d] = %d (zero)\n", i, calloc_arr[i]);
    }
    free(calloc_arr);
    printf("\n");

    // Allocating struct array
    typedef struct
    {
        int id;
        double score;
    } Student;

    printf("Test 3: Allocating array of structs\n");
    size_t num_students = 3;
    Student *students = (Student *)calloc(num_students, sizeof(Student));
    if (students == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("All students zero-initialized:\n");
    for (size_t i = 0; i < num_students; i++)
    {
        printf("Student %zu: id=%d, score=%.1f\n",
               i, students[i].id, students[i].score);
    }

    // Set some values
    students[0].id = 101;
    students[0].score = 95.5;
    students[1].id = 102;
    students[1].score = 88.0;

    printf("\nAfter setting values:\n");
    for (size_t i = 0; i < num_students; i++)
    {
        printf("Student %zu: id=%d, score=%.1f\n",
               i, students[i].id, students[i].score);
    }

    free(students);
    printf("\n");

    // Overflow checking (calloc checks for overflow)
    printf("Test 4: calloc overflow protection\n");
    size_t huge_count = SIZE_MAX / 2;
    size_t huge_size = SIZE_MAX / 2;
    printf("Attempting to allocate SIZE_MAX/2 * SIZE_MAX/2 bytes...\n");
    void *overflow = calloc(huge_count, huge_size);
    if (overflow == NULL)
    {
        printf("calloc correctly failed (would overflow)\n");
    }
    else
    {
        printf("Allocation succeeded (unexpected)\n");
        free(overflow);
    }
    printf("\n");

    // Important notes
    printf("=== Important Notes ===\n");
    printf("1. calloc(num_elements, size_per_element)\n");
    printf("2. calloc initializes ALL bytes to zero\n");
    printf("3. calloc checks for overflow in size calculation\n");
    printf("4. Use calloc when you need zero-initialized memory\n");
    printf("5. Slightly slower than malloc due to initialization\n");
    printf("6. calloc(n, size) is safer than malloc(n * size)\n");

    return EXIT_SUCCESS;
}
