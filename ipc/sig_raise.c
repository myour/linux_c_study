#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void do_sig(int signo)
{
	printf("catch SIGUSR1 signal.\n");

}

int main(int argc, char* argv[])
{
	int ret;
	signal(SIGUSR1,do_sig);

	printf("Test raise function .\n");
	while(1)
	{
		sleep(2);
		ret = raise(SIGUSR1);
	}

	return 0;
}

