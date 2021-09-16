#ifndef ILRD_uuid_H
#define ILRD_uuid_H

#include <time.h>		/* time_t */
#include <unistd.h>		/* pid_t */
#include <sys/types.h>	/* system calls */


typedef struct uuid
{
    time_t time_val;
    size_t counter;
    pid_t pid;
}uuid_t;

extern uuid_t g_bad_uid;

/*g_bad_uuid->time_val = NULL;
g_bad_uuid->counter = 0;
g_bad_uuid->pid = NULL;
*/


/*
* creates a UUID struct
* Return Value: a UUID
* Parameters  : - 
* Input       : - 
* Time Complexity: O(1)
*/
uuid_t UUIDCreate();


/*
* Checks whether two UUID's are the same
* Return Value: 1 if they are the same, 0 otherwise
* Parameters  : uuid1: a uuid
              : uuid2: a uuid
* Input       : -
* Time Complexity: O(1)
*/
int UUIDIsSameUID(uuid_t uuid1, uuid_t uuid2);


/*
* Checks whether the given uuid is a bad uid
* Return Value: 1 if the given uuid is bad, 0 otherwise
* Parameters  : uuid: a uuid
* Input       : -
* Time Complexity: O(1)
*/
int UUIDIsBadUID(uuid_t uuid);

#endif   /* ILRD_uuid_H */
