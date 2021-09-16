/* RC7 */
#ifndef ILRD_SCHD_H
#define ILRD_SCHD_H

#include "uuid.h"

typedef  time_t (*user_func_t)(void *param);
typedef struct scheduler scheduler_t;


/*
struct scheduler
{
    p_queue_t *p_queue;
    int stop_flag;
};
*/


/*
* Create a new scheduler
* Return Value: a pointer to the new scheduler, NULL on alloc failure
* Parameters  : -
* Input       : -
*/
scheduler_t *SchdCreate();


/*
* Destroys the given scheduler
* Return Value: -
* Parameters  : schd: the scheduler
* Input       : schd cannot be NULL
*/
void SchdDestroy(scheduler_t *schd);


/*
* Counts the number of tasks in the scheduler
* Return Value: number of tasks
* Parameters  : schd: the scheduler
* Input       : schd cannot be NULL
*/
size_t SchdSize(scheduler_t *schd);


/*
* Checks whether the scheduler is empty or not
* Return Value: 1 if empty, 0 otherwise
* Parameters  : schd: the scheduler
* Input       : schd cannot be NULL
*/
int SchdIsEmpty(scheduler_t *schd);


/*
* Adds a new task to the scheduler
* Return Value: returns the uuid of the new task, bad_uuid in case of failure
* Parameters  : schd: the scheduler
                command_func: pointer to a user function
                param: user data
                time: when to perform the task
* Input       : schd cannot be NULL
                command_func cannot be NULL
* Errors      : time == -1
*/
uuid_t SchdAdd(scheduler_t *schd,
               user_func_t command_func,
               void *param,
               time_t time);


/*
* Removes a task from the scheduler
* Return Value: 0 if task was removed, 1 otherwise (uid not found)
* Parameters  : schd: the scheduler
                uid: the task id
* Input       : schd cannot be NULL
                
*/
int SchdRemove(scheduler_t *schd, uuid_t uid);


/*
* runs the scheduler
* Return Value: returns the number of tasks performed, -1 if user function returned error code, -2 if stopped by user intervention, -3 on failled attempt to re-insert task to scheduale. Schedualer will sleep between tasks and wake up 10 seconds before next task.
* Parameters  : schd: the scheduler
* Input       : schd cannot be NULL
*/
int SchdRun(scheduler_t *schd);


/*
* Stops the scheduler
* Return Value: -
* Parameters  : schd: the scheduler
* Input       : schd cannot be NULL
*/
void SchdStop(scheduler_t *schd);


/*
* Checks whether the given uuid is a bad uuid
* Return Value: 1 if bad uuid, 0 otherwise
* Parameters  : uid: a uuid
* Input       : -
*/
int SchdIsBadUID(uuid_t uid);



#endif
