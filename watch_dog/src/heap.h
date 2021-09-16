/* RC4 */
#ifndef ILRD_HEAP_H
#define ILRD_HEAP_H


typedef int (*heap_match_func_t)( const void *user_data,
                                const void *array_data,
                                const void *param);
                                
typedef int (*heap_cmp_func_t)( const void *user_data,
                                const void *array_data,
                                void *param);


/*
* Heapify up the data at index in the given array
* Return Value: -
* Parameters  : array: the given array
                cmp_func: a user comparison function - parameters:
                                                       const void *user_data
                                                       const void *array_data
                                                       void *param
                index: the index of the data in the array
                arr_size: the size of the array
* Input       : array, cmp_func cannot be NULL
                index must be >= 0 and < arr_size
                arr_size cannot be 0
* Time Complexity: O(logn)
*/
void HeapifyUp(void *array, heap_cmp_func_t cmp_func, size_t index, 
               size_t arr_size, void *cmp_param);


/*
* Heapify down the data at index in the given array
* Return Value: -
* Parameters  : array: the given array
                cmp_func: a user comparison function - parameters:
                                                       const void *user_data
                                                       const void *array_data
                                                       void *param
                index: the index of the data in the array
                arr_size: the size of the array
* Input       : array, cmp_func cannot be NULL
                index must be >= 0 and < arr_size
                arr_size cannot be 0
* Time Complexity: O(logn)
*/
void HeapifyDown(void *array, heap_cmp_func_t cmp_func, size_t index, 
                 size_t arr_size, void *cmp_param);

#endif
