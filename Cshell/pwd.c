
#include "headers.h"

void pwd()
{
	char d[600];
	getcwd(d,600);
	printf("%s\n",d);
}