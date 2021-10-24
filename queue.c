/***********************
* Daniel Knafel
* 316012624
* Group 01 - CS
* Assignment 5
***********************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "element.h"
#include "queue.h"

/******************
* Function Name: initQueue
* Input: None
* Output: Queue*
* Function Operation: Initiates a new queue 
******************/
Queue* initQueue()
{
	Queue* queue = (Queue*) malloc(sizeof(Queue));

	// assert memory allocation
	if (queue == NULL)
	{
		printf("Memory not allocated in %s, %s", __FILE__, __func__);
		return NULL;
	}

	queue->s1 = initStack();
	if (queue->s1 == NULL)
		return NULL;

	queue->s2 = initStack();
	if (queue->s2 == NULL)
		return NULL;
	
	assert(queue != NULL && queue->s1 != NULL && queue->s2 != NULL);

	return queue;
}
/******************
* Function Name: destroyQueue
* Input: Queue* queue
* Output: None
* Function Operation: Frees all memory allocated for the queue on the heap 
******************/
void destroyQueue(Queue* queue)
{
	if (queue->s1 != NULL)
		destroyStack(queue->s1);
	if (queue->s2 != NULL)
		destroyStack(queue->s2);
	if (queue != NULL)
		free(queue);
}
/******************
* Function Name: isQueueEmpty
* Input: Queue* queue
* Output: Int
* Function Operation: Returns 1 if the queue is currently empty, and 0 if it isn't
******************/
int isQueueEmpty(Queue* queue)
{
	if (isStackEmpty(queue->s1) && isStackEmpty(queue->s2))
		return 1;
	return 0;
}
/******************
* Function Name: lenOfQueue
* Input: Queue* queue
* Output: Int
* Function Operation: Returns the amount of Elements currently in the queue
******************/
int lenOfQueue(Queue* queue)
{
	return (lenOfStack(queue->s1) + lenOfStack(queue->s2));
}
/******************
* Function Name: capacityOfQueue
* Input: Queue* queue
* Output: Int
* Function Operation: Returns the current amount of Element-type memory blocks allocated to the queue 
******************/
int capacityOfQueue(Queue* queue)
{
	return (capacityOfStack(queue->s1) + capacityOfStack(queue->s2));
}
/******************
* Function Name: enqueue
* Input: Queue* queue, Element element
* Output: None
* Function Operation: Adds an Element to the queue
******************/
void enqueue(Queue* queue, Element element)
{
	push(queue->s1, element);
}
/******************
* Function Name: copyStacks
* Input: Queue* queue
* Output: None
* Function Operation: Copies the content of the input stack to the output stack
******************/
void copyStacks(Queue* queue)
{
	while (lenOfStack(queue->s1) > 0)
	{
		push(queue->s2, pop(queue->s1));
	}
}
/******************
* Function Name: dequeue
* Input: Queue* queue
* Output: Element
* Function Operation: Returns the the first Element of the queue and removes it from the queue
******************/
Element dequeue(Queue* queue)
{
	assert(lenOfStack(queue->s1) >= 0 && lenOfStack(queue->s2) >= 0);

	if (lenOfStack(queue->s2) == 0)
		copyStacks(queue);	

	return pop(queue->s2);
}
/******************
* Function Name: peek
* Input: Queue* queue
* Output: Element
* Function Operation: Returns the the first Element of the queue without removing it from the queue
******************/
Element peek(Queue* queue)
{
	assert((lenOfStack(queue->s1) + lenOfStack(queue->s2)) >= 0);

	if (lenOfStack(queue->s2) == 0)
		copyStacks(queue);

	return top(queue->s2);
}