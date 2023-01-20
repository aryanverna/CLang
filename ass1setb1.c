#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void childprocess();
void parentprocess();
void insertionsort();
void bubblesort();
void accept();
void display();
int a[10],n,i;

int main()
{
printf("Enter the limit:");
scanf("%d",&n);
printf("\nEnter the elements:");
accept();
printf("\nUnsorted Elements:\t");
display();
pid_t pid;
pid=fork();
if(pid==0)
{
childprocess();
}
else
{
parentprocess();
}
}
void childprocess()
{
printf("\nIn child process we have to sort elements using insertion sort:");
printf("\nSorted Elements:\t");
insertionsort();
display();
}
void parentprocess()
{
printf("\nIn parent process we have to sort elements using bubble sort:");
printf("\nSorted Elements:\t");
bubblesort();
display();
}
void accept()
{
for(i=0;i<n;i++)
scanf("%d",&a[i]);
}
void display()
{
for(i=0;i<n;i++)
printf("%d\t",a[i]);
}
void insertionsort()
{
int t,j,k;
for(i=1;i<n;i++)
{
t=a[i];
for(j=0;j<i;j++)
{
if(a[i]<a[j])
{
for(k=i;k>j;k--)
a[k]=a[k-1];
a[j]=t;
}
}
}
}
void bubblesort()
{
 int t,j;
 for(i=n-1;i>=1;i--)
 {
for(j=0;j<=i-1;j++)
{
if(a[j]>a[j+1])
{
t=a[j];
a[j]=a[j+1];
a[j+1]=t;
}
}
}
}