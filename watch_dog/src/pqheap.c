/***************************************
* Author: Yoni Wainsztok
* Date: 20/01/2019
* Reviewer: Magal
* Subject: pqheap-RC1
***************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dynamic_vector.h"
#include "pqheap.h"

struct p_queue
{
    vector_t *d_vector;
	heap_cmp_func_t cmp_func;
};

const int WORD_SIZE = sizeof(size_t);

static void SwapPQueueIMP(void **value1, void **value2);
void PrintPQ(p_queue_t *pq);


p_queue_t *PQueueCreate(heap_cmp_func_t sort_func)
{
	p_queue_t *pq = NULL;

	assert(NULL != sort_func);

	pq = (p_queue_t *)malloc(sizeof(p_queue_t));

	if(NULL == pq)
	{
		return (NULL);
	}

	pq->d_vector = DVectorCreate(20, WORD_SIZE);

	if(NULL == pq->d_vector)
	{
		free(pq);

		return (NULL);
	}
	pq->cmp_func = sort_func;

	return (pq);
}


void PQueueDestroy(p_queue_t *p_queue)
{
	assert(NULL != p_queue);

	DVectorDestroy(p_queue->d_vector);
	p_queue->d_vector = NULL;
	p_queue->cmp_func = NULL;

	free(p_queue);
}


int PQueueEnqueue(p_queue_t *p_queue, const void *data)
{
	int result = 0;

	assert(NULL != p_queue);

	result = DVectorPush(p_queue->d_vector, &data);
	if(0 == result)
    {
		HeapifyUp(	DVectorGetItemAddress(p_queue->d_vector, 0),
					p_queue->cmp_func,
					PQueueSize(p_queue) - 1,
					PQueueSize(p_queue),
					NULL);
	}
	
	return (result);
}


void PQueueDequeue(p_queue_t *p_queue)
{
	assert(NULL != p_queue);

	SwapPQueueIMP(	DVectorGetItemAddress(p_queue->d_vector, 0),
					DVectorGetItemAddress(	p_queue->d_vector, 
											PQueueSize(p_queue) - 1));
	DVectorPop(p_queue->d_vector);
	HeapifyDown(DVectorGetItemAddress(p_queue->d_vector, 0),
				p_queue->cmp_func,
				0,
				PQueueSize(p_queue),
				NULL);
}


size_t PQueueSize(p_queue_t *p_queue)
{
	assert(NULL != p_queue);

	return (DVectorSize(p_queue->d_vector));
}


int PQueueIsEmpty(p_queue_t *p_queue)
{
	assert(NULL != p_queue);

	return (0 == DVectorSize(p_queue->d_vector) ? 1 : 0);
}


void *PQueuePeek(p_queue_t *p_queue)
{
	void **data = NULL;

	assert(NULL != p_queue);

	data = DVectorGetItemAddress(p_queue->d_vector, 0);

	return (*data);
}


void *PQueueRemove(p_queue_t *p_queue,
                   pqueue_match_func_t match_func,
                   const void *user_data)
{
	size_t i = 0;
	void **data = NULL;
	void **item_address = NULL;
	void * return_data = NULL;

	assert(NULL != p_queue);
	assert(NULL != match_func);

	for(i = 0; i < PQueueSize(p_queue); ++i)
	{
		item_address = DVectorGetItemAddress(p_queue->d_vector, i);
		if(1 == match_func(*item_address, user_data, NULL))
		{
			data = DVectorGetItemAddress(	p_queue->d_vector, 
											PQueueSize(p_queue) - 1);
			SwapPQueueIMP(	item_address, data);
			return_data = *data;
			if(0 == DVectorPop(p_queue->d_vector))
			{
				return (NULL);
			}
			HeapifyUp(	DVectorGetItemAddress(p_queue->d_vector, 0),
						p_queue->cmp_func,
						i,
						PQueueSize(p_queue),
						NULL);
			HeapifyDown(DVectorGetItemAddress(p_queue->d_vector, 0),
						p_queue->cmp_func,
						i,
						PQueueSize(p_queue),
						NULL);

			return (return_data);
		}
	}
	
	return (NULL);
}


void PQueueClear(p_queue_t *p_queue)
{
	assert(NULL != p_queue);

	while(1 != PQueueIsEmpty(p_queue))
	{
		PQueueDequeue(p_queue);
	}

}


static void SwapPQueueIMP(void **value1, void **value2)
{
	void *temp = *value1;
	*value1 = *value2;
	*value2 = temp;
}


void PrintPQ(p_queue_t *pq)
{
	size_t i = 0;
    size_t size = PQueueSize(pq);

	printf("------------------------------\n");
	for(i = 0; i < size; ++i)
	{
		printf("%d ", **(int**)DVectorGetItemAddress(pq->d_vector, i));	
	}
	printf("\n");
	printf("------------------------------\n");
}