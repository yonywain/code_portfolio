/****************************************
* Author: Oksana Rubanov               *
* Date: 27/11/2018                     *
* Reviewer: Ori Friedman               *
****************************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memmove */

#include "dynamic_vector.h" /* API */ 

struct dynamic_vector
{
	void *head;
	size_t element_size;
	size_t size;
	size_t capacity;
};

vector_t *DVectorCreate(size_t number_of_elements, size_t element_size)
{
	vector_t *vector = NULL;

	assert(number_of_elements > 0 && element_size > 0);

	vector = (vector_t *)malloc(sizeof(vector_t));
	vector->head = malloc(number_of_elements * element_size);
	
	if(NULL == vector->head || NULL == vector)
	{
		return NULL;
	}
	
	vector->element_size = element_size;
	vector->size = 0;
	vector->capacity = number_of_elements;

	return vector;
}

void DVectorDestroy(vector_t *vector)
{
	vector->element_size = 0;
	vector->size = 0;
	vector->capacity = 0;
	
	free(vector->head);
 	free(vector);
}

void *DVectorGetItemAddress(vector_t *vector, size_t index)
{
	char *ptr = NULL;

	assert(NULL != vector);
	
	ptr = (char *)vector->head;
	ptr += (index *	vector->element_size);
	
	return ptr;
}

int DVectorPush(vector_t *vector, const void *element)
{
	char *runner = NULL;
	char *temp = NULL;

	assert(NULL != vector && NULL != element);

	if(vector->size == vector->capacity)
	{
		vector->capacity *= 2;
		temp = (char *)realloc(vector->head, vector->capacity * vector->element_size);
		
		if(NULL == vector->head)
		{
			return 1;
		}
		vector->head = temp;
	}	
	
	runner = (char *)vector->head;
	runner += (vector->size * vector->element_size);
	memmove(runner, element, vector->element_size);
	vector->size += 1;

	return 0;
}

int DVectorPop(vector_t *vector)
{
	assert(NULL != vector && 0 != vector->size);
	
	vector->size -= 1;
	
	if(vector->capacity / 4 >= vector->size)
	{
		vector->capacity = (vector->capacity / 2) + 1;
		vector->head = (char *)realloc(vector->head, vector->capacity * vector->element_size);

		if(NULL == vector->head)
		{
			return 1;
		}
	}
	
	return 0;
}


int DVectorReserve(vector_t *vector, size_t fix_size)
{
	void *temp = NULL;

	assert(NULL != vector);

	if(fix_size > vector->size)
	{
		vector->capacity = fix_size;
	}
	else
	{
		vector->capacity = vector->size;
	}
		
	temp = realloc(vector->head, (vector->capacity * vector->element_size));

	if(NULL == vector->head)
	{
		return 1;
	}
	
	vector->head = temp;

	return 0;
}


size_t DVectorSize(const vector_t *vector)
{
	assert(NULL != vector);	

	return vector->size;
}

size_t DVectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->capacity;
}

