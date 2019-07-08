/****************************************
* Author: Yoni Wainsztok
* Date: 13/12/18
* Reviewer: Inbar
* Subject: SCHEDULER-RC1
****************************************/
#include <unistd.h>	/* time	  */
#include <stdlib.h>	/* malloc */
#include <string.h> /* memset */
#include <assert.h> /* assert */

#include "pqheap.h" /* PQueueCreate */
#include "task.h" /* RemoveElement */
#include "schd.h" /* API */

struct scheduler
{
    p_queue_t *p_queue;
    int stop_flag;
};

enum EXIST{NO, YES};
enum RETURN{SUECCESS, FAIL};
enum ERRORS{MEM_ERR = -3, USER_TERMINATED = -2, FUNC_ERR = -1};
enum SWITCH{OFF, ON};

/* complementary functions (matching & finding functions)*/
static int TimeCmp(const void *time_in_schd, 
					const void *time_to_add, 
					void *param);
static int uidFind(const void *schd, 
					const void *uuid_to_find, 
					const void *param);

scheduler_t *SchdCreate()
{
	scheduler_t *new_schd = NULL;
	
	new_schd = (scheduler_t *)malloc(sizeof(scheduler_t));
	if(NULL == new_schd)
	{
		return (NULL);
	}
	
	new_schd->p_queue = PQueueCreate(TimeCmp);
	if(NULL == new_schd->p_queue)
	{
		free(new_schd);
		return (NULL);
	}
	new_schd->stop_flag = OFF;
		
	return (new_schd);	
}


void SchdDestroy(scheduler_t *schd)
{
	assert(NULL != schd);
	
	while(SUECCESS == SchdIsEmpty(schd))
	{
		TaskRemoveElement(PQueuePeek(schd->p_queue));
		PQueueDequeue(schd->p_queue);
	}
	
	PQueueDestroy(schd->p_queue);
	memset(schd, 0, sizeof(scheduler_t)); /*not necessary*/
	free(schd);
}


size_t SchdSize(scheduler_t *schd)
{
	assert(NULL != schd);
	
	return (PQueueSize(schd->p_queue));
}


int SchdIsEmpty(scheduler_t *schd)
{
	assert(NULL != schd);
	
	return (PQueueIsEmpty(schd->p_queue));
}


uuid_t SchdAdd(scheduler_t *schd,
               user_func_t command_func,
               void *param,
               time_t time)
{
	task_t *added_task = NULL;
	
	assert(NULL != schd);
	assert(NULL != command_func);
	assert(FUNC_ERR != time);	
	
	added_task = TaskCreateElement(command_func, param, time);
	if(NULL == added_task || FAIL == PQueueEnqueue(schd->p_queue, added_task))
	{
		TaskRemoveElement(added_task);
		return (g_bad_uid);
	}
	
	return (TaskGetUUID(added_task));
}


int SchdRemove(scheduler_t *schd, uuid_t uuid)
{	
	void *task_to_rm = NULL;
	
	assert(NULL != schd);
	assert(YES != UUIDIsBadUID(uuid));
	
	task_to_rm = PQueueRemove(schd->p_queue, uidFind, &uuid);
	if(NULL == task_to_rm)
	{
		return (FAIL);
	}
	
	TaskRemoveElement(task_to_rm);
	
	return (SUECCESS);
}


int SchdRun(scheduler_t *schd)
{
	int count = 0;
	task_t *current_task = NULL;
	time_t repeat_time = -1;
	time_t sleeper = 0;
	
	assert(NULL != schd);
	
	while(NO == SchdIsEmpty(schd) && ON != schd->stop_flag)
	{
		current_task = PQueuePeek(schd->p_queue);
		PQueueDequeue(schd->p_queue);
		sleeper = difftime(TaskGetTime(current_task), time(NULL));
		
		while(sleeper > 1)
		{
/* 			sleep(TaskGetTime(current_task) - cur_time);
 */			sleeper = sleep(sleeper);
		}
		
		
		
		/* repeat time = output of running task*/
		repeat_time = TaskRunTask(current_task);
		++count;
		switch(repeat_time)
		{
			case(SUECCESS) : /* Case: No errors */
				TaskRemoveElement(current_task);
				break;
				
			case(FUNC_ERR) : /* Case: Task function returned error */
				TaskRemoveElement(current_task);
				return(FUNC_ERR); 
				
			default : /* Case: Task is to be repeated */
				TaskSetTime(current_task, repeat_time);
				if(FAIL == PQueueEnqueue(schd->p_queue, current_task))
				{
					TaskRemoveElement(current_task);
								
					return(MEM_ERR);
				}
				break;
		}
	}
	
	if(ON == schd->stop_flag) /* Case: Running tasks terminated by user */
	{
		schd->stop_flag = OFF;
		return (USER_TERMINATED);
	}
	
	return (count);
}


void SchdStop(scheduler_t *schd)
{
	assert(NULL != schd);
	
	schd->stop_flag = ON;
}

int SchdIsBadUID(uuid_t uid)
{
	return (UUIDIsBadUID(uid));
}

/* complementary functions (matching & finding functions)*/
static int TimeCmp(const void *schd_task, const void *added_task, void *param)
{
	(void)param;
	
	return (TaskGetTime(schd_task) < TaskGetTime(added_task));
}
				
								
static int uidFind(const void *task_in_schd, 
					const void *uuid_to_find, 
					const void *param)
{
	(void)param;
	
	return(UUIDIsSameUID(TaskGetUUID(task_in_schd), *(uuid_t*)uuid_to_find));	
}

