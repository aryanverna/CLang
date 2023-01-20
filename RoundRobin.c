#include<stdio.h>
#include<stdlib.h>
struct Process
{
	int first_bt,next_bt,at,ft,tat,wt,temp_bt;
}P[100];

struct Schedule
{
	int pid,endtime;
}sch[100];

int sch_cnt;    //Schedule Counter
int ct;        //Current time
int np;       //Number of processes
int i;
int tq;     //time quantum/time slice


void accept()
{
	printf("Enter the number of processes:");
	scanf("%d",&np);

	for(i=0;i<np;i++)
	{
		printf("Enter the arrival time:");
		scanf("%d",&P[i].at);

		printf("Enter the first burst time:");
		scanf("%d",&P[i].first_bt);
		
		P[i].next_bt=rand()%10+1;
		P[i].temp_bt=P[i].first_bt;
		
	}
        printf("Enter the time quantum:");
        scanf("%d",&tq);
}

int getProcessByRoundrobin()
{
	int minp=-1;
	int minat=32768;

	for(i=0;i<np;i++)
	{
		if(P[i].at<=ct && P[i].temp_bt>0 && P[i].at<minat)
		{
			minp=i;
			minat=P[i].at;
		}
	}
        return minp;
}


void showGanttChart()
{
	for(i=0;i<sch_cnt*5;i++)
	printf("-");
	printf("\n|");
	
        for(i=0;i<sch_cnt;i++)
	printf(" P%d |",sch[i].pid);
	printf("\n");
	
        for(i=0;i<sch_cnt*5;i++)
	printf("-");
	printf("\n0");

	for(i=0;i<sch_cnt;i++)
	printf("%5d",sch[i].endtime);
}

void showPT()
{  
	float avgtat=0,avgwt=0;
        printf("\n");
	printf("\nPID\tFBT\tNBT\tAT\tFT\tTAT\tWT\n");
	for(i=0;i<np;i++)
	{
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,P[i].first_bt,P[i].next_bt,P[i].at,P[i].ft,P[i].tat,P[i].wt);
		avgtat+=P[i].tat;
		avgwt+=P[i].wt;
	}

	avgtat=avgtat/np;
	avgwt=avgwt/np;

	printf("Average turn arount time:%f",avgtat);
	printf("\nAverage waiting time:%f\n",avgwt);
}

void main()
{
	accept();
    // To schedule first burst time of each process
	while(1)
	{
		int x=getProcessByRoundrobin();
		if(x==-1)              //if no process will return -1
			break;

		sch[sch_cnt].pid=x;
		if(P[x].temp_bt<tq)
        //suppose P[x].temp_bt=3    and    tq=4
		{
			ct=ct+P[x].temp_bt;
			P[x].temp_bt=0;
		}
		else //  suppose P[x].temp_bt=6    and    tq=4
		{
			ct=ct+tq;
			P[x].temp_bt=P[x].temp_bt-tq;
		}
		sch[sch_cnt].endtime=ct;
		sch_cnt++;
	}

	for(i=0;i<np;i++)
	{
		P[i].temp_bt=P[i].next_bt;         
	}
    // To schedule Next Burst Time of each process
	while(1)
	{
		int x=getProcessByRoundrobin();
		if(x==-1)
			break;

		sch[sch_cnt].pid=x;
		if(P[x].temp_bt<tq)
		{
			ct=ct+P[x].temp_bt;
			P[x].temp_bt=0;
		}
		else
		{
			ct=ct+tq;
			P[x].temp_bt=P[x].temp_bt-tq;
		}
		sch[sch_cnt].endtime=ct;
		sch_cnt++;

		if(P[x].temp_bt==0)
		{
			  P[x].ft=ct;                  
			  P[x].tat=P[x].ft-P[x].at;
		      P[x].wt=P[x].tat-P[x].first_bt-P[x].next_bt-2;
        }
	}

	showGanttChart();
	showPT();
} 
