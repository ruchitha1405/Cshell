#include "headers.h"

void sig(int jobno,int signo)
{
   /* if (nargs != 3)
    {
        printf("Error in no.of args in sig\n");
        return;
    }
    int jobnum = atoi(command[1]);
    int signo = atoi(command[2]);*/

   if (jobno <= no_of_bgjobs && jobno > 0)
    {
       if(bgp_arr[jobno-1].is_exitted==0){ 
           

       int k= kill(bgp_arr[jobno-1].Pid,signo);
       if (k<0) {
           perror("Error in kill");
           return;
       }
       }
    }  
    else
    {
        printf("No such process found \n");
        return;
    }
}