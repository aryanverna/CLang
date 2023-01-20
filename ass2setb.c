#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
void separate();
void list();

DIR *dp;
struct dirent *de;

char cmd[80], token1[20],token2[20],token3[20],token4[20],ch;
int n,fp,wc,cc,lc;
pid_t pid;
void separate(){
strcpy(token1,"\0");
strcpy(token2,"\0");
strcpy(token3,"\0");
strcpy(token4,"\0");
n=sscanf(cmd,"%s%s%s%s", token1,token2,token3,token4);
}
int main(){
while(1){
printf("\n Myshell $");
fgets(cmd,80,stdin);
separate();
if (strcmp(token1,"exit")==0)
exit (0);
pid=fork();
if (pid ==-1)
printf("child process is not created");
else if(pid ==0){
if (strcmp(token1,"count")==0)
list();
else{
switch (n)
{
case 1:
if(fork()==0)
execlp(token1,token1,NULL);
wait(0);
break;
case 2:
if(fork()==0)
execlp(token1,token1,token2,NULL);
wait(0);
break;
case 3:
if(strcmp(token1,"list")==0)
list(token2,token3);
else
if(fork()==0)
execlp(token1,token1,token2,token3,NULL);
wait(0);
break;
case 4:
if(fork()==0)
execlp(token1,token1,token2,token3,token4,NULL);
wait(0);
break;
default:
printf("\nInvalid");
}
}
}
else
wait(NULL);
}
return 0;
}

void list()
{
int cnt=0;
dp=opendir(token3);
if(dp==NULL)
{
printf("\n%s directory not found",token3);
}
else
{
{
if(strcmp(token2,"f")==0)
{
while(1)
{
de=readdir(dp);
if(de==NULL)
break;
printf("\n file name: %s",de->d_name);
}
}
if(strcmp(token2,"n")==0)
{
while(1)
{
de=readdir(dp);
if(de==NULL)
break;
cnt++;
}
printf("\n total files: %d",cnt);
}
if(strcmp(token2,"i")==0)
{
while(1)
{
de=readdir(dp);
if(de==NULL)
break;
printf("\n file name: %s",de->d_name);
printf("\t inode no: %ld",de->d_ino);
}
}
}
}
}