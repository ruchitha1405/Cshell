
#include "headers.h"

void prompt() 
{
//char *username=getlogin(); //returns pointer to the string of loginname
//char hostname[1000];
int hz=sz;
char cwd[1000];
//char dir[500];
getcwd(cwd,1000);
int cz = strlen(cwd);
char cur_path[1200];
char tilde='~';
memset(cur_path, '\0', 1200);
int k=1;
if(hz==cz){
 cur_path[0]= tilde;
}
else if (cz>hz){
    for (int i = hz; i < cz; i++, k++)
        {
            //printf("hel\n");
            cur_path[k] = cwd[i];
        }

        cur_path[0]= tilde;
}
else{
    for (int i = 0; i < strlen(cwd); i++)
        {
            cur_path[i] = cwd[i];
        }
}
char hostbuf[300];
    int hostname = gethostname(hostbuf, 300);
    if (hostname <0)
    {
        perror("hostname Error");
        exit(0);
    }
    char username[500];
    int loginname = getlogin_r(username, 500);
    if (loginname != 0)
    {
        perror("login Error:");
        exit(0);
    }
    //char *print;
    
     strcat(username, "@");
    strcat(username, hostbuf);
     strcat(username, ":");
    strcat(username, cur_path);
    strcat(username, ">");
    printf("%s", username);

}