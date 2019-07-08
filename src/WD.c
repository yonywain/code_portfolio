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
#include <signal.h>    /* signal */

#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork() */
#include <pthread.h>   /* pthread */

#include "schd.h"      /* Scheduler API */
#include "WD.h"        /* Watch-Dog API */

#define ENV_NAME ("WATCH_DOG")
#define FILE_NAME ("./watch_dog.out")

struct args
{
    pid_t pid;
    char **argv;
    char **env;
    sigset_t set;
};

/* static pid_t CreateWatchDog(char **argv); */
static char **AddGraceToArgList(int argc, char **argv, int grace);
static void *ThreadWDFunc(void *args);

extern void HandleSignal(int sig);
extern int WatchDogIMP(scheduler_t *sched, 
                pid_t *pid, 
                char **argv, 
                char **env, 
                char *program);



extern time_t TaskFunc(void *param);
extern void SetStopFlag();

pthread_t MMI(int argc, char **argv, char **env, int grace)
{
    struct sigaction act = {0};
    pthread_t thread_id = {0};
    struct args *thread_args = NULL;
    char **new_argv = AddGraceToArgList(argc, argv, grace);
   /*  char **new_argv = argv; */
    sigset_t set;
    extern char **environ;

    thread_args = (struct args *)malloc(sizeof(struct args));
    act.sa_handler = HandleSignal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    thread_args->argv = new_argv;
    thread_args->env = env;

    
    if (NULL == getenv(ENV_NAME))
    {
        /* thread_args.pid = CreateWatchDog(new_argv); */
        printf("******WD NOT exist*******\n");
        thread_args->pid = fork();
        if (0 == thread_args->pid)
        {
            setenv(ENV_NAME, "yoni", 1);
            execve(FILE_NAME, new_argv, environ);
        }
    }
    else
    {

        thread_args->pid = getppid();
    }
    
    sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, &set, NULL);

    thread_args->set = set;

    pthread_create(&thread_id, NULL, ThreadWDFunc, thread_args);

    return thread_id;
}

static char **AddGraceToArgList(int argc, char **argv, int grace)
{
    int i = 0;
    char **new_argv = (char **)malloc((argc + 3) * sizeof(char *));
    char *buffer = (char *)malloc(2);

    for (i = 0; i < argc; ++i)
    {
        new_argv[i] = argv[i];
    }
    sprintf(buffer, "%d", grace);
    new_argv[i] = buffer;
    ++i;
    new_argv[i] = NULL;

    return new_argv;
}

/* static pid_t CreateWatchDog(char **argv)
{
    pid_t child_pid = {0};
    char pid_str[20] = {0};

    child_pid = fork();
    if (0 == child_pid)
    {
        sprintf(pid_str, "%d", child_pid);
        setenv(ENV_NAME, pid_str, 0);
        execvp(FILE_NAME, argv);
    }

    return child_pid;
} */

static void *ThreadWDFunc(void *args)
{
    struct args *thread_args = (struct args *)args;
    scheduler_t *sched = SchdCreate();
    int sig = 0;

    while (1)
    {
        printf("In Thread func waiting\n");
        sigwait(&thread_args->set, &sig);
	    pthread_sigmask(SIG_UNBLOCK, &thread_args->set, NULL);

        printf("in thread func after waiting\n");

        if(1 == WatchDogIMP(sched, &thread_args->pid, thread_args->argv, thread_args->env, FILE_NAME))
        {
            break;
        }
    }

    return NULL;
}

void DNR(pthread_t thread_id)
{
    SetStopFlag();

    pthread_join(thread_id, NULL);
}