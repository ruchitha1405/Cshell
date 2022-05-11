#include "headers.h"
void delete(int p)
{
    if(p==-1)
    {
        no_of_bgjobs=0;
        return;
    }
	int flag=0;
	for(int i=0;i<no_of_bgjobs;i++)
	{
		if(bgp_arr[i].Pid==p)
		{
			flag=1;
			for(int j=i; j<no_of_bgjobs-1; j++)
			{
				bgp_arr[j]=bgp_arr[j+1];
				//bgp_arr[j].num --;
			}
			no_of_bgjobs--;
			for(int k=0;k<100;k++){
        		bgp_arr[k].num=k+1;
				if(k>=no_of_bgjobs) bgp_arr[k].is_exitted=0;
    		}
		}
	}
}
void bg(int jobnum)
{
	int flag=0;
	for(int i=1; i<=no_of_bgjobs; i++)
	{
		if(i==jobnum)
		{
			flag=1;
			int k=kill(bgp_arr[jobnum-1].Pid, SIGCONT);
			if(k<0)
			{
				/*t=0;*/
				perror("Error in kill");
			}
		}
	}
	if(flag!=1)
	{
		/*t=0;*/
		printf("Error:no background job corresponding to the given job number exists\n");
	}
	/*t=1;*/
}
void fg(int jobnum)
{
	if(jobnum>no_of_bgjobs)
	{
		/*t=0;*/
		printf("no job with the given job number exists.\n");
		return;
	}
	int p=bgp_arr[jobnum-1].Pid;
	
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(STDIN_FILENO, p);
	fgp.Pid=p;
	strcpy(fgp.name, bgp_arr[jobnum-1].name);
	strcpy(fgp.fullname, bgp_arr[jobnum-1].fullname);
	int k=kill(p, SIGCONT);
	if(k<0)
	{
		/*t=0;*/
		perror("Error in kill");
		return;
	}
	
	delete(p);
	int status;
	waitpid(p, &status, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
	if(WIFSTOPPED(status))
	{
		/*t=0;*/
		
		strcpy(bgp_arr[no_of_bgjobs].name, fgp.name);
		strcpy(bgp_arr[no_of_bgjobs].fullname, fgp.fullname);
         bgp_arr[no_of_bgjobs].Pid=p;
		 no_of_bgjobs++;
       // printf("\n%d\n", p);
	}
	return;
}