#include "headers.h"


// A comparator function used by qsort
int compare(const void * a, const void * b)
{  
    return ( strcmp((*((struct job*)a)).fullname , (*((struct job*)b)).fullname)) ;
}

void jobs(char* flag)
{	
	//printf("testing1\n");
	int k=no_of_bgjobs;
    job * temp=(job *) malloc(no_of_bgjobs*(sizeof(struct job)));
	//printf("testing2\n");
		//job temp[k];
		for(int i=0;i<no_of_bgjobs;i++){
			temp[i]=bgp_arr[i];
		}
		qsort(temp,k,sizeof(struct job),compare);
	/*t=1;*/
	for(int i=0; i<no_of_bgjobs; i++)
	{	if(bgp_arr[temp[i].num-1].is_exitted==0)
		{//char stats[10000];
        char status;
        char* stats=(char *) malloc(10000*(sizeof(char)));
		//printf("testing3\n");
		sprintf(stats, "/proc/%d/stat",temp[i].Pid);
		FILE *fd;
		fd=fopen(stats, "r");
		if(fd<0)
		{
			/*t=0;*/
			perror("Error in opening stat file");
			return;
		}
		else
		{	//printf("testing4\n");
			fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
            //printf("testing5\n");
			fclose(fd);
		}

        if(flag==NULL)
		{if(status=='T')
			printf("[%d] Stoppped %s [%d]\n", temp[i].num, temp[i].fullname, temp[i].Pid);
		 if (status=='R' || status=='S')
			printf("[%d] Running %s [%d]\n", temp[i].num, temp[i].fullname, temp[i].Pid);
			//printf("testing6\n");
        }
        else if(strcmp(flag,"-s")==0){
            if(status=='T')
			printf("[%d] Stoppped %s [%d]\n", temp[i].num, temp[i].fullname, temp[i].Pid);
        }
        else if(strcmp(flag,"-r")==0){
            if (status=='R' || status=='S')
			printf("[%d] Running %s [%d]\n", temp[i].num, temp[i].fullname, temp[i].Pid);
        }
		//printf("testing7\n");
        free(stats);
		}
    }
    free(temp);
}