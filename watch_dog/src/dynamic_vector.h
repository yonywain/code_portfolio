#ifndef ILRD_DYNAMIC_VECTOR_H
#define ILRD_DYNAMIC_VECTOR_H

typedef struct dynamic_vector vector_t;

/*
* Create a dynamic vector based on parameters
* Return Value: pointer to managment struct, NULL if allocation failed
* Parameters  : number_of_elements: the dynamic vector size
*		element_size:  the size of each element of the dynamic vector 
* Proper Input: size > 0 && element_size > 0
* Errors: 
* Time Complexity: O(1)
*/
vector_t *DVectorCreate(size_t number_of_elements, size_t element_size);

/*
* Frees all allocated elements.
* Return Value: -
* Parameters  : vector : pointer to dynamic vector
* Proper Input: -
* Errors: - 
* Time Complexity: O(1)
*/
void DVectorDestroy(vector_t *vector);

/*
* Get element address in the index
* Return Value: pointer to the address
* Parameters  : vector: pointer to dynamic vector
*		index: index of the element
* Proper Input: index >=0 && NULL != vector
* Errors: index > size - Undifined behavior
* Notes: the address migth be changed if using push/pop/reserve 
* Time Complexity: O(1)
*/
void *DVectorGetItemAddress(vector_t *vector, size_t index);

/*
* Push element to the next empty place in dynamic vector
* Return Value: 0 - succeded, 1 - failed
* Parameters  : vector: pointer to dynamic vector
*		element: item that we want to push
* Proper Input: element != NULL && vector != NULL
* Errors: 
* Note: 
* Time Complexity: O(n)
*/
int DVectorPush(vector_t *vector, const void *element);

/*
* Pop the last element from dynamic vector
* Return Value: 0 - succeded, 1 - failed reallocat memory
* Parameters  : vector: pointer to dynamic vector
* Proper Input: vector != NULL
* Errors: size = 0 and you do pop it is undefined behavior
* Time Complexity: O(n)
*/
int DVectorPop(vector_t *vector);

/*
* Resized the size of dynamic vector
* Return Value: 1 - succeded, 0 - failed memory allocation
* Parameters  : vector: pointer to dynamic vector
*		fix_size: new size of dynamic vector
* Proper Input: element != NULL  fix_size >= 0
* Note: if fix_size < size it will be always reserved to size
* Errors: realloc failed - push the element and return failed to realloc memory
* Time Complexity: O(n)
*/
int DVectorReserve(vector_t *vector, size_t fix_size);

/*
* Returns the size of the vector
* Return Value: the size of the vector
* Parameters  : vector: pointer to the vector
* Proper Input: vector != NULL
* Errors: -
* Time Complexity: O(1)
*/
size_t DVectorSize(const vector_t *vector);

/*
* Returns the capacity of the vector
* Return Value: the remain capacity of the vector
* Parameters  : vector: pointer to the vector
* Proper Input: vector != NULL
* Errors: -
* Time Complexity: O(1)
*/
size_t DVectorCapacity(const vector_t *vector);

#endif /* ILRD_DYNAMIC_VECTOR_H */
