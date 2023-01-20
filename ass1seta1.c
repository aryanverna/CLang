#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<stdlib.h>
void ChildProcess();
void ParentProcess();
int main()
{
    pid_t pid;
    pid = fork();
    if(pid==0)
    {
        printf("Process I'd of child process is %d\n",pid);
        ChildProcess();
    }
    else
    {
        printf("Process I'd of parent process is %d\n",pid);
        ParentProcess();
    }
    return 0;
}
void ChildProcess()
{
    printf("I am child process\n");
}
void ParentProcess()
{
    printf("I am parent process\n");
}