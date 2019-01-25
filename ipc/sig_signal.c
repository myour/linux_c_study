#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
//#include <stdio.h>

typedef void (*sighandler_t)(int);

void handler(int signo)
{
	printf("--- SIGINT Catched ---\n");

}

int main(int argc, char* argv[])
{
	sighandler_t ret;

	ret = signal(SIGINT,handler);
	if(SIG_ERR == ret)
	{
		perror("signal");
		exit(-1);
	}

	while(1);

	return 0;
}





