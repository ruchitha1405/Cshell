#include"headers.h"


void repeat(int k, char *args[],int r){
    int c=k;
//cd
        if(strcmp(args[0],"cd")==0)
        {
            /*t=1;*/
            for(int l=0;l<r;l++) cd(c,args);
        }
//pwd
       else if(strcmp(args[0], "pwd")==0)
        {
            /*t=1;*/
        	for(int l=0;l<r;l++)pwd();
        }
//echo
        else if(strcmp(args[0], "echo")==0)
        {
            /*t=1;*/
        	for(int l=0;l<r;l++)echo(c,args);
        }
 //ls
        else if(strcmp(args[0], "ls")==0)
        {
            /*t=1;*/
        	for(int l=0;l<r;l++)ls(c, args);
        }
//pinfo
        else if(strcmp(args[0],"pinfo")==0)
        {
            /*t=1;*/
        	if(c>2)
        	{
               /*t=0;*/
        		printf("Too many arguments.\n");
        		return;
        	}
        	for(int l=0;l<r;l++)pinfo(c,args);
        }

else //foreground process
        	{
               /*t=1;*/
        		//args[c]=NULL;
            for(int l=0;l<r;l++){
        		int forkReturn=fork();
        		if(forkReturn<0)
                {
                    /*t=0;*/
        			perror("Fork failed");
                }
        		else if(forkReturn>0)//parent
	        	{
                   /* foreg.pid=forkReturn;
                    strcpy(foreg.name,args[0]);
                    strcpy(foreg.fullname, "\0");
                    for(int j=0;j<c; j++)
                    {
                        strcat(foreg.fullname, args[j]);
                        if(j!=(c-1))
                            strcat(foreg.fullname, " ");
                    }*/
	        		/*int status;
	        		waitpid(forkReturn,&status,WUNTRACED);
                    if(status!=0)
                        t=0;*/
                        wait(NULL);
	        	}
	        	else//child
	        	{
	        		int x=execvp(args[0],args);
	        		if(x<0)
	        		{
	        			perror("Error");    
                        exit(1);
                    }
	        	}
            }
        	}
		

}