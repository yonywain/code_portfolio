/****************************************
* Author: Yoni Wainsztok
* Date: 18/02/19
* Reviewer: Dafna
* Subject: Watch_Dog-RC1
****************************************/
#define _POSIX_C_SOURCE (199309L)
#define _BSD_SOURCE
#define _POSIX_SOURCE
#include <stdio.h>     /* printf */
#include <stdlib.h>    /* exit() */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork() */
#include <signal.h>    /* signal */
#include <pthread.h>   /* pthread */

#include "wd_sharedlib.h"

enum state
{
    RUN = 0,
    READY_TO_STOP,
    STOP
};

static int g_counter = 3;
static int g_grace = 3;
enum state g_stop_flag = RUN;

void HandleSignal(int sig)
{
    switch (sig)
    {
    case SIGUSR1:
        printf("My pid in HANDLER is = %dl\n", getpid());
        g_counter = g_grace;
        break;
    case SIGUSR2:
        g_stop_flag = STOP;
        write(1, "SIGUSER2 - FLAG STOP\n", 22);
        break;
    }
}

int WatchDogIMP(scheduler_t *sched, pid_t *pid, char **argv, char **env, char *program)
{
    write(1, "In watch dog IMP\n", 18);
    SchdAdd(sched, TaskFunc, pid, time(NULL) + 1); /* check failure*/
    SchdRun(sched);

    printf("SHARED_FUNC : pid input = %dl \n", *pid);
    printf("SHARED_FUNC : program = %s\n", program);

    if (RUN == g_stop_flag)
    {
        *pid = fork();

        if (0 == *pid)
        {

            execve(program, argv, env);
        }
        printf("SHARED_FUNC : CHILD_PID = %dl \n", *pid);
        g_counter = g_grace;
    }
    else
    {
        SchdDestroy(sched);
        write(1, "SCHED DESTROY\n", 15);
        return 1;
    }
    
    return 0;
}

time_t TaskFunc(void *param)
{
    pid_t pid = *(pid_t *)param;

    printf("In TaskFunc counter = %d\n", g_counter);
    printf("In TaskFunc calling pid = %dl\n", pid);
    if (RUN != g_stop_flag)
    {
        kill(pid, SIGUSR2);
    }

    kill(pid, SIGUSR1);
    --g_counter;
    if (0 != g_counter && STOP != g_stop_flag)
    {
        return time(NULL) + 5;
    }

    return 0;
}

void SetStopFlag()
{
    g_stop_flag = READY_TO_STOP;
    write(1, "Set FLAG to READY TO STOP\n", 27);
}
