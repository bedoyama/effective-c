#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Goto Statement ===\n\n");

    // Simple goto
    printf("Simple goto:\n");
    int i = 0;

start_label:
    printf("i = %d\n", i);
    i++;
    if (i < 3)
    {
        goto start_label;
    }
    printf("Done\n\n");

    // Forward jump
    printf("Forward jump:\n");
    int condition = 1;
    if (condition)
    {
        printf("Jumping forward...\n");
        goto forward_label;
    }
    printf("This is skipped\n");

forward_label:
    printf("Arrived at forward label\n\n");

    // Error handling pattern (one of the acceptable uses)
    printf("Error handling with goto:\n");
    int error = 0;
    int *ptr1 = NULL;
    int *ptr2 = NULL;

    ptr1 = (int *)malloc(sizeof(int));
    if (ptr1 == NULL)
    {
        printf("Failed to allocate ptr1\n");
        error = 1;
        goto cleanup;
    }
    printf("Allocated ptr1\n");

    ptr2 = (int *)malloc(sizeof(int));
    if (ptr2 == NULL)
    {
        printf("Failed to allocate ptr2\n");
        error = 1;
        goto cleanup;
    }
    printf("Allocated ptr2\n");

    // Use the pointers
    *ptr1 = 10;
    *ptr2 = 20;
    printf("ptr1 = %d, ptr2 = %d\n", *ptr1, *ptr2);

cleanup:
    printf("Cleanup phase\n");
    if (ptr1)
    {
        free(ptr1);
        printf("Freed ptr1\n");
    }
    if (ptr2)
    {
        free(ptr2);
        printf("Freed ptr2\n");
    }

    if (error)
    {
        printf("Function failed\n");
    }
    else
    {
        printf("Function succeeded\n");
    }

    return EXIT_SUCCESS;
}
