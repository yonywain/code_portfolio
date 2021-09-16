#ifndef ILRD_STACK_H
#define ILRD_STACK_H


typedef struct stack stack_t;
/*struct stack
{
	void *curr;
	void *head;
	void *end;
	size_t element_size;
};*/ /*put in src file*/


stack_t *StackCreate(size_t size, size_t element_size);
/*

function builds a stack, based on parameters recieved.

Return Value: pointer to the struct "stack", NULL if allocation failure

Parameters  : size = the max number of elements within the stack
     		  element_size = the size of each element of the stack

Proper Input: size > 0, element_size > 0

Errors		: failed allocation

Time Complexity: O(1)

*/


void StackDestroy(stack_t *data_stack);
/*

function frees all allocated elements.

Return Value: -

Parameters  : stack *data_stack = pointer to stack

Proper Input: data_stack != NULL

Errors		: assert for NULL data_stack

Time Complexity: O(1)

*/


int StackPush(stack_t *data_stack, const void *added_element);
/*

recieves a pointer to struct stack and a value, pushes value on top of stack.

Return Value: -

Parameters  : void *added_element = new data to be added to stack
		      stack *data_stack = pointer to struct stack

Proper Input: data_stack != NULL, added_element != NULL

Errors		: 

Time Complexity: O(1)

*/


void StackPop(stack_t *data_stack);
/*

recieves a pointer to struct stack and removes the data stored at the top

Return Value: -

Parameters  : stack *data_stack = pointer to struct stack

Proper Input: data_stack != NULL

Errors		: assert for NULL data_stack

Time Complexity: O(1)

*/


void *StackPeek(stack_t *data_stack);
/*

recieves a pointer to struct stack and returns a pointer to data stored at the top.

Return Value: pointer to data stored at the head of the stack

Parameters  : stack *data_stack = pointer to struct stack

Proper Input: data_stack != NULL

Errors		: assert for NULL data_stack, 

Time Complexity: O(1)

*/


size_t StackSize (const stack_t *data_stack);
/*

recieves a pointer to struct stack and returns the amount of elements stored in the stack

Return Value: number of elements in stack

Parameters  : stack *data_stack = pointer to struct stack

Proper Input: data_stack != NULL

Errors		: ssert for NULL data_stack,

Time Complexity: O(1)

*/
#endif   /* ILRD_STACK_H */
