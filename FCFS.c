#include <stdio.h>
#include <stdlib.h>
// For Constructing Process Table
struct Process
{
	int first_bt; // First burst time
	int next_bt;  // Next burst time
	int at;		  // Arrival time
	int ft;		  // Finish time
	int tat;	  // Turnaround time
	int wt;		  // Waiting time
	int temp_bt;  // Temporary variable to store burst times
} P[100];
// For Constructing Gantt Chart
struct Schedule
{
	int pid;	 // Process Number
	int endtime; // Endtime of current slot/schedule
} sch[100];
// sch[1].pid=3
// sch[1].endtime=13
int sch_cnt; // Schedule Counter
int ct;		 // Current time of the System
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
		// 863873750%10+1   [0 to 9]
		// 0+1
		// 1  [1 to 10]

		P[i].next_bt = rand() % 10 + 1;

		P[i].temp_bt = P[i].first_bt;
	}
}

int getProcessByFCFS()
{
	int minp = -1; // Process Number having smaller AT
	int minat = 10000;

	for (i = 0; i < np; i++)
	{
		if (P[i].at <= ct && P[i].temp_bt > 0 && P[i].at < minat)
		{
			minp = i;
			minat = P[i].at;
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
	printf("\nPID\tFBT\tNBT\tAT\tFT\tTAT\tWT\n");
	for (i = 0; i < np; i++)
	{
		printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, P[i].first_bt, P[i].next_bt, P[i].at, P[i].ft, P[i].tat, P[i].wt);
		avgtat = avgtat + P[i].tat;
		avgwt = avgwt + P[i].wt;
	}

	avgtat = avgtat / np;
	avgwt = avgwt / np;

	printf("Average turn arount time:%f", avgtat);
	printf("\nAverage waiting time:%f\n", avgwt);
}

void main()
{
	accept(); // Accept details of all processes
			  // Process First Burst Time of each process using first while(1)
	while (1)
	{
		int x = getProcessByFCFS(); // x=4
		if (x == -1)
			break;

		sch[sch_cnt].pid = x;
		ct += P[x].temp_bt; // ct=6
		P[x].temp_bt = 0;
		sch[sch_cnt].endtime = ct;
		sch_cnt++;
	}

	for (i = 0; i < np; i++)
	{
		P[i].temp_bt = P[i].next_bt;
	}

	while (1)
	{
		int x = getProcessByFCFS();
		if (x == -1)
			break;
		sch[sch_cnt].pid = x;
		ct += P[x].temp_bt;
		P[x].temp_bt = 0;
		P[x].ft = ct;
		sch[sch_cnt].endtime = ct;
		sch_cnt++;
		P[x].tat = P[x].ft - P[x].at;
		// TAT= WT+BT
		// WT = TAT-BT
		// WT = TAT-FBT-NBT-2
		P[x].wt = P[x].tat - P[x].first_bt - P[x].next_bt - 2;
	}
	showGanttChart(); // Display Gantt Chart
	showPT();		  //  Display Process Table
}
