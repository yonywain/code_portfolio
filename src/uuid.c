/***************************************
* Author: Yoni Wainsztok
* Date: 11/12/18
* Reviewer: Magal
* Subject: uid-RC1
***************************************/

#include "uuid.h"

uuid_t g_bad_uid = {-1, 0, 0};


uuid_t UUIDCreate()
{
	static size_t counter = 0;
	uuid_t new_id = {0, 0, 0};
	
	new_id.time_val = time(NULL);
	new_id.counter = ++counter;
	new_id.pid = getpid();
	
	if(-1 == new_id.time_val)
	{
		new_id.counter = 0;
		new_id.pid = 0;
	}
	
	return (new_id);
}


int UUIDIsSameUID(uuid_t uuid1, uuid_t uuid2)
{
	return (uuid1.time_val == uuid2.time_val &&
			uuid1.counter == uuid2.counter &&
			uuid1.pid == uuid2.pid);
}


int UUIDIsBadUID(uuid_t uuid)
{
	return (UUIDIsSameUID(g_bad_uid, uuid));
}
