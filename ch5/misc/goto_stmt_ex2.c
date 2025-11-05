#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char name[50];
    double value;
} object_t;

int do_something(void)
{
    FILE *file1, *file2;
    object_t *obj;
    int ret_val = 0; // Initially assume a successful return value

    file1 = fopen("a_file", "w");
    if (file1 == NULL)
    {
        ret_val = -1;
        goto FAIL_FILE1;
    }

    file2 = fopen("another_file", "w");
    if (file2 == NULL)
    {
        ret_val = -1;
        goto FAIL_FILE2;
    }

    obj = malloc(sizeof(object_t));
    if (obj == NULL)
    {
        ret_val = -1;
        goto FAIL_OBJ;
    }

    // Operate on allocated resources
    obj->id = 42;
    strncpy(obj->name, "Example Object", sizeof(obj->name) - 1);
    obj->value = 3.14159;

    fprintf(file1, "Object ID: %d\n", obj->id);
    fprintf(file2, "Object Name: %s, Value: %f\n", obj->name, obj->value);

    printf("Successfully created and wrote to files\n");

    // Clean up everything
    free(obj);
FAIL_OBJ: // Otherwise, close only the resources we opened
    fclose(file2);
FAIL_FILE2:
    fclose(file1);
FAIL_FILE1:
    return ret_val;
}

// Demonstration of the pattern with different failure scenarios
int simulate_failure_at_step(int fail_at_step)
{
    FILE *file1 = NULL, *file2 = NULL;
    object_t *obj = NULL;
    int ret_val = 0;

    printf("\n=== Simulating failure at step %d ===\n", fail_at_step);

    // Step 1: Open first file
    if (fail_at_step != 1)
    {
        file1 = fopen("temp_file1.txt", "w");
        if (file1 == NULL)
        {
            printf("Step 1: Failed to open file1\n");
            ret_val = -1;
            goto FAIL_FILE1;
        }
        printf("Step 1: Opened file1 successfully\n");
    }
    else
    {
        printf("Step 1: Simulating file1 failure\n");
        ret_val = -1;
        goto FAIL_FILE1;
    }

    // Step 2: Open second file
    if (fail_at_step != 2)
    {
        file2 = fopen("temp_file2.txt", "w");
        if (file2 == NULL)
        {
            printf("Step 2: Failed to open file2\n");
            ret_val = -1;
            goto FAIL_FILE2;
        }
        printf("Step 2: Opened file2 successfully\n");
    }
    else
    {
        printf("Step 2: Simulating file2 failure\n");
        ret_val = -1;
        goto FAIL_FILE2;
    }

    // Step 3: Allocate memory
    if (fail_at_step != 3)
    {
        obj = malloc(sizeof(object_t));
        if (obj == NULL)
        {
            printf("Step 3: Failed to allocate memory\n");
            ret_val = -1;
            goto FAIL_OBJ;
        }
        printf("Step 3: Allocated memory successfully\n");
    }
    else
    {
        printf("Step 3: Simulating malloc failure\n");
        ret_val = -1;
        goto FAIL_OBJ;
    }

    // Success path
    printf("All steps succeeded, using resources...\n");
    obj->id = 100;
    fprintf(file1, "Success!\n");
    fprintf(file2, "Success!\n");

    // Cleanup (reverse order of acquisition)
    printf("Cleanup: Freeing memory\n");
    free(obj);
FAIL_OBJ:
    if (file2)
    {
        printf("Cleanup: Closing file2\n");
        fclose(file2);
    }
FAIL_FILE2:
    if (file1)
    {
        printf("Cleanup: Closing file1\n");
        fclose(file1);
    }
FAIL_FILE1:
    printf("Cleanup complete, returning %d\n", ret_val);
    return ret_val;
}

// Show what happens without goto (nested if statements)
int without_goto_pattern(void)
{
    FILE *file1, *file2;
    object_t *obj;
    int ret_val = 0;

    file1 = fopen("no_goto_file1.txt", "w");
    if (file1 == NULL)
    {
        return -1;
    }

    file2 = fopen("no_goto_file2.txt", "w");
    if (file2 == NULL)
    {
        fclose(file1); // Have to remember to close file1
        return -1;
    }

    obj = malloc(sizeof(object_t));
    if (obj == NULL)
    {
        fclose(file2); // Have to remember to close file2
        fclose(file1); // Have to remember to close file1
        return -1;
    }

    // Use resources
    fprintf(file1, "Data\n");
    fprintf(file2, "Data\n");

    // Cleanup - must be in correct order
    free(obj);
    fclose(file2);
    fclose(file1);

    return ret_val;
}

int main()
{
    printf("=== Goto for Resource Cleanup Pattern ===\n\n");

    // Test 1: Normal success case
    printf("Test 1: Normal operation (all resources acquired)\n");
    int result = do_something();
    printf("Result: %d\n", result == 0 ? "SUCCESS" : "FAILURE");

    // Clean up test files
    remove("a_file");
    remove("another_file");

    // Test 2: Demonstrate failure at each step
    printf("\n=== Demonstrating Failure at Each Step ===\n");

    for (int step = 1; step <= 3; step++)
    {
        simulate_failure_at_step(step);
    }

    // Also show success case
    printf("\n");
    simulate_failure_at_step(0); // No failure

    // Clean up temp files
    remove("temp_file1.txt");
    remove("temp_file2.txt");

    // Explanation
    printf("\n=== Why This Pattern Is Useful ===\n");
    printf("1. Resources are cleaned up in REVERSE order of acquisition\n");
    printf("2. Each label handles cleanup for resources acquired BEFORE it\n");
    printf("3. Prevents resource leaks even when errors occur\n");
    printf("4. Avoids deeply nested if-else blocks\n");
    printf("5. Single cleanup code path - easier to maintain\n\n");

    printf("Label execution flow on failure:\n");
    printf("- Fail at file1: FAIL_FILE1 only\n");
    printf("- Fail at file2: FAIL_FILE2 -> FAIL_FILE1\n");
    printf("- Fail at malloc: FAIL_OBJ -> FAIL_FILE2 -> FAIL_FILE1\n");
    printf("- Success: All cleanup labels executed in sequence\n");

    return EXIT_SUCCESS;
}
