#include <stdio.h>
#include <stdlib.h>
#include "processDef.h"

void table1(Pr *P, int n, int qt, int st);

int main()
{
	Pr *P;
	int n, qt, st, i;
	printf("Enter the no. of Processes\n");
	scanf("%d", &n);
	P = (Pr*)malloc(n*sizeof(Pr));
	
	for(i=0; i<n; i++)
	{
		printf("Enter Arrival Time & Burst Time of Process no. %d\n", i+1);
		scanf("%d%d", &P[i].at, &P[i].bt);
	}
	
	printf("Enter Time Quantum size\n");
	scanf("%d", &qt);
	printf("Enter Context Switching Time\n");
	scanf("%d", &st);
	table1(P, n, qt, st);
	
	return 0;
}
