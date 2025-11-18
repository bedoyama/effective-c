/*
 * Queue Test Program
 *
 * Demonstrates using the queue module and testing all its functionality.
 * This is the main program that uses the queue library.
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void)
{
    printf("=== Queue Implementation Test ===\n\n");

    printf("Test 1: Create queue\n");
    Queue *q = queue_create();
    if (q == NULL)
    {
        fprintf(stderr, "Failed to create queue\n");
        return EXIT_FAILURE;
    }
    printf("  ✓ Queue created successfully\n");
    queue_print(q);
    printf("\n");

    printf("Test 2: Check empty queue\n");
    printf("  queue_is_empty() = %s\n", queue_is_empty(q) ? "true" : "false");
    printf("  queue_size() = %zu\n", queue_size(q));
    printf("\n");

    printf("Test 3: Enqueue elements\n");
    for (int i = 1; i <= 5; i++)
    {
        if (queue_enqueue(q, i * 10))
        {
            printf("  ✓ Enqueued: %d\n", i * 10);
        }
        else
        {
            printf("  ✗ Failed to enqueue: %d\n", i * 10);
        }
    }
    queue_print(q);
    printf("\n");

    printf("Test 4: Peek at front element\n");
    int value;
    if (queue_peek(q, &value))
    {
        printf("  ✓ Front element: %d\n", value);
    }
    else
    {
        printf("  ✗ Failed to peek\n");
    }
    queue_print(q);
    printf("\n");

    printf("Test 5: Dequeue some elements\n");
    for (int i = 0; i < 3; i++)
    {
        if (queue_dequeue(q, &value))
        {
            printf("  ✓ Dequeued: %d\n", value);
        }
        else
        {
            printf("  ✗ Failed to dequeue\n");
        }
    }
    queue_print(q);
    printf("\n");

    printf("Test 6: Enqueue more elements\n");
    for (int i = 6; i <= 8; i++)
    {
        if (queue_enqueue(q, i * 10))
        {
            printf("  ✓ Enqueued: %d\n", i * 10);
        }
        else
        {
            printf("  ✗ Failed to enqueue: %d\n", i * 10);
        }
    }
    queue_print(q);
    printf("\n");

    printf("Test 7: Queue size\n");
    printf("  Current size: %zu\n", queue_size(q));
    printf("  Is empty: %s\n", queue_is_empty(q) ? "true" : "false");
    printf("  Is full: %s\n", queue_is_full(q) ? "true" : "false");
    printf("\n");

    printf("Test 8: Clear queue\n");
    queue_clear(q);
    printf("  ✓ Queue cleared\n");
    queue_print(q);
    printf("\n");

    printf("Test 9: Test with wrap-around\n");
    // Fill the queue near capacity to test circular behavior
    for (int i = 0; i < QUEUE_CAPACITY - 1; i++)
    {
        queue_enqueue(q, i);
    }
    printf("  Filled queue with %d elements\n", QUEUE_CAPACITY - 1);
    printf("  Is full: %s\n", queue_is_full(q) ? "true" : "false");

    // Dequeue some
    for (int i = 0; i < 10; i++)
    {
        queue_dequeue(q, NULL);
    }
    printf("  Dequeued 10 elements\n");

    // Enqueue more (will wrap around)
    for (int i = 0; i < 10; i++)
    {
        queue_enqueue(q, 1000 + i);
    }
    printf("  Enqueued 10 new elements (with wrap-around)\n");
    printf("  Final size: %zu\n", queue_size(q));
    printf("\n");

    printf("Test 10: Cleanup\n");
    queue_destroy(q);
    printf("  ✓ Queue destroyed\n\n");

    printf("=== Program Structure Demonstration ===\n");
    printf("This example demonstrates:\n");
    printf("1. Header file (queue.h) - Public interface\n");
    printf("2. Implementation file (queue.c) - Private implementation\n");
    printf("3. Main file (queue_main.c) - Application code\n");
    printf("4. Opaque types - Hide implementation details\n");
    printf("5. Proper separation of concerns\n");
    printf("6. Compilation: gcc -c queue.c && gcc queue.o queue_main.c -o queue\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. File Structure:
 *    - queue.h: Interface (declarations, type definitions)
 *    - queue.c: Implementation (function definitions)
 *    - queue_main.c: Application (uses the queue)
 *
 * 2. Opaque Types:
 *    - struct queue defined only in queue.c
 *    - Users only get a pointer (Queue *)
 *    - Implementation can change without affecting users
 *
 * 3. Compilation Steps:
 *    Step 1: gcc -c queue.c -o queue.o         (compile implementation)
 *    Step 2: gcc queue.o queue_main.c -o queue (link with main)
 *    Or:     gcc queue.c queue_main.c -o queue (compile and link together)
 *
 * 4. Benefits:
 *    - Encapsulation: Implementation hidden
 *    - Modularity: Each file has one responsibility
 *    - Reusability: Queue can be used in other programs
 *    - Maintainability: Changes to implementation don't affect interface
 */
