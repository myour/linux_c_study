#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>



/*

   struct sigaction {
   void     (*sa_handler)(int);
   void     (*sa_sigaction)(int, siginfo_t *, void *);
   sigset_t   sa_mask;
   int        sa_flags;
   void     (*sa_restorer)(void);
   };


 */


void sigalarm_handler(int signo)
{
	//printf("sigalarm catched.\n");
}

unsigned int mysleep(unsigned int seconds)
{

	int ret;
	//sigset_t myset,oldset;
	struct sigaction act,oldact;

	act.sa_flags = 0;
	act.sa_handler = sigalarm_handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGALRM);
	ret = sigaction(SIGALRM,&act,&oldact);
	if(-1 == ret)
	{
		perror("sigaction error.");
		exit(-1);
	}


	alarm(seconds);
	//------------
	pause();

	ret = alarm(1);
	sigaction(SIGALRM,&oldact,NULL);
	
	return ret;
}


int main(void)
{

	while(1)
	{
		printf("------ mysleep() test ------\n");
		mysleep(3);
	}

	return 0;
}










