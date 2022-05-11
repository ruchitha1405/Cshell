
#include "headers.h"

void echo(int c, char *args[])
{
	for(int k=1;k<c;k++)
    {
        printf("%s ",args[k]);
    }
   printf("\n");
}