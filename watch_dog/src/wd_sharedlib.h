/****************************************
* Author: Yoni Wainsztok
* Date: 18/02/19
* Reviewer: Dafna
* Subject: Watch_Dog-RC1
****************************************/
#ifndef ILRD_WD_SHARED_LIB_H
#define ILRD_WD_SHARED_LIB_H

#include "schd.h"

/* Signal Handler
* Parameters  : sig - signal to handle
*/
void HandleSignal(int sig);

/* Watch-dog implementation for keeping process alive.
* Return Value: - 0 - Continue to keep program alive
                  1 - shut down watchdog application
* Parameters  : sched - scheduler which contains repeated life check task
                pid - process ID to check its life status
                argv - contains running command and grace time
                env - contains enviroment variable to check if watchdog is up 
                      already
                program - executable program name to lunch
*/
int WatchDogIMP(scheduler_t *sched, 
                pid_t *pid, 
                char **argv, 
                char **env, 
                char *program);

/* Task function used by scheduler which contains the life check itself.
* Return Value: - time for the next lunch of this task. if 0, task is finished
                  with no next lunch time.
* Parameters  : param - pid of the process to call to.
*/

time_t TaskFunc(void *param);

/* Set stop flag to "stop" for exiting watch-dog application (intriged by DNR 
function)*/
void SetStopFlag();

#endif /* ILRD_WD_SHARED_LIB_H */