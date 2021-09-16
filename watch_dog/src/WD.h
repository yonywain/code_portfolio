/****************************************
* Author: Yoni Wainsztok
* Date: 18/02/19
* Reviewer: Dafna
* Subject: Watch_Dog-RC1
****************************************/
#ifndef ILRD_WD_H
#define ILRD_WD_H

/* Start watch-dog operation (MMI - Make Me Immortal).
* Return Value: - Thread ID to join later in DNR function
* Parameters  : argc - amount of elements in argv.
                argv - command line trigger
                env - environment variables
                grace - quantity of life checks before relunching program 
                (in case where program is dead).
*/
pthread_t MMI(int argc, char **argv, char **env, int grace);

/* Finish watch-dog coverage.
* Parameters  : thread_id - Thread ID to join.
*/
void DNR(pthread_t thread_id);

#endif  /* ILRD_WD_H */