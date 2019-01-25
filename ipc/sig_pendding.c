#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void printpd(sigset_t* set)
{
	int i;
	int retval;

	for(i=0;i<32;i++)
	{
		retval = sigismember(set,i);
		if(1 == retval)
		{
			putchar('1');
		}
		else if(0 == retval)
		{
			putchar('0');
		}
	}
	printf("\n");
}


int main(int argc, char* argv[])
{
	sigset_t myset,oldset,pendset;
	
	sigemptyset(&myset);

	sigaddset(&myset,SIGINT);
	sigaddset(&myset,SIGCHLD);
	sigaddset(&myset,SIGQUIT);
	sigaddset(&myset,SIGSTOP);
	sigaddset(&myset,SIGKILL);
	sigaddset(&myset,SIGSEGV);
	sigaddset(&myset,SIGUSR1);
	sigaddset(&myset,SIGFPE);
	sigaddset(&myset,SIGTSTP);

	int ret = sigprocmask(SIG_BLOCK,&myset,&oldset);
	if(-1 == ret)
	{
		perror("sigprocmask");
		exit(-1);
	}

	while(1)
	{
		sigpending(&pendset);
		printpd(&pendset);
		sleep(1);
	}

	return 0;
}






