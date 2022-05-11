#include"headers.h"

void cd(int c, char *args[])
{
		/*t=1;*/
		char dir[500];
       	char temp[500];
		   if(c<2)
       	{	printf("insufficient arguments.\n");
      		return;
       	}
       	else if(c>2)
       	{
       		/*t=0;*/
      		printf("Too many arguments.\n");
       		return;
       	}
       
        strcpy(temp,args[1]);
		if(temp[0]=='-')
		{   if (strcmp(oldpwd,"~")==0) printf("%s\n", home_dir);
        else  printf("%s\n", oldpwd);
			char **argz=(char **)malloc(4*sizeof(char *));
			argz[0]="cd";
			argz[1]=oldpwd;			
			cd(2, argz);
			return;
		}
 		else if(temp[0]=='~')
		{
			//int lentemp=strlen(temp);
			for(int i=0;i<strlen(temp)-1;i++)
			{
				temp[i]=temp[i+1];
			}
			temp[strlen(temp)-1]='\0';
			strcpy(dir,home_dir);
			strcat(dir,temp);
		}
		
		else
		{
			strcpy(dir,temp);
		}
		for(int u=0;u<h;u++);
		char temp1[500];
		char Dir[500];
		getcwd(temp1,500);
		int len2=strlen(home_dir);
		int len1=strlen(temp1);
		for(int u=0;u<h;u++);
		int i,flag=1;
		if(len1>=len2)
		{
			for(i=0;i<len2;i++)
			{
				if(home_dir[i]!=temp1[i])
					flag=0;
			}
		}
		if(len1<len2 || flag==0 )
		{
			strcpy(Dir,temp1);
		}
		else
		{
			int a=1;
			Dir[0]='~';
			for(i=len2;i<len1;i++)
			{
				Dir[a]=temp1[i];
				a++;
			}
			Dir[a]='\0';
		}
		for(int u=0;u<h;u++);
		strcpy(oldpwd, Dir);
		int chd=chdir(dir);
		if(chd<0)
		{
			/*t=0;*/
			perror("Error");
		}
}