#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "processDef.h"
#include "queueDef.h"

/* Prototype defn. */
void table1(Pr *P, int n, int qt, int st);
void table2(Pr *P, int n, int qt, int st, int switchCount, int tt);
Pr *sortProcesses(Pr *arr, int n);
void enQueue(QL **front, QL **rear, Pr val);
Pr deQueue(QL **front);
void *scheduler(void *threadargs);
//void *scheduler2(void *threadargs);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t turn_cond = PTHREAD_COND_INITIALIZER;

int tt, turn, qt, st, n, switchCount = 0, totalRemt = 0;
QL *front = NULL, *rear = NULL;

typedef struct
{
	Pr *currentProcess;
	Pr *processArray;
	int numProcesses;
} ThreadArgs;

/* Master Thread */
int main()
{
	Pr *P;
	int i, status;
	printf("Enter the no. of Processes\n");
	scanf("%d", &n);

	P = (Pr *)malloc(n * sizeof(Pr));
	pthread_t threads[n];
	char buffer[5];
	void *retval;

	for (i = 0; i < n; i++)
	{
		printf("Enter Arrival Time & Burst Time of Process no. %d\n", i + 1);
		scanf("%d%d", &P[i].at, &P[i].bt);
		sprintf(buffer, "P%d", i + 1);
		strcpy(P[i].name, buffer);
		P[i].remt = P[i].bt;
		totalRemt += P[i].remt;
		P[i].index = i + 1;
	}

	printf("Enter Time Quantum size\n");
	scanf("%d", &qt);
	printf("Enter Context Switching Time\n");
	scanf("%d", &st);

	table1(P, n, qt, st);

	printf("Sorting Processes according to Arrival Time...\n");
	P = sortProcesses(P, n);
	printf("Sorted processes:\n");
	table1(P, n, qt, st);
	printf("\n");

	/* Round Robin Init */
	turn = P[0].index;
	for(i=1; i<n; i++) {
		if(P[i].at == P[0].at)
			enQueue(&front, &rear, P[i]); //handling same initial AT for multiple processes
	}

	tt = P[0].at;
	printf("Initially; tt = %d\n\nEvaluating Gantt Chart...\n\n", tt);

	if (tt != 0)
	{
		for (i = 0; i < tt; i++)
		{
			printf(" X ");
			switchCount++;
		}
	}

	for (i = 0; i < n; i++)
	{
		ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs));
		args->currentProcess = &P[i];
		args->processArray = P;
		args->numProcesses = n;

		if ((status = pthread_create(&threads[i], NULL, &scheduler, (void *)args)))
		{
			printf("Thread creation failed\n");
			exit(0);
		}
	}

	for (i = 0; i < n; i++)
	{
		pthread_join(threads[i], &retval);
		//sleep(1);
	}

	printf("\n");
	table2(P, n, qt, st, switchCount, tt);
	printf("Final Time = %d\n", tt - st);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&turn_cond);
	free(P);
	pthread_exit(NULL);
}
