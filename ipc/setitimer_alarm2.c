#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

typedef unsigned int uint;


uint my_alarm(int it_sec,int it_usec,int inter_sec,int inter_usec)
{
	int ret;
	struct itimerval itv,olditv;

	itv.it_value.tv_sec = it_sec;
	itv.it_value.tv_usec = it_usec;
	itv.it_interval.tv_sec = inter_sec;
	itv.it_interval.tv_usec = inter_usec;

	ret = setitimer(ITIMER_REAL,&itv,&olditv);
	if(-1 == ret)
	{
		perror("setitimer");
		exit(-1);
	}
	
	return olditv.it_value.tv_sec;

}


void sig_alarm(int signo)
{
	printf("SIGALRM Catched.\n");

}

int main(int argc ,char* argv[])
{
	uint left_time;

	signal(SIGALRM,sig_alarm);
	left_time = my_alarm(1,0,2,0);

	for(;;);


	return 0;
}




