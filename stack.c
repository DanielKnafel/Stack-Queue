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

#define NDEBUG
#define DEFAULT_SIZE 1
#define EMPTY_STACK -1

/******************
* Function Name: initStack
* Input: None
* Output: Stack*
* Function Operation: Initiates a new stack
******************/
Stack* initStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));

	// assert memory allocation
	if (stack == NULL)
	{
		printf("Memory not allocated in %s, %s", __FILE__, __func__);
		return NULL;
	}

	Element* content = (Element*)malloc(sizeof(Element));

	// assert memory allocation
	if (content == NULL)
	{
		printf("Memory not allocated in %s, %s", __FILE__, __func__);
		return NULL;
	}

	assert(content != NULL && stack != NULL);

	// Initiate a new stack with size 1
	stack->content = content;
	stack->size = DEFAULT_SIZE;
	stack->topIndex = EMPTY_STACK;

	return stack;
}
/******************
* Function Name: destroyStack
* Input: Stack* stack
* Output: None
* Function Operation: Frees all memory allocated for the stack on the heap
******************/
void destroyStack(Stack* stack)
{
	if (stack->content != NULL)
		free(stack->content);
	if (stack != NULL)
		free (stack);
}
/******************
* Function Name: isStackEmpty
* Input: Stack* stack
* Output: Int
* Function Operation: Returns 1 if the stack is currently empty, and 0 if it isn't
******************/
int isStackEmpty(Stack* stack)
{
	if (stack->topIndex == EMPTY_STACK)
		return 1;
	return 0;
}
/******************
* Function Name: lenOfStack
* Input: Stack* stack
* Output: Int
* Function Operation: Returns the amount of Elements currently in the stack
******************/
int lenOfStack(Stack* stack)
{
	return stack->topIndex + 1;
}
/******************
* Function Name: capacityOfStack
* Input: Stack* stack
* Output: Int
* Function Operation: Returns the current amount of Element-type memory blocks allocated to the queue
******************/
int capacityOfStack(Stack* stack)
{
	return stack->size;
}
/******************
* Function Name: resizeStack
* Input: Stack* stack, int newSize
* Output: Element*
* Function Operation: Reallocates a given stack to a new size. Returns a pointer to the new address.
******************/
Element* resizeStack(Stack* stack, int newSize)
{
	Element* newStack = realloc(stack->content, sizeof(Element) * newSize);
	// Allocation failed
	if (newStack == NULL)
	{
		printf("Memory not allocated in %s, %s", __FILE__, __func__);
		newStack = stack->content;
	}
	else
		stack->size = newSize;
	return newStack;
}
/******************
* Function Name: push
* Input: Stack* stack, Element element
* Output: Void
* Function Operation: Adds a given Element to an existing stack
******************/
void push(Stack* stack, Element element)
{
	// Update the topIndex and make add the new Element to the stack if possible
	if (stack->topIndex+1 < stack->size)
		stack->content[++stack->topIndex] = element;

	// if the stack will be full after the push, double its size first.
	if (stack->topIndex + 1 == stack->size)
		stack->content = resizeStack(stack, stack->size * 2);
}
/******************
* Function Name: pop
* Input: Stack* stack
* Output: Element element
* Function Operation: Removes the top Element of a given stack and returns it
******************/
Element pop(Stack* stack)
{
	assert(stack->topIndex != EMPTY_STACK);

	Element top = stack->content[stack->topIndex];

	// If the stack is will be less than half-full after the pop, reduce its size by half.
	if (stack->topIndex < stack->size / 2 && stack->size > DEFAULT_SIZE)
		stack->content = resizeStack(stack, (stack->size / 2));
	// Update the topIndex
	stack->topIndex--;
	return top;
}
/******************
* Function Name: top
* Input: Stack* stack
* Output: Element element
* Function Operation: Returns the top Element of a given stack without changing the stack
******************/
Element top(Stack* stack)
{
	assert(stack->topIndex != EMPTY_STACK);

	return stack->content[stack->topIndex];
}
/******************
* Function Name: printStack
* Input: Stack* stack
* Output: Void
* Function Operation: Prints all the Elements in a given stack
******************/
void printStack(Stack* stack)
{
	if (stack->topIndex == EMPTY_STACK)
		printf("can't print! stack is empty!\n");
	else
	{
		for (int i = stack->topIndex; i >= 0; i--)
		{
			if (stack->content[i].c > 0)
			{
				printf("%d: ", i + 1);
				printElement(stack->content[i]);
				printf("\n");
			}
		}
	}
}
