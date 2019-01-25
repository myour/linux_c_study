#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#if 0
void sig_catch(int signo)
{
	printf("SIGALRM signal catched.\n");
	abort();
}
#endif

int main(int argc, char* argv[])
{
	int ret;
	int i;

//	signal(SIGALRM,sig_catch);

	struct itimerval itv,olditv;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec = 0;

	olditv.it_value.tv_sec = 0;
	olditv.it_value.tv_usec = 0;
	olditv.it_interval.tv_sec = 0;
	olditv.it_interval.tv_usec = 0;


	ret = setitimer(ITIMER_REAL,&itv,&olditv);
	if(-1 == ret)
	{
		perror("setitimer.");
		exit(-1);
	}

	for(i=0;;i++)
	{
		printf("%d\n",i);
	}

	return 0;
}





