#include "headers.h"


void pinfo(int k, char *args[])
{
	
	int pid;
	if(k==1)
		pid=getpid();
	else if(k==2)
		pid=atoi(args[1]);
	else
	{
		
		printf("Too many arguments\n");
		return;
	}
    char buffer[1200] = "";
    char stats[10000]="";
	
	sprintf(stats, "/proc/%d/stat", pid);

	int fd=open(stats, O_RDONLY);
	if(fd<0)
	{
		
        perror("Error opening stats file,may be because the process has already terminated.");
		return;
	}
	else
	{
        read(fd, buffer, sizeof(buffer));
    char *list[800];
    char *temp = strtok(buffer, " \r\t\n");
    int j = 0;
    while (temp != NULL)
    {
        list[j++] = temp;
        temp = strtok(NULL, " \r\t\n");
    }
    printf("pid -- %s\n", list[0]);

    printf("Process Status -- %s", list[2]); //process status
    if (strcmp(list[2],"S")==0 || strcmp(list[2],"R")==0)
    {
        int flag1=0;
    for(int m=0; m<no_of_bgjobs;m++){
        if (bgp_arr[m].Pid==pid) flag1=1; //process is bgp 
    }
    if (flag1==0)printf("+");
    }
    printf("\n");
    printf("memory -- %s\n", list[23]);        //memory amount

   
	close(fd);

		char exec[10000];
	
	sprintf(exec, "/proc/%d/exe", pid);

		char path[10000];
		int x=readlink(exec, path, 10000);
		if(x<0)
		{
			
			perror("Error reading process in exec file");
			return;
		}
		else
		{
			path[x]='\0';
			char *s=strstr(path, home_dir); //check for substring in home_dir in path
            char tilda[strlen(path)];
            int k=1;
			if(s)
			{   for (int i = sz; i < strlen(path); i++, k++)
                        {
           
                            tilda[k] = path[i];
                        }

                    tilda[0] = '~';
                    tilda[k]='\0';
				
				printf("Executable path -- %s\n", tilda);
			}
			else
			{
				printf("Executable path -- %s\n", path);
			}
		}
	}

}


