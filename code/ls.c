#include "headers.h"
void print_ls(char* D, int a, int l)
{
	/*t=1;*/
	//first we convert ~ to actual address of shell
	char dir[600];
	char temp1[600];
	//char temp2[600];
	//strcpy(temp2,D);//for printing purposes
	if( D[0]=='~')
	{
		//int lentemp=strlen(D);
		for(int i=0;i<strlen(D)-1;i++)
		{
			D[i]=D[i+1];
		}
		D[strlen(D)-1]='\0';
		strcpy(dir,home_dir);
		strcat(dir,D);
	}
	else
	{
		strcpy(dir,D);
	}
	int len2=strlen(home_dir);
	int  len1=strlen(dir);
	for(int u=0;u<h;u++);
	int i,flag=1;
	if(len1>=len2)
	{
		for(i=0;i<len2;i++)
		{
			if(home_dir[i]!=dir[i])
				flag=0;
		}
	}
	if(flag==0 || len1<len2)
	{
		strcpy(temp1,dir);
	}
	else
	{
		int k=1;
		temp1[0]='~';
		for(i=len2;i<len1;i++)
		{
			temp1[k]=dir[i];
			k++;
		}
		temp1[k]='\0';
	}
	DIR *p;
	struct dirent **files;
	int b=scandir(dir, &files, NULL, alphasort);
	if(b<0)
	{
		/*t=0;*/
		perror(dir);
		return;
	}
	else
	{
		if(strcmp(temp1,".")!=0 && strcmp(temp1,home_dir)!=0 && strcmp(temp1,"..")!=0)
			printf("%s:\n", temp1);
		char filepath[700];
		if(l==0 && a>0)
		{
			for(int i=0; i<b; i++)
			{
				struct dirent *f=files[i];
				printf("%s\n", f->d_name);
			}
		}
		else if(l==0 && a==0)
		{
			for(int i=0; i<b; i++)
			{
				struct dirent *f=files[i];
				if(f->d_name[0]=='.' || f->d_name[1]=='.')
					continue;
				printf("%s\n", f->d_name);
			}
		}
		
		else if(l>0 && a>0)
		{
			for(int i=0; i<b; i++)
			{
				struct dirent *f=files[i];
				struct stat fStat;
				strcpy(filepath, dir);
				strcat(filepath, "/");
				strcat(filepath, f->d_name);
				
            	stat(filepath, &fStat);

				printf((S_ISDIR(fStat.st_mode)) ? "d" : "-");
                printf((fStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fStat.st_nlink);
                struct passwd *pwuid=getpwuid(fStat.st_uid);
                printf("  %s", pwuid->pw_name);
				for(int u=0;u<h;u++);
                struct group *grgid=getgrgid(fStat.st_gid);
                printf("  %s", grgid->gr_name);
                printf("  %ld\t", fStat.st_size);

                char TIME[100] = "";
                time_t curr = time(NULL);
                struct tm filetime, currenttime;
                localtime_r(&fStat.st_mtime, &filetime);
                localtime_r(&curr, &currenttime);
				for(int u=0;u<h;u++);
                if (filetime.tm_year != currenttime.tm_year)
                {  strftime(TIME, sizeof(TIME), "%b %e  %Y", &filetime);
                    
                }
                else
                {
                    strftime(TIME, sizeof(TIME), "%b %e %H:%M", &filetime);
                }
                printf(" %s ", TIME);
                printf("%s\n", f->d_name);
			}
		}
		
		
		else if(l>0 && a==0)
		{
			for(int i=0; i<b; i++)
			{
				struct dirent *f=files[i];
				struct stat fStat;
				if(f->d_name[0]=='.')
					continue;
				strcpy(filepath, dir);
				strcat(filepath, "/");
				strcat(filepath, f->d_name);
				
            	stat(filepath, &fStat);

				printf((S_ISDIR(fStat.st_mode)) ? "d" : "-");
                printf((fStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fStat.st_nlink);
                struct passwd *pwuid=getpwuid(fStat.st_uid);
				for(int u=0;u<h;u++);
                printf("  %s", pwuid->pw_name);
                struct group *grgid=getgrgid(fStat.st_gid);
                printf("  %s", grgid->gr_name);
                printf("  %ld\t", fStat.st_size);

                char TIME[100] = "";
                time_t curr = time(NULL);
                struct tm filetime, currenttime;
                localtime_r(&fStat.st_mtime, &filetime);
                localtime_r(&curr, &currenttime);
				for(int u=0;u<h;u++);
                if (filetime.tm_year != currenttime.tm_year)
                { strftime(TIME, sizeof(TIME), "%b %e  %Y", &filetime);
                   
                }
                else
                {
                     strftime(TIME, sizeof(TIME), "%b %e %H:%M", &filetime);
                }
                printf(" %s ", TIME);
                printf("%s\n", f->d_name);
			}

		}
		
	}
}
void ls(int c, char *args[])
{
	/*t=1;*/
	char dir[600];
	getcwd(dir,600);
	if(c==1)
	{
		print_ls(dir,0,0);
	}
	else
	{
		int l=0,a=0,k=0,dirs=0;
		char *dirarr[60]; // can enter max 60 directories as arguments for ls
		for(int i=1;i<c;i++)
		{
			if(args[i][0]=='-')
			{
				
				 if(strcmp(args[i],"-a")==0)
				{
					a++;
				}
				else if(strcmp(args[i],"-l")==0)
				{
					l++;
				}
				else if((strcmp(args[i], "-al")==0) || (strcmp(args[i],"-la")==0)  )
				{
					
					a++;
					l++;
				}
				
				else
				{
					/*t=0;*/
					printf("Invalid flags given as arguments\n");
					exit(0);
				}
			}
			else
			{
				
				dirarr[k]=args[i];
				dirs++;
				k++;
			}
		}

		//printf("l=%d a=%d dirs=%d\n", l, a, dirs);
		if(dirs==0)
		{
			print_ls(dir,a,l);//d is the current directory
		}
		else
		{
			for(int i=0;i<dirs;i++)
			{
				print_ls(dirarr[i],a,l);
				if( i!=(dirs-1)) printf("\n");
			}
		}

	}
}
