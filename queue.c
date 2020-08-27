#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "queue.h"

/**
 * Author: Manuel Cruz
 * Purpose: Defines the operations to do to a queue
 */

void set_queue(queue_t* queue)
{
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;
}

void release_queue(queue_t* queue)
{
	if (queue == NULL)
	{
		fprintf(stderr, "Cannot destroy a NULL queue\n");
		exit(NULL_ERROR);
	}
	
	// remove everything from queue
	while (queue->size > 0)
		pop(queue);
}

void push(queue_t* queue, void* element)
{
	if (queue == NULL)
	{
		fprintf(stderr, "Cannot push to a NULL queue\n");
		exit(NULL_ERROR);
	}
	
	if (element == NULL)
	{
		fprintf(stderr, "Cannot push a NULL element\n");
		exit(NULL_ERROR);
	}
	
	element_t* element_struct = (element_t*) malloc(sizeof(element_t));
	if (element_struct == NULL)
	{
		fprintf(stderr, "Cannot create element struct to push to queue");
		fprintf(stderr, ", not enough memory\n");
		exit(MEMORY_ERROR);
	}
	
	// set element struct
	element_struct->element = element;
	element_struct->next = NULL;
	
	// if first element is being added make it first and last
	if (queue->size == 0)
	{
		queue->first = element_struct;
		queue->last = element_struct;
	}
	// make the last one point to the new one and 
	// the make the new one the last one
	else
	{
		queue->last->next = element_struct;
		queue->last = element_struct;
	}
	queue->size++;
}

void* pop(queue_t* queue)
{
	if (queue == NULL)
	{
		fprintf(stderr, "Cannot pop a NULL queue\n");
		exit(NULL_ERROR);
	}
	
	if (queue->size == 0)
	{
		fprintf(stderr, "Cannot pop an empty queue\n");
		exit(POP_EMPTY_QUEUE);
	}
	
	element_t* element_struct = queue->first;
	void* element = element_struct->element;
	queue->first = element_struct->next;
	free(element_struct);
	
	queue->size--;
	if(queue->size == 0)
		queue->last = NULL;
		
	return element;
}

bool is_empty(queue_t* queue)
{
	if (queue == NULL)
	{
		fprintf(stderr, "Cannot check size of NULL queue\n");
		exit(NULL_ERROR);
	}
	return queue->size == 0;
}
