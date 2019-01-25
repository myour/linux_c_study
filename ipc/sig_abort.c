#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void do_sig(int signo)
{
	printf("catch SIGABRT signal.\n");

}

int main(int argc, char* argv[])
{
	//int ret;
	signal(SIGABRT,do_sig);

	printf("Test abort function .\n");
	while(1)
	{
		sleep(2);
		//ret = raise(SIGABRT);
		abort();
	}

	return 0;
}

