#include "processDef.h"
#include <stdlib.h>
#include <stdio.h>

void table1(Pr *P, int n, int qt, int st)
{
	int i;
	printf("\nProcess\tArrival Time\tBurst Time\n");
	for(i=0; i<n; i++)
	{
		printf("P%d\t%d\t\t%d\n", i+1, P[i].at, P[i].bt);
	}
	printf("\nTime Quantum = %d\n", qt);
	printf("Context Switching = %d\n\n", st);
}