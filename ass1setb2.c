#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int pid=fork();
    if(pid>0)
    {
        printf("I am Parent Process\n");
        printf("Process I'd is %d\n",getpid());
    }
    else if(pid==0)
    {
        printf("I am Child Process\n");
        printf("Child Process I'd is %d \n",getpid());
        printf("Parent's Process I'd is %d \n",getppid());

        sleep(5);

        printf("\n I am Child Process\n");
        printf("Child I'd is %d \n",getpid());
        printf("Parent Process I'd is %d \n",getppid());
    }
    else
    {
        printf("\nFailed to create child process\n");
    }
    return 0;
}