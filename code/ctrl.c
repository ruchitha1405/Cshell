
#include "headers.h"


void ctrlc(int signum)
{
	int p=getpid();
	if(p<0)
	{
		perror("Error");
	}
	if(p!=shell_pid)
	{
		return;
	}
	if(fgp.Pid!=-1)
	{
		/*t=0;*/
		int k=kill(fgp.Pid, SIGINT);
		if(k<0)
		{
			/*t=1;*/
			perror("Error in kill");
		}
	}
	signal(SIGINT, ctrlc);
}

void ctrlz(int signum)
{
	int p=getpid();
	if(p<0)
	{
		perror("Error");
		return;
	}
	if(p!=shell_pid)
	{
		return;
	}
	if(fgp.Pid!=-1)
	{
		//int in=kill(fgp.Pid, SIGTTIN);//not needed
		int stp=kill(fgp.Pid, SIGTSTP);
		//if(in<0 || stp<0)
        if(stp<0)
		{
			perror("Error in kill");
		}
		else
		{	
			/*t=0;*/
			
	        bgp_arr[no_of_bgjobs].Pid=fgp.Pid;
	        strcpy(bgp_arr[no_of_bgjobs].name, fgp.name);
	        strcpy(bgp_arr[no_of_bgjobs].fullname, fgp.fullname);
            no_of_bgjobs++;
	        //printf("\n%d\n", fgp.Pid);
	        return;
		}
	}
	signal(SIGTSTP, ctrlz);	
}