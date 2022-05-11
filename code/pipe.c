#include "headers.h"



int checkpipe(char *command)
{
	char *p=strstr(command, "|");
	if(p!=NULL)
		return 1;
	else
		return 0;
}

void piping(char *command)
{
	//tokenising pipe elements
	char **args=malloc(256*sizeof(char *));
   // memset(args, NULL, 256*sizeof(char*));
	char *p=strtok(command, "|");
	int ptr=0;
	while(p!=NULL)
	{
		args[ptr]=p;
		p=strtok(NULL, "|");
		ptr++;
	}
    //dup2(1, STDOUT_FILENO);
    //dup2(0, STDIN_FILENO);
	int pipefd[2];
	int fd=0, forkReturn;
	for(int i=0; args[i]!=NULL; i++)
	{
		
		if(pipe(pipefd)<0)
		{
			perror("Error");
			return;
		}
        
  
		forkReturn=fork();
		if(forkReturn<0)
		{
			perror("forkReturn");
		}
		else if(forkReturn==0)
		{
			int d1=dup2(fd, STDIN_FILENO);
			if(d1<0)
			{
				perror("d1");
				return;
			}
			if(args[i+1]!=NULL)
			{
				int d2=dup2(pipefd[1], STDOUT_FILENO);
				if(d2<0)
				{
					perror("d2");
					return;
				}
			}
            //else dup2(1, STDOUT_FILENO);
			int c1=close(pipefd[0]);
			if(c1<0)
			{
				perror("c1");
				return;
			}
			execute(args[i]);
			exit(2);
		}
		else
		{
			wait(NULL);
			int c2=close(pipefd[1]);
			if(c2<0)
			{
				perror("c2");
				return;
			}
			fd=pipefd[0];
		}
	}
   // dup2(0, STDIN_FILENO);
    //dup2(1, STDOUT_FILENO);
}
