#include"headers.h"

void exitted()
{
	int status;
	int p=waitpid(-1, &status, WNOHANG);
    for(int i=0; i<no_of_bgjobs; i++){
        if(bgp_arr[i].Pid==p){
            //if(bgp_arr[i].is_exitted==0)
            bgp_arr[i].is_exitted=1;
            if(WIFEXITED(status))
    			
    				//int exstat=WEXITSTATUS(status);
    			printf("\n%s with pid %d exited normally\n", bgp_arr[i].name, p);
    				
    			//printf("No of jobs: %d\n",no_of_jobs);	
    			
            else  printf("\n%s with pid %d exitted abnormally\n", bgp_arr[i].name, p);
            //loop();
            //signal(SIGCHLD, exitted);
            //return;
        }
    }
	
	/*for(int i=1; i<=no_of_jobs; i++)
	{
		if(jobarr[i].pid==p)
		{
            if(overkill==0)
            {
    			if(WIFEXITED(status))
    			{
    				int exstat=WEXITSTATUS(status);
    				if(exstat==0)
    					fprintf(stderr, "\n%s with pid %d exited normally\n", jobarr[i].name, p);
    				else
    				{
    					fprintf(stderr, "\n%s with pid %d exitted with exit status %d\n", jobarr[i].name, p, exstat);
    				}
    			//printf("No of jobs: %d\n",no_of_jobs);	
    			}
                else
                {
                    fprintf(stderr, "\n%s with pid %d exitted abnormally\n", jobarr[i].name, p);
                }
                delete(p);
                prompt(home);
    			fflush(stdout);
            }
		}
	}
    if(overkill==1)
    {
        delete(-1);
        overkill=0;
    }
    */
}