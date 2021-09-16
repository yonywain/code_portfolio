/****************************************
* Author: Yoni Wainsztok                *
* Date: 27/11/2018                      *
****************************************/

#include <assert.h>/* assert */
#include <string.h>/* memmove */
#include <stdlib.h>/* malloc */
#include "stack.h"/* function declarations */

struct stack
{
	void *curr;
	void *end;
	size_t elementSize;
	char head[1];
};


stack_t *StackCreate(size_t size, size_t element_size)
{
	stack_t *returnedMem = 
		(stack_t *)malloc(sizeof(stack_t) + (size * element_size) - 1);

	if(NULL == returnedMem)
	{
		return NULL;
	}
	
	returnedMem->elementSize = element_size;
	returnedMem->curr = returnedMem->head;
	returnedMem->end = (char *)returnedMem->curr + (size * element_size) - 1;

	return returnedMem;
}


void StackDestroy(stack_t *data_stack)
{
	assert(NULL != data_stack);
	
	free(data_stack);
}

int StackPush(stack_t *data_stack, const void *added_element)
{
	assert(NULL != data_stack && NULL != added_element);
	 
	if(data_stack->curr > data_stack->end)
	{
		return 0;
	}
	else
	{
		memmove(data_stack->curr, added_element, data_stack->elementSize);
		data_stack->curr = (char *)data_stack->curr + data_stack->elementSize;
		return 1;
	}
}


void StackPop(stack_t *data_stack)
{
	assert(NULL != data_stack);
	
	data_stack->curr = (char *)data_stack->curr - data_stack->elementSize;
}


void *StackPeek(stack_t *data_stack)
{
	assert(NULL != data_stack);
	
	if(data_stack->curr == data_stack->head)
	{
		return NULL;
	}

	return ((char *)data_stack->curr - data_stack->elementSize);
}


size_t StackSize (const stack_t *data_stack)
{
	assert(NULL != data_stack);
	
	return (((char *)data_stack->curr - (char *)data_stack->head)/data_stack->elementSize);
}

