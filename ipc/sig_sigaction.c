#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



void do_sigact(int signo)
{
	printf("--- SIGQUIT Catched ---\n");
}

int main(int argc, char* argv[])
{
	int ret;
	struct sigaction sact;
	
	sact.sa_handler = do_sigact;
	sact.sa_flags = 0;
	sigemptyset(&sact.sa_mask);
	sigaddset(&sact.sa_mask,SIGQUIT);
	sigaddset(&sact.sa_mask,SIGSTOP);// SIGKILL && SIGSTOP can't be catched!
	sigaddset(&sact.sa_mask,SIGINT);

	ret = sigaction(SIGQUIT,&sact,NULL);
	if(-1 == ret)
	{
		printf("sigaction err.\n");
		exit(-1);
	}

	while(1)
	{
		sleep(1);
	}

	return 0;
}






