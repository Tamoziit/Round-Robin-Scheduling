#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"

extern pthread_mutex_t mutex;

void *scheduler(void* threadargs)
{
	Pr *P = (Pr*)threadargs;
	pthread_t sid;
	
	pthread_mutex_lock(&mutex);
	sid = pthread_self();
	printf("%s: AT = %d, BT = %d, ID = %lu\n", P->name, P->at, P->bt, sid);
	pthread_mutex_unlock(&mutex);
	
	pthread_exit((void*)(long)sid);
}
