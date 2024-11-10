#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"
#include "queueDef.h"

extern pthread_mutex_t mutex2;
extern int tt, n;
extern QL *front, *rear;
int enQueued = 0;

void enQueue(QL **front, QL **rear, Pr val);
Pr deQueue(QL **front);

void *queueCreator(void* threadargs)
{
    Pr *P = (Pr*)threadargs;
    int i;
    pthread_t sid = pthread_self();
    
    while (enQueued < n)
    {
        for (i = 0; i < n; i++)
        {
            if (tt == P[i].at && P[i].enqueued == 0)
            {
            	printf("Enqueuing: %s at time %d\n", P[i].name, tt);
                pthread_mutex_lock(&mutex2);
                    enQueue(&front, &rear, P[i]);
                    enQueued++;
                    P[i].enqueued = 1; // Marking as enqueued
                pthread_mutex_unlock(&mutex2);
            }
        }
        sleep(1);
    }
    
    pthread_exit((void*)(long)sid);
}
