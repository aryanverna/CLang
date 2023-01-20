#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
void seperate();
void typeline();

char cmd[89],token1[20],token2[20],token3[20],token4[20],ch;
int n,fp,m,lc;
pid_t pid;


void separate() //seperates command into diff tokens
{
      strcpy(token1,"\0"); //making tokens 1st null
      strcpy(token2,"\0");
      strcpy(token3,"\0");
      strcpy(token4,"\0");
      n=sscanf(cmd,"%s%s%s%s",token1,token2,token3,token4);
}
int main()
{
      while(1)
      {
            printf("\nMyShell $");
            fgets(cmd,80,stdin);
            separate();
            if(strcmp(token1,"exit")==0)
                  exit(0);
            pid=fork(); // creating child process
            if(pid==-1)
                  printf("\n child process not created");
            else if(pid==0) //child process created
            {
                  if(strcmp(token1,"typeline")==0)
                        typeline();
                  else //in built linux command is entered
                  {
                        switch(n)
                        {
                              case 1:
                                    execlp(token1,token1,NULL); //this function executes linux commands
                                    break;
                              case 2:
                                    execlp(token1,token1,token2,NULL);
                                    break;
                              case 3:
                                    execlp(token1,token1,token2,token3,NULL);
                                    break;
                              case 4:
                                    execlp(token1,token1,token2,token3,token4,NULL);
                                    break;
                        }//switch close
                  }//else of linux cmd ended
            }//else if of child process ended
            else
                  wait(NULL);//parrent process waits for child process to complete
      }//while close
      return 0;
}//main
void typeline()
{
      lc=0;
      fp=open(token3,O_RDONLY);
      while(read(fp,&ch,1))
      {
            if(ch=='\n')
                  lc++;
      }
      lc=lc+1;
      lseek(fp,0,SEEK_SET);
      if(strcmp(token2,"a")==0)
      {
            while(read(fp,&ch,1))
            {
                  printf("%c",ch);
            }
      }
      else
      {
            n=atoi(token2);
            if(n>0)
            {
                  while(read(fp,&ch,1))
                  {
                        printf("%c",ch);
                        if(ch=='\n')
                              n--;
                        if(n==0)
                              break;
                  }
            }
            else
            {
                  n=-n;
                  m=lc-n;
                  while(read(fp,&ch,1))
                  {
                        if(ch=='\n')
                              m--;
                        if(m==0)
                              break;
                  }
                  while(read(fp,&ch,1))
                  {
                        printf("%c",ch);
                  }
            }
      }
      close(fp);
}