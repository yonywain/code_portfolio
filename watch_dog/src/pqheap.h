/* RC3 */
#ifndef ILRD_PQHEAP_H
#define ILRD_PQHEAP_H

#include "heap.h"


typedef int (*pqueue_match_func_t)(const void *task,
                                   const void *uid,
                                   const void *param);

typedef int (*pqueue_cmp_func_t)(const void *user_data,
                             const void *array_data,
                             void *param);

typedef struct p_queue p_queue_t;


/*
* Create new priority queue
* Return Value: A pointer to the priority
* Parameters  : sort_func: the function used for enqueuing the data
* Input       : sort_func cannot be NULL
* Time Complexity: O(1)
*/
p_queue_t *PQueueCreate(pqueue_cmp_func_t sort_func);


/*
* Destroys the priority queue
* Return Value: - 
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(n)
*/
void PQueueDestroy(p_queue_t *p_queue);


/*
* Inserts new data into the priority queue
* Return Value: 0 in case of success, 1 otherwise
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(1)
*/
int PQueueEnqueue(p_queue_t *p_queue, const void *data);


/*
* Removes the head of the queue
* Return Value: - 
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(1)
*/
void PQueueDequeue(p_queue_t *p_queue);


/*
* Returns the number of elements in the queue
* Return Value: number of elements in the queue
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(n)
*/
size_t PQueueSize(p_queue_t *p_queue);


/*
* Checks whether the queue is empty or not
* Return Value: 1 in case the queue is empyu, 0 otherwise
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(1)
*/
int PQueueIsEmpty(p_queue_t *p_queue);


/*
* Returns the data in the head of the priority queue
* Return Value: Returns the data in the head of the priority queue
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(1)
*/
void *PQueuePeek(p_queue_t *p_queue);


/*
* Removes data in the queue according to a certain parameter
* Return Value: 
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
*               match_func cannot be NULL
* Time Complexity: O(n)
*/
void *PQueueRemove(p_queue_t *p_queue,
                   pqueue_match_func_t match_func,
                   const void *user_data);


/*
* Removes all the data in the queue
* Return Value: - 
* Parameters  : p_queue: the priority queue
* Input       : p_queue cannot be NULL
* Time Complexity: O(n)
*/
void PQueueClear(p_queue_t *p_queue);


#endif
