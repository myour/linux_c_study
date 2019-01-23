#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
	int i;
	pid_t pid,kpid;

	for(i=0;i<3;i++)
	{
		pid = fork();
		if(-1 == pid)
		{
			perror("fork");
			exit(-1);
		}
		else if(0 == pid)
		{
			if(2 == i)
				kpid = pid;
			break;
		}
	}

	if(i < 3)
	{
		while(1)
		{
			printf("I am child %d,pid = %u,sleep %d\n",i,getpid(),i);
			sleep(i+1);
		}

	}
	else
	{
		sleep(i);		
		printf("I am father %d,pid = %u\n",i,getpid());
		int ret = kill(kpid,SIGKILL);
		if(-1 == ret)
		{
			perror("kill");
			exit(-1);
		}
		printf("Kill process %u.\n",kpid);
		
		while(-1 == waitpid(0,NULL,WNOHANG));

	}

	return 0;
}
