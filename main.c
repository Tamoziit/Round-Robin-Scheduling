#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"
#include "queueDef.h"

/* Prototype defn. */
void table1(Pr *P, int n, int qt, int st);
Pr *sortProcesses(Pr *arr, int n);
void enQueue(QL **front, QL **rear, Pr val);
Pr deQueue(QL **front);
void printQueue(QL *front);
void *scheduler(void* threadargs);

pthread_mutex_t mutex;
int tt, turn, qt, st;
QL *front = NULL, *rear = NULL;

/* Master Thread */
int main()
{
	Pr *P;
	int n, i, status;
	printf("Enter the no. of Processes\n");
	scanf("%d", &n);
	
	P = (Pr*)malloc(n*sizeof(Pr));
	pthread_t threads[n];
	char buffer[5];
	void *retval;
	
	for(i=0; i<n; i++)
	{
		printf("Enter Arrival Time & Burst Time of Process no. %d\n", i+1);
		scanf("%d%d", &P[i].at, &P[i].bt);
		sprintf(buffer, "P%d", i + 1);
        P[i].name = strdup(buffer);
        P[i].remt = P[i].bt;
	}
	
	printf("Enter Time Quantum size\n");
	scanf("%d", &qt);
	printf("Enter Context Switching Time\n");
	scanf("%d", &st);
	
	table1(P, n, qt, st);
	
	printf("Sorting Processes according to Arrival Time...\n");
	P = sortProcesses(P, n);
	printf("Sorted processes:\n");
	for(i=0; i<n; i++)
		printf("%s:(%d) ", P[i].name, P[i].at);
	printf("\n\n");
	
	/* Ready Queue Test */
	enQueue(&front, &rear, P[0]);
	P[0].index = 1;
	enQueue(&front, &rear, P[1]);
	P[1].index = 2;
	printQueue(front);
	//Pr temp = deQueue(&front);
	//printf("%s\n", temp.name);
	printf("from main; Front = %u, Rear = %u\n", front, rear);
	turn = 1;
	tt = P[0].at;
	
	printf("Initially; tt = %d, addr = %u\n", tt, &tt);
	
	for(i=0; i<n; i++)
	{
		printf("From main; turn = %d\n", P[i].index);
		if((status=pthread_create(&threads[i], NULL, &scheduler, (void*)&P[i])))
		{
			printf("Thread creation failed\n");
			exit(0);
		}
	}
	
	for(i=0; i<n; i++)
	{
		pthread_join(threads[i], &retval);
		printf("Thread %d exited with retval = %lu\n", i+1, retval);
		printf("Total time when this thread exits = %d\n", tt);
		sleep(1);
	}
	
	printf("Final Time = %d\n", tt);
	
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
