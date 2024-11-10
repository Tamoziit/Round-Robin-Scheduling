#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"
#include "queueDef.h"

extern pthread_mutex_t mutex;
extern int tt, turn, qt, st;

void enQueue(QL **front, QL **rear, Pr val);
Pr deQueue(QL **front);

void *scheduler(void* threadargs)
{
	Pr *P = (Pr*)threadargs;
	pthread_t sid;
	extern QL *front, *rear;
	Pr temp;
	int timeSlice = 0;
	
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
			
			while(timeSlice < qt && P->remt > 0)
            {
                tt++;
                P->remt--;
                timeSlice++;
                sleep(1);
            }
			
			tt+=st;
			printf("time = %d; %u\n", tt, &tt);
			
			// ready queue update
			if(P->remt > 0)
				enQueue(&front, &rear, *P);
				
			temp = deQueue(&front);
			turn = temp.index;
			
			printf("Next Turn = %d\n", turn);
		pthread_mutex_unlock(&mutex);
		
		timeSlice = 0;
		sleep(1);
	}
	
	if(P->remt == 0)
	{
		pthread_exit((void*)(long)sid);
	}
}
