#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

void separate();
void count();
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
count();
else{
switch (n){

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
if(strcmp(token1,"count")==0)
count(token2,token3);
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

void count(){
lc=0;       wc=0;       cc=0;
fp=open(token3,O_RDONLY);
if(fp==-1){
printf("\n file %s not opened",token3);
}
else {
while (read(fp,&ch,1)){
if (ch!=' '  && ch!='\t' && ch !='\n'){
cc++;
}
else if (ch==' '  || ch=='\t'){
wc++;
}
else {
wc++;
lc++;
}
}
}

if (strcmp(token2,"w")==0)
printf("\n words count is :%d",wc);

if (strcmp(token2,"l")==0)
printf("\n line count is :%d",lc);

if (strcmp(token1,"count")==0)
printf("\n char count is :%d",cc);

close (fp);
}