#include"headers.h"


void execute(char *command)
{
        if(checkpipe(command))
        {
            //printf("Piping detected.\n");
            piping(command);
            return;
        }
        if(checkredir(command))
        {
            redirection(command);
            return;
        }


        char *token;
        char *args[100]={NULL};
        token=strtok(command," \n\t\r");
        int c=0;
        //tokenizing command
        while(token!=NULL)
        {
        	args[c]=token;
        	//printf("%d %s\n",c,args[c]);
        	c++;
        	token=strtok(NULL," \n\t\r");
        }
        args[c]=NULL;
        //cd
        if(strcmp(args[0],"cd")==0)
        {
            /*t=1;*/
        	cd(c,args);
        }

        //pwd
       else if(strcmp(args[0], "pwd")==0)
        {
            /*t=1;*/
        	pwd();
        }

        //echo
        else if(strcmp(args[0], "echo")==0)
        {
            /*t=1;*/
        	echo(c,args);
        }
        //ls
        else if(strcmp(args[0], "ls")==0)
        {
            /*t=1;*/
        	ls(c, args);
        }
        //history
        /*else if(strcmp(args[0], "history")==0)
        {
            t=1;
        	char PTR[5000];
        	sprintf(PTR, "%d", ptr);
        	//printf("%d %s\n", ptr, PTR);
        	if(c>2)
        	{
                t=0;
        		printf("Too many arguments.\n");
        		return;
        	}
        	else if(c==1)
        	{
        		if(ptr>=10)
        		history("10");
        		else
        		history(PTR);
        	}
        	else if(c==2)
        	{
        		if(atoi(args[1])<=ptr)
        			history(args[1]);
        		else
        		{
        			history(PTR);
        		}
        	}
        }*/
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
        	pinfo(c,args);
        }
        //repeat
        else if (strcmp(args[0],"repeat")==0)
        {  /*t=1;*/
            if(c<3)
        	{
               /*t=0;*/
        		printf("insufficient number of arguments.\n");
        		return;
        	}
             int a;
            int r= atoi(args[1]);
            repeat (c-2,&args[2],r);
            /*char command1[100]={'\0'};
            for ( a=2 ; a<c;a++){
                strcat(command1 , args[a]);
                if (a!= (c-1))
                    strcat(command1 , " ");
                //else strcat(command1,"\n");
            }
            //execute(command1);
            //execute(command1);
            for ( a=0 ; a<r;a++){
                execute(command1);
            }*/
        }

        //fg
        else if(strcmp(args[0], "fg")==0)
        {
           /* t=1;*/
            if(c!=2)
            {
                /*t=0;*/
                printf("Error: Incorrect number of arguments\n");
            }
            else
            {
                int n=atoi(args[1]);
                //delete(jobarr[n].pid);
                fg(n);
            }
        }

        //bg
        else if(strcmp(args[0], "bg")==0)
        {   //printf("checking1\n");
            /*t=1;*/
            if(c!=2)
            {
                /*t=0;*/
                printf("Error: Incorrect number of arguments\n");
            }
            else
            {
                int n=atoi(args[1]);
                //printf("%d\nchecking2\n",n);
                bg(n);
            }
        }
         else if(strcmp(args[0], "sig")==0)
        {
           /* t=1;*/
            if(c!=3)
            {
                /*t=0;*/
                printf("Error: Incorrect number of arguments\n");
                return;
            }
            else
            {
                int jobn=atoi(args[1]);
                int signo=atoi(args[2]);
                //delete(jobarr[n].pid);
                sig(jobn,signo);
            }
        }

        else if(strcmp(args[0], "jobs")==0)
        {
           /* t=1;*/
            if(c > 2)
            {
                /*t=0;*/
                printf("Error: Incorrect number of arguments\n");
                return;
            }
            else 
            {
                jobs(args[1]);
                
            }
            
        }
         //quit
        else if(strcmp(args[0], "quit")==0)
        {
            for(int i=0; i<no_of_bgjobs; i++)
            {
                kill(bgp_arr[i].Pid, 9);
            }
            /*t=1;*/
        	exit(0);
        }
        

        else if(strcmp(args[c-1],"&")==0)// background process
        	{    /*t=1;*/
        		args[c-1]=NULL;
               int u= no_of_bgjobs;
	        	int forkReturn=fork();
	        	/*setpgid(0,0);*/
	        	if(forkReturn<0)
                {
                    /*t=0;*/
	        		perror("Fork failed\n");
                    
                }
	        	else if(forkReturn==0)//child
	        	{
	        		//int p=getpid();
                    //bgp_arr[k].is_exitted=0;
	        		int q=execvp(args[0],args);
	        		if(q<0)
                    {
	        			perror("Error");
                        //exit(256);
                        exit(1);
                    }
	        	}
	        	else
	        	{    printf("%d\n", forkReturn); //printing pid of bgprocess
	        		
	        		/*printf("[%d] ID:%d\n", no_of_jobs, forkReturn);*/
	        		bgp_arr[no_of_bgjobs].Pid=forkReturn;
                    
                    strcpy(bgp_arr[no_of_bgjobs].name, "");
	        		strcpy(bgp_arr[no_of_bgjobs].name, args[0]);
                   
                    strcpy(bgp_arr[no_of_bgjobs].fullname, "");
                    for(int j=0; j<c-1; j++)
                    {
                        strcat(bgp_arr[no_of_bgjobs].fullname, args[j]);
                        if(j!=(c-2))
                            strcat(bgp_arr[no_of_bgjobs].fullname, " ");
                    }
                     no_of_bgjobs++;
	        	}
        	}
        else //foreground process
        	{
               /*t=1;*/
        		//args[c]=NULL;
        		int forkReturn=fork();
        		if(forkReturn<0)
                {
                    /*t=0;*/
        			perror("Fork failed");
                }
        		else if(forkReturn>0)//parent
	        	{
                    fgp.Pid=forkReturn;
                    strcpy(fgp.name,args[0]);
                    strcpy(fgp.fullname, "");
                    for(int j=0;j<c; j++)
                    {
                        strcat(fgp.fullname, args[j]);
                        if(j!=(c-1))
                            strcat(fgp.fullname, " ");
                    }
	        		int status;
	        		/*waitpid(forkReturn,&status,WUNTRACED);
                    if(status!=0)
                        t=0;*/
                        //wait(NULL);
                        waitpid(forkReturn,&status,WUNTRACED);
	        	}
	        	else//child
	        	{   /*fgp.Pid=forkReturn;
                    strcpy(fgp.name,args[0]);
                    strcpy(fgp.fullname, "");
                    for(int j=0;j<c; j++)
                    {
                        strcat(fgp.fullname, args[j]);
                        if(j!=(c-1))
                            strcat(fgp.fullname, " ");
                    }*/
	        		int x=execvp(args[0],args);
	        		if(x<0)
	        		{
	        			perror("Error");    
                        exit(1);
                    }
	        	}
        	}
		
	//writetofile();
}

void readinp(){
     
    //getcwd(home,500);
    size_t size=1002;
	size_t bigsize=100000;
    char *command;
    char *inp;
    command=(char *)malloc(size);//lenth of each command is at most 1000.
    inp=(char *)malloc(bigsize);  // inputstr can be 100000 characters long.
    
    
    int gl=getline(&inp,&bigsize,stdin);
        if(gl==-1) //ctrl+D
        {
            for(int i=0; i<no_of_bgjobs; i++)
            {
                kill(bgp_arr[i].Pid, 9);
            }
            /*t=1;*/
        	exit(0);
        }
        else if(gl<0)
        {
        	printf("cannot read input\n");
        	exit(0);
        }
    //tokenize COMMAND
	    char *p=strtok(inp, ";\n");
	    char *commands[100];
	    int number=0;
	    while(p!=NULL)
	    {
	        commands[number++]=p;
	        p=strtok(NULL, ";\n");
	    }
        commands[number]=NULL;

        for(int i=0; i<number; i++)
	    {
		    strcpy(command,commands[i]);
	        strcat(command,"\n");
	        /*strcpy(hist[ptr%20], command);
	        ptr++;*/
	        execute(command);
	        //printf("%d\n", t);
    	}
        free(command);
        free(inp);
    }
void loop (){
     while (1)
    {   fgp.Pid=-1;
        prompt();
        
        readinp();
    }
}
int main(void)
{
   shell_pid = getpid();
    
    signal(SIGTSTP, ctrlz);
    signal(SIGINT, ctrlc);
    signal(SIGCHLD, exitted);
    // signal(SIGTSTP, ctrlz);
    no_of_bgjobs=0;
    getcwd(home_dir, 1000);
     sz = strlen(home_dir);
     strcpy(oldpwd, "~");
    //printf("home = %s\n", home_dir);
   /*t=1;*/
    for(int i=0;i<100;i++){
        bgp_arr[i].num=i+1;
        bgp_arr[i].is_exitted=0;
    }
   loop();
   
    return 0;
}