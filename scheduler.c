#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"
#include "queueDef.h"

extern pthread_mutex_t mutex;
extern int tt, turn, qt, st;

void *scheduler(void* threadargs)
{
	Pr *P = (Pr*)threadargs;
	pthread_t sid;
	extern QL *front, *rear;
	
	while(turn != P->index)
	{
		printf("Index = %d waiting...\n", P->index);
		sleep(1);
	}
	
	while(P->remt > 0)
	{
		pthread_mutex_lock(&mutex);
			printf("My Turn = %d\n", turn);
			sid = pthread_self();
			printf("%s: AT = %d, BT = %d, Rem T = %d, ID = %lu\n", P->name, P->at, P->bt, P->remt, sid);
			
			if(P->remt < qt)
			{
				tt+=P->remt;
				P->remt = 0;
			}
			else
			{
				P->remt-=qt;
				tt+=qt;
			}
			
			tt+=st;
			printf("%d; %u\n", tt, &tt);
			if(turn == 2)
				turn = 1;
			else
				turn++;
			printf("Next Turn = %d\n", turn);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	
	if(P->remt == 0)
		pthread_exit((void*)(long)sid);
}
