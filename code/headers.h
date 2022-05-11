#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>


//#include "prototypes.h"
#include "cd.h"
#include "prompt.h"
#include "echo.h"
#include "repeat.h"
#include "ls.h"
#include "pinfo.h"
#define h 10000
#include "pwd.h"
//#include "history.h"
//#include "bg.h"
#include "bg_exitstatus.h"
#include "pipe.h"
#include "redirection.h"
#include "jobs.h"
#include "fbg.h"
#include "ctrl.h"
#include "sig.h"
//#define CMD_DELIMITER ";\n"
///#define ARG_DELIMITER " \t\r\n\a"
void execute(char *command);
void loop ();
/*int t;*/
char home_dir[1000];
char oldpwd[1000];
char hist[20][1000];
//int ptr=0;
//void readinp();
typedef struct job{
	int num;
	char name[200];
	char fullname[1000];
	pid_t Pid;
	int is_exitted;
}job;
job bgp_arr[100];//bg jpbs array
//struct job jobarr[10000];
int no_of_bgjobs;//num of background processes

int sz; //size of home_dir

int shell_pid;
struct job fgp;
int t;

//struct job foreg;