#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processDef.h"
#include "queueDef.h"

/* Prototype defn. */
void table1(Pr *P, int n, int qt, int st);
Pr *sortProcesses(Pr *arr, int n);
void enQueue(QL **front, QL **rear, Pr val);
Pr deQueue(QL **front);
void printQueue(QL *front);


/* Master Thread */
int main()
{
	Pr *P;
	int n, qt, st, i, tt=0;
	printf("Enter the no. of Processes\n");
	scanf("%d", &n);
	P = (Pr*)malloc(n*sizeof(Pr));
	char buffer[5];
	QL *front = NULL, *rear = NULL;
	
	for(i=0; i<n; i++)
	{
		printf("Enter Arrival Time & Burst Time of Process no. %d\n", i+1);
		scanf("%d%d", &P[i].at, &P[i].bt);
		sprintf(buffer, "P%d", i + 1);
        P[i].name = strdup(buffer);
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
	/*enQueue(&front, &rear, P[0]);
	enQueue(&front, &rear, P[1]);
	printQueue(front);
	Pr temp = deQueue(&front);
	printf("%s\n", temp.name);*/
	
	return 0;
}
