#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "processDef.h"
#include "queueDef.h"

extern pthread_mutex_t mutex;
extern pthread_cond_t turn_cond;
extern int tt, turn, qt, st, switchCount, totalRemt;
extern QL *front, *rear;

typedef struct {
    Pr *currentProcess;
    Pr *processArray;
    int numProcesses;
} ThreadArgs;

void enQueue(QL **front, QL **rear, Pr val);
Pr deQueue(QL **front);

void *queueMaintainer(Pr* P, int n)
{
    int i;
    
    for (i = 0; i < n; i++)
    {
        if (tt == P[i].at && P[i].enqueued == 0 && P[i].remt > 0)
        {
            enQueue(&front, &rear, P[i]);
            P[i].enqueued = 1; // Marking as enqueued
        }
    }
}

void advanceTimeDeadlockAvoider(Pr* processArray, int n) {
    for (int i = 0; i < n; i++) {
        if (processArray[i].cpu == 0 && processArray[i].at > tt) {
        	switchCount += (processArray[i].at - tt);
            tt = processArray[i].at;
            turn = processArray[i].index;
            pthread_cond_broadcast(&turn_cond);
            break;
        }
    }
}

void *scheduler(void* threadargs)
{
	ThreadArgs *args = (ThreadArgs*)threadargs;
    Pr *P = args->currentProcess;
    Pr *allProcesses = args->processArray;
    int n = args->numProcesses;
    
	pthread_t sid;
	Pr temp;
	int timeSlice = 0, i;
	struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0; 
	
	while (1) {
        pthread_mutex_lock(&mutex);

        while (turn != P->index) {
        	pthread_cond_wait(&turn_cond, &mutex);
        }

        if (P->remt > 0) {
            sid = pthread_self();
            P->cpu = 1;
            //printf("Turn = %d\n", turn);

            while (timeSlice < qt && P->remt > 0) {
            	if(P->remt == P->bt)
            		P->start = tt;
                tt++;
                printf(" %s ", P->name);
                P->remt--;
                totalRemt--;
                timeSlice++;
                queueMaintainer(allProcesses, n);
                nanosleep(&ts, NULL);
            }

            if (P->remt > 0) {
                enQueue(&front, &rear, *P);
            }
            if(P->remt == 0)
            	P->ct = tt;

            for(i=1; i<=st; i++)
            {
            	tt++;
            	switchCount++;
            	queueMaintainer(allProcesses, n);
            }
            if(totalRemt > 0)
            	printf(" X ");

            Pr temp = deQueue(&front);
            if (temp.index != -1) {
                turn = temp.index;
            } else {
                advanceTimeDeadlockAvoider(allProcesses, n);
            }
			//printf("Next turn = %d\n", turn);
			pthread_cond_broadcast(&turn_cond);
        }

        pthread_mutex_unlock(&mutex);
        timeSlice = 0;

        if (P->remt == 0) {
            free(args);
            pthread_exit((void*)(long)sid);
        }
    }
}
