#include <stdio.h>   /* printf */
#include <stdlib.h>  /* exit() */
#include <pthread.h> /* pthread */
#include <signal.h>  /* signal */
#include <unistd.h>  /* sleep */

#include "WD.h"

int main(int argc, char **argv, char **env)
{
    pthread_t thread_id = {0};

    printf("------------START PROCESS-----------\n");
    thread_id = MMI(argc, argv, env, 5);

    sleep(20);

    DNR(thread_id);
    sleep(10);

    printf("Ending Process - %lu\n", thread_id);


    return 0;
}