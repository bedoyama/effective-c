/*
 * Queue Implementation - Demonstrating Program Structure
 *
 * This is the header file (interface) for a simple integer queue.
 * Shows proper header structure with guards, includes, and declarations.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

// Queue configuration
#define QUEUE_CAPACITY 100

// Opaque type - implementation details hidden
typedef struct queue Queue;

// Queue operations (public interface)
Queue *queue_create(void);
void queue_destroy(Queue *q);

bool queue_enqueue(Queue *q, int value);
bool queue_dequeue(Queue *q, int *value);
bool queue_peek(const Queue *q, int *value);

size_t queue_size(const Queue *q);
bool queue_is_empty(const Queue *q);
bool queue_is_full(const Queue *q);
void queue_clear(Queue *q);

void queue_print(const Queue *q);

#endif /* QUEUE_H */
