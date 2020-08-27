#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/**
 * Author: Manuel Cruz
 * Purpose: Describes a queue, and also an element of a queue.
 */

/**
 * Description of an element in queue
 */
typedef struct
{
	void* element;
	void* next;
} element_t;

/**
 * Description of a queue structure
 */
typedef struct
{
	element_t* first;
	element_t* last;
	size_t     size;
} queue_t;

/**
 * Sets a queue that has already been created.
 */
void set_queue(queue_t* queue);

/**
 * Destroys a queue structure. If NULL will crash.
 * @param queue - Pointer to where queue is located. Cannot be NULL
 */
void release_queue(queue_t* queue);

/**
 * Pushes an element to the back of the queue.
 * @param queue - Queue structure to push to. Cannot be NULL, it will crash.
 * @param element - Element to push. Cannot be NULL, it will crash
 */
void push(queue_t* queue, void* element);

/**
 * Pops an element to the back of the queue.
 * @param queue - Queue structure to pop from. Cannot be NULL, It will crash.
 *
 * @return element in front of queue
 */
void* pop(queue_t* queue);

/**
 * Checks whether the given queue is empty or not
 *
 * @param queue - queue to check. Cannot be NULL, it will crash.
 *
 * @return true if it is empty. False, otherwise.
 */
bool is_empty(queue_t* queue);

#endif
