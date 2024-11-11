#include <stdlib.h>
#include <stdio.h>
#include "processDef.h"

void table2(Pr *P, int n, int qt, int st, int switchCount, int tt)
{
	int i;
	float tatAvg = 0.0, wtAvg = 0.0, rtAvg = 0.0;
	float cpuUtil = 0.0, idle = 0.0;
	printf("\nProcess\tArrival Time\tBurst Time\t1st CPU\tResponse Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
	for(i=0; i<n; i++)
	{
		P[i].rt = P[i].start - P[i].at;
		P[i].tat = P[i].ct - P[i].at;
		P[i].wt = P[i].tat - P[i].bt;
		tatAvg += P[i].tat;
		wtAvg += P[i].wt;
		rtAvg += P[i].rt;
		printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", P[i].name, P[i].at, P[i].bt, P[i].start, P[i].rt, P[i].ct, P[i].tat, P[i].wt);
	}
	
	tatAvg = tatAvg/(float)n;
	wtAvg = wtAvg/(float)n;
	rtAvg = rtAvg/(float)n;
	int burst = (tt - st)-(switchCount - st);
	cpuUtil = (burst/(float)(tt-st))*100.0;
	idle = ((switchCount - st)/(float)(tt-st))*100.0;
	
	printf("\nAvg. Turnaround Time = %f\n", tatAvg);
	printf("Avg. Waiting Time = %f\n", wtAvg);
	printf("Avg. Response Time = %f\n", rtAvg);
	printf("CPU Utilization = %f%\n", cpuUtil);
	printf("Idle Time = %f%\n", idle);
}
