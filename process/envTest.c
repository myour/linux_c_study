#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[])
{
	int ret;
	const char* NAME = "MMP";
	char * str = NULL;

	str = getenv(NAME);
	if(NULL == str)
		printf("Get env %s=%s .\n",NAME,str);
	
	ret = setenv(NAME,"love u.",1);
	if(-1 == ret)
		printf("setenv %s fail.",NAME);
	else
		printf("After setenv %s=%s .\n",NAME,getenv(NAME));

	ret = unsetenv(NAME);
	if(-1 == ret)
		printf("setenv %s fail.",NAME);
	else
		printf("After  unsetenv %s=%s .\n",NAME,getenv(NAME));

	return 0;
}


