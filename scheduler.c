#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"
#include "queueDef.h"

extern pthread_mutex_t mutex;
extern int tt, turn;

void *scheduler(void* threadargs)
{
	Pr *P = (Pr*)threadargs;
	pthread_t sid;
	extern QL *front, *rear;
	
	printf("Turn = %d\n", turn);
	
	while(turn != P->index);
	
	pthread_mutex_lock(&mutex);
	sid = pthread_self();
	printf("%s: AT = %d, BT = %d, ID = %lu\n", P->name, P->at, P->bt, sid);
	tt++;
	printf("%d; %u\n", tt, &tt);
	if(turn == 2)
		turn = 1;
	else
		turn++;
	sleep(2);
	//printf("Front = %u, Rear = %u\n", front, rear);
	pthread_mutex_unlock(&mutex);
	
	if(P->bt == 0)
		pthread_exit((void*)(long)sid);
	else
		scheduler(P);
}
