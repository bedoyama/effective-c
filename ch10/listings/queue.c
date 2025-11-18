/*
 * Queue Implementation - Implementation File
 *
 * This is the implementation file for the queue.
 * Shows proper separation of interface and implementation.
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementation details (private structure)
struct queue
{
    int data[QUEUE_CAPACITY];
    size_t front;
    size_t rear;
    size_t count;
};

// Create a new queue
Queue *queue_create(void)
{
    Queue *q = malloc(sizeof(Queue));
    if (q == NULL)
    {
        return NULL;
    }

    q->front = 0;
    q->rear = 0;
    q->count = 0;

    return q;
}

// Destroy the queue and free memory
void queue_destroy(Queue *q)
{
    free(q);
}

// Add an element to the rear of the queue
bool queue_enqueue(Queue *q, int value)
{
    if (q == NULL || queue_is_full(q))
    {
        return false;
    }

    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % QUEUE_CAPACITY;
    q->count++;

    return true;
}

// Remove an element from the front of the queue
bool queue_dequeue(Queue *q, int *value)
{
    if (q == NULL || queue_is_empty(q))
    {
        return false;
    }

    if (value != NULL)
    {
        *value = q->data[q->front];
    }

    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->count--;

    return true;
}

// Look at the front element without removing it
bool queue_peek(const Queue *q, int *value)
{
    if (q == NULL || queue_is_empty(q))
    {
        return false;
    }

    if (value != NULL)
    {
        *value = q->data[q->front];
    }

    return true;
}

// Get the current size of the queue
size_t queue_size(const Queue *q)
{
    return (q == NULL) ? 0 : q->count;
}

// Check if the queue is empty
bool queue_is_empty(const Queue *q)
{
    return (q == NULL) || (q->count == 0);
}

// Check if the queue is full
bool queue_is_full(const Queue *q)
{
    return (q != NULL) && (q->count >= QUEUE_CAPACITY);
}

// Remove all elements from the queue
void queue_clear(Queue *q)
{
    if (q == NULL)
    {
        return;
    }

    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// Print the queue contents (for debugging)
void queue_print(const Queue *q)
{
    if (q == NULL)
    {
        printf("Queue: NULL\n");
        return;
    }

    printf("Queue: [");

    if (!queue_is_empty(q))
    {
        size_t index = q->front;
        for (size_t i = 0; i < q->count; i++)
        {
            printf("%d", q->data[index]);
            if (i < q->count - 1)
            {
                printf(", ");
            }
            index = (index + 1) % QUEUE_CAPACITY;
        }
    }

    printf("] (size=%zu)\n", q->count);
}
