#include <stdlib.h>
#include <stdio.h>
#include "processDef.h"

void table1(Pr *P, int n, int qt, int st)
{
	int i;
	printf("\nProcess\tArrival Time\tBurst Time\tIndex\n");
	for (i = 0; i < n; i++)
	{
		printf("%s\t%d\t\t%d\t\t%d\n", P[i].name, P[i].at, P[i].bt, P[i].index);
	}
	printf("\nTime Quantum = %d\n", qt);
	printf("Context Switching = %d\n\n", st);
}
