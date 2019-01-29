#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

typedef unsigned int uint;

#define ERR_EXIT(msg)\
do{\
	perror(msg);\
	exit(-1);\
}while(0);


void do_sigalarm(int signo)
{
	printf("------ %d signal catched! -------\n",signo);
}

uint my_sleep(uint sec)
{
	int ret,retval;
	struct sigaction sact,oldsact;
	
	sact.sa_handler = do_sigalarm;
	sact.sa_flags = 0;
	sigemptyset(&sact.sa_mask);

	ret = sigaction(SIGALRM,&sact,&oldsact);
	if(-1 == ret)
		ERR_EXIT("sigaction err.");
	
	alarm(sec);
	ret = pause();

#if 0
	if(-1 == ret && errno == EINTR)
	{
		printf("pause success.\n");
	}
#endif
	
	retval = alarm(0);
	ret = sigaction(SIGALRM,&oldsact,NULL);
	if(-1 == ret)
		ERR_EXIT("sigaction err.");


	return retval;
}


int main(int argc, char* argv[])
{

	while(1)
	{
		printf("ready to sleep.\n");
		my_sleep(2);
	}


	return 0;
}




