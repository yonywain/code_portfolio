/****************************************
* Author: Yoni Wainsztok
* Date: 18/02/19
* Reviewer: Dafna
* Subject: Watch_Dog-RC1
****************************************/
#define _POSIX_C_SOURCE (199309L)
#include <stdio.h>     /* printf */
#include <stdlib.h>    /* exit() */
#include <signal.h>    /* signal */

#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork() */
#include <pthread.h>   /* pthread */

#include "schd.h"      /* Scheduler API */

/* static int g_grace = 5; */

extern void HandleSignal(int sig);
extern int WatchDogIMP(scheduler_t *sched, 
                pid_t *pid, 
                char **argv, 
                char **env, 
                char *program);
extern time_t TaskFunc(void *param);

int main(int argc, char **argv, char **env)
{
    struct sigaction act = {0};
    pid_t pid = getppid();
    scheduler_t *sched = SchdCreate();
    char *file_name = argv[0];

    write(1, "------------START WATCH_DOG-----------\n", 40);
    act.sa_flags = SA_SIGINFO;
    act.sa_handler = HandleSignal;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    argv[argc - 1] = NULL;

    while (1)
    {
        printf("WD : pid inside watch dog WHILE = %dl\n", pid);
        if (1 == WatchDogIMP(sched, &pid, argv, env, file_name))
        {
            write(1, "WATCH dOG DEAD!!!\n", 19);
            break;
        }
    }

    return (0);
}
