/***************************************
* Author: Yoni Wainsztok
* Date: 20/01/2019
* Reviewer: Magal
* Subject: heap-RC1
***************************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "heap.h"

/* #define Get_Arr_Data(arr, x) ((void **)((char *)arr + (x * (sizeof(size_t)))))
 */
enum {LEFT, RIGHT};

size_t GetKidIdxByDirectionIMP(size_t index, int direction);
size_t GetParentIdxIMP(size_t index);
void SwapIMP(void **value1, void **value2);
size_t GetMaxKidIdxIMP(	void *array, 
						size_t left_idx, 
						size_t right_idx, 
						size_t arr_size, 
						heap_cmp_func_t cmp_func, 
						void *cmp_param);
void **Get_Arr_Data(void *arr, int x);

void HeapifyUp(void *array, heap_cmp_func_t cmp_func, size_t index, 
               size_t arr_size, void *cmp_param)
{
	size_t parent_idx = GetParentIdxIMP(index);

	assert(NULL != cmp_func);

	(void)arr_size;
	while(0 != index && 0 < (cmp_func(	*Get_Arr_Data(array, index), 
										*Get_Arr_Data(array, parent_idx), 
										cmp_param)))
	{
		SwapIMP(Get_Arr_Data(array, index), Get_Arr_Data(array, parent_idx));
		index = parent_idx;
		parent_idx = GetParentIdxIMP(index);
	}
}


void HeapifyDown(void *array, heap_cmp_func_t cmp_func, size_t index, 
                 size_t arr_size, void *cmp_param)
{
	size_t max_kid_idx = 0;

	assert(NULL != cmp_func);

	while(GetKidIdxByDirectionIMP(index, LEFT) < arr_size)
	{
		max_kid_idx = GetMaxKidIdxIMP(	array, 
										GetKidIdxByDirectionIMP(index, LEFT),
										GetKidIdxByDirectionIMP(index, RIGHT),
										arr_size,
										cmp_func,
										cmp_param);
		if(0 < cmp_func(*Get_Arr_Data(array, index), 
						*Get_Arr_Data(array, max_kid_idx), 
						cmp_param))
		{
			break;
		}
		SwapIMP(Get_Arr_Data(array, index), Get_Arr_Data(array, max_kid_idx));
		index = max_kid_idx;
	}
}


size_t GetParentIdxIMP(size_t index)
{
	return ((index - 1) / 2);
}

void SwapIMP(void **value1, void **value2)
{
	void *temp = *value1;
	*value1 = *value2;
	*value2 = temp;
}

size_t GetMaxKidIdxIMP(	void *array, 
						size_t left_idx, 
						size_t right_idx, 
						size_t arr_size, 
						heap_cmp_func_t cmp_func, 
						void *cmp_param)
{
	size_t result = 0;

	if(right_idx >= arr_size)
	{
		result = left_idx;
	}
	else
	{
		result = (0 < cmp_func(	*Get_Arr_Data(array, left_idx), 
								*Get_Arr_Data(array, right_idx), 
								cmp_param) 
					? left_idx : right_idx);
	}
	
	return (result);
}

size_t GetKidIdxByDirectionIMP(size_t index, int direction)
{
	size_t kid_idx = index * 2 + 1;

	return (direction == LEFT ? kid_idx : kid_idx + 1);
}

void **Get_Arr_Data(void *arr, int x)
{
	return ((void **)((char *)arr + (x * (sizeof(size_t)))));
}