#include <stdlib.h>	/* malloc */
#include <string.h> /* memset */
#include <assert.h> /* assert */

#include "task.h"


struct task 
{
	task_func_t command;
	void *param;
	time_t time;
	uuid_t uuid;
};

/*
* Creates a new task
* Return Value: returns a pointer to the created task, 
                NULL if allocation failure
* Parameters  : 
* Input       : none of the inputs can be NULL
*/
task_t *TaskCreateElement(task_func_t command, 
                          void *param,
                          time_t time)
{
	task_t *task = NULL;
	
	assert(NULL != command);
	assert(-1 != time);
	
	task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		return (NULL);
	}
	task->command = command;
	task->param = param;
	task->time = time;
	task->uuid = UUIDCreate();
	
	return (task);
}

/*
* Destroys a task
* Return Value: 
* Parameters  : task: a task element
* Input       : schd and task cannot be NULL
*/
void TaskRemoveElement(task_t *task)
{
	assert(NULL != task);
	
	memset(task, 0, sizeof(task_t));
	free(task);
}


/*
* Returns the scheduled time of the task 
* Return Value: returns the scheduled time in seconds since the epoch
* Parameters  : task: a task element
* Input       : task cannot be NULL
*/
time_t TaskGetTime(const task_t *task)
{
	assert(NULL != task);
	
	return (task->time);
}

/*
* Returns the uuid of the given task 
* Return Value: returns the uuid
* Parameters  : task: a task element
* Input       : task cannot be NULL
*/
uuid_t TaskGetUUID(const task_t *task)
{
	assert(NULL != task);
	
	return (task->uuid);
}

/*
* Performs the task 
* Return Value: -
* Parameters  : task: a task element
* Input       : task cannot be NULL
*/
time_t TaskRunTask(task_t *task)
{
	assert(NULL != task);
	
	return (task->command(task->param));
}

/*
* sets the time in the task
* Return Value: -
* Parameters  : task: a task element
* Input       : task cannot be NULL
*/
void TaskSetTime(task_t *task, time_t time_to_run)
{
	assert(NULL != task);
	assert(-1 != time_to_run);
	
	task->time = time_to_run;
}
