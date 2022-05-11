#include "headers.h"


int checkredir(char *command)
{
    char *out=strstr(command, ">");
    char *in=strstr(command, "<");
    char *outa=strstr(command, ">>");

    //Note: if outa is not NULL, out will also be not NULL

    if(in!=NULL && out!=NULL)
    {
    	if(outa!=NULL)// < and >>
    		return 2;
    	else
    		return 1;// < and >
    }
    else if(in!=NULL)// <
    	return 3;
    else if(outa!=NULL)// >>
    	return 4;
    else if(out!=NULL)// >
    	return 5;
    else// nothing
    	return 0;

}

int is_fileexists(char* path) 
{
    struct stat f;
    if(stat(path, &f) == 0 && !S_ISDIR(f.st_mode))
        return 1;
    else
    	return 0;
}

void redirection(char *command)
{
	/*t=1;*/
	int status;
	int stdout=dup(STDOUT_FILENO);
	int stdin=dup(STDIN_FILENO);
	int in, out;
	char *output[2];
	char *input[2];
	int res=checkredir(command);
	//printf("res=%d\n", res);	
	if(res==1)
	{
		in=1;
		out=1;
	}
	else if(res==2)
	{
		in=1;
		out=2;
	}
	else if(res==3)
	{
		in=1;
		out=0;
	}
	else if(res==4)
	{
		in=0;
		out=2;
	}
	else if(res==5)
	{
		in=0;
		out=1;
	}
	char *outfile;
	output[0]=&command[0];
	if(out==1)
	{
		output[0]=strtok(command, ">");
		output[1]=strtok(NULL, ">");
		outfile=strtok(output[1], " \r\t\n");
	}
	else if(out==2)
	{
		output[0]=strtok(command, ">>");
		output[1]=strtok(NULL, ">>");
		outfile=strtok(output[1], " \r\t\n");
	}
	char *infile;
	input[0]=output[0];
	if(in==1)
	{
		input[0]=strtok(input[0], "<");
		input[1]=strtok(NULL, "<");
		infile=strtok(input[1], " \r\t\n");
	}
	char **args=(char**)malloc(sizeof(char*)*300);
    //memset(args,NULL,sizeof(char*)*300);
	
	//printf("Yahan tak hogaya\n");
	if(in==1)
	{
		if(input[1]==NULL)
		{
			/*t=0;*/
			printf("No file name specified for input.\n");
			return;
		}
		else if(is_fileexists(infile)==0)
		{
			/*t=0;*/
			printf("File not found.\n");
			return;
		}
	}
     int ptr=0;
	input[0]=strtok(input[0], " \n\r\t");
    while(input[0]!=NULL)
    {
        args[ptr]=(char *)malloc(sizeof(char)*strlen(input[0])+12);
        strcpy(args[ptr], input[0]);
        input[0]=strtok(NULL, " \n\t\r");
        ptr++;
    }
    args[ptr] = NULL;

	if(out==1 || out==2)
	{
		if(outfile==NULL)
		{
			t=0;
			printf("No file name specified for output.\n");
			return;
		}
	}

	int pid=fork();
	if(pid<0)
	{
		t=0;
		perror("Error in forking");
		return;
	}
	else if(pid==0)
	{
		if(in==1)
		{
			int infd=open(infile, O_RDONLY);
			if(infd<0)
			{
				t=0;
				perror("Error in Input");
				return;
			}
			else
			{
				int d1=dup2(infd, STDIN_FILENO);
				if(d1<0)
				{
					t=0;
					perror("Error");
					return;
				}
				close(infd);
			}
		}
		if(out==1 || out==2)
		{
	//		printf("Yahan tak bhi hogaya\n");
			int outfd;
			if(out==2)
			{
				outfd=open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else
			{
				outfd=open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
	//		printf("Yahaan tak bhi hogaya\n");
			if(outfd<0)
			{
				t=0;
				perror("Error ");
				return;
			}
			else
			{
	//			printf("Yahaaan tak bhi hogaya\n");
				int d2=dup2(outfd, STDOUT_FILENO);
				if(d2<0)
				{
					t=0;
					perror("Error");
					return;
				}
				close(outfd);
			}
		}
		int exfd=execvp(args[0], args);
		if(exfd<0)
		{
			t=0;
			perror("Error");
			exit(1);
		}
        
        /*int d3=dup2(stdin, 0);
        if(d3<0)
		{
			t=0;
			perror("Error");
			return;
		}
        close(stdin);
        int d4=dup2(stdout, 1);
        if(d4<0)
		{
			t=0;
			perror("Error");
			return;
		}
        close(stdout);*/
	}
	else
	{wait(NULL);
    /*int d3=dup2(stdin, 0);
        if(d3<0)
		{
			t=0;
			perror("Error");
			return;
		}
        close(stdin);
        int d4=dup2(stdout, 1);
        if(d4<0)
		{
			t=0;
			perror("Error");
			return;
		}
        close(stdout);*/
		/*while(wait(&status)!=pid);
		if(status!=0)
			t=0;*/
	}

}