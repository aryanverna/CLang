#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
void seperate();
void search();
char cmd[80],token1[20],token2[20],token3[20],token4[20],ch;
int fp,n;
pid_t pid;
void seperate()//seperates command into different tokens
{
      strcpy(token1,"\0");
      strcpy(token2,"\0");
      strcpy(token3,"\0");
      strcpy(token4,"\0");
      n=sscanf(cmd,"%s%s%s%s",token1,token2,token3,token4);
}
int main()
{
      while(1)
      {
            printf("\n Myshell $");
            fgets(cmd,80,stdin);
            seperate();
            if(strcmp(token1,"exit")==0)
                  exit(0);
            pid = fork();
            if(pid == -1)
                  printf("\n child process not created");
            else if(pid==0)
            {
                  if(strcmp(token1,"search")==0)
                        search();
                  else
                  {
                        switch(n)
                        {
                              case 1:
                                    execlp(token1,token3,NULL);
                                    break;
                              case 2:
                                    execlp(token1,token1,token2,NULL);
                                    break;
                              case 3:
                                    execlp(token1,token1,token2,token3,NULL);
                              case 4:
                                    execlp(token1,token2,token2,token3,token4,NULL);
                                    break;
                        }
                  }
            }
            else
                  wait(NULL);
      }
      return 0;
}
void search()
{
      char s[80];
      int i=0,cnt=0,lc=1;
      fp=open(token3,O_RDONLY);
      if(fp==-1)
      {
            printf("\nFile not found");
            return;
      }
      while(read(fp,&ch,1)) //file found
      {
            //printf("%c",ch);
            if(ch=='\n')
                  lc++;
            if(ch=='\n' || ch=='\t' || ch==' ')
            {
                  s[i]='\0';
                  i=0;
                  if(strstr(s,token4))
                  {
                        if(strcmp(token2,"f")==0)
                        {
                              printf("pattern \"%s\" found in \"%s\" at line no:%d\n",token4,s,lc);
                              break;
                        }//fend

                        if(strcmp(token2,"c")==0)
                        {
                              cnt++;
                        }//c end
                         if(strcmp(token2,"a")==0)
                         {
                               printf("pattern \"%s\" found in \"%s\" at line no:%d\n",token4,s,lc);
                                           }//a end
                  }
            }
      
            else
            {
                  s[i]=ch;
                  i++;
            }
      }
      if(strcmp(token2,"c")==0)
            printf("\nTotal occurances of given pattern=%d",cnt);
}