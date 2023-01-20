#include <stdio.h>
#include <stdlib.h>
struct Process
{
	int first_bt, next_bt, at, ft, tat, wt, temp_bt, priority;
} P[100];
struct Schedule
{
	int pid, endtime;
} sch[100];

int sch_cnt; // Schedule Counter
int ct;		 // Current time
int np;		 // Number of processes
int i;

void accept()
{
	printf("Enter the number of processes:");
	scanf("%d", &np);

	for (i = 0; i < np; i++)
	{
		printf("Enter the arrival time:");
		scanf("%d", &P[i].at);

		printf("Enter the first burst time:");
		scanf("%d", &P[i].first_bt);

		printf("Enter the priority:");
		scanf("%d", &P[i].priority);

		P[i].next_bt = rand() % 10 + 1;

		P[i].temp_bt = P[i].first_bt;
	}
}

int getProcessByPriority()
{
	int minp = -1;
	int minat = 32768;

	for (i = 0; i < np; i++)
	{
		if (P[i].at <= ct && P[i].temp_bt > 0 && P[i].priority < minat)
		{
			minp = i;
			minat = P[i].priority;
		}
	}
	return minp;
}

void showGanttChart()
{
	for (i = 0; i < sch_cnt * 5; i++)
		printf("-");
	printf("\n|");

	for (i = 0; i < sch_cnt; i++)
		printf(" P%d |", sch[i].pid);
	printf("\n");

	for (i = 0; i < sch_cnt * 5; i++)
		printf("-");
	printf("\n0");

	for (i = 0; i < sch_cnt; i++)
		printf("%5d", sch[i].endtime);
}

void showPT()
{
	float avgtat = 0, avgwt = 0;
	printf("\n");
	printf("\nPID\tFBT\tNBT\tAT\tFT\tTAT\tWT\tPriority\n");
	for (i = 0; i < np; i++)
	{
		printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, P[i].first_bt, P[i].next_bt, P[i].at, P[i].ft, P[i].tat, P[i].wt, P[i].priority);
		avgtat += P[i].tat;
		avgwt += P[i].wt;
	}

	avgtat = avgtat / np;
	avgwt = avgwt / np;

	printf("Average turn arount time:%f", avgtat);
	printf("\nAverage waiting time:%f\n", avgwt);
}

void main()
{
	accept();
	// Scheduling First Burst Time of each Process
	while (1)
	{
		int x = getProcessByPriority();
		if (x == -1) // if no process will return -1
			break;

		sch[sch_cnt].pid = x;
		ct += P[x].temp_bt;
		P[x].temp_bt = 0;
		sch[sch_cnt].endtime = ct;
		sch_cnt++;
	}

	for (i = 0; i < np; i++)
	{
		P[i].temp_bt = P[i].next_bt;
	}
	// Scheduling Next Burst Time of each Process
	while (1)
	{
		int x = getProcessByPriority();
		if (x == -1)
			break;

		sch[sch_cnt].pid = x;
		ct += P[x].temp_bt;
		P[x].temp_bt = 0;
		P[x].ft = ct;
		sch[sch_cnt].endtime = ct;
		sch_cnt++;
		P[x].tat = P[x].ft - P[x].at;
		P[x].wt = P[x].tat - P[x].first_bt - P[x].next_bt - 2;
	}

	showGanttChart();
	showPT();
}
