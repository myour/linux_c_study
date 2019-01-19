#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


extern char** environ;  // must add

int main(int argc, char* argv[])
{
#if 1
	int i;

	for(i=0;environ[i];i++)
	{
		printf("%s\n",environ[i]);
	}
#else
	while(*environ != NULL)
	{
		printf("%s\n",*environ);
		environ++;
	}
#endif

	return 0;
}
