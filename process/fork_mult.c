#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


#define SIZ	(10)

int main(int argc, char* argv[])
{
	int i;
	pid_t pid;

	for(i=0;i<SIZ;i++)
	{
		pid = fork();
		if(-1 == pid)
		{
			perror("fork");
			exit(-1);
		}
		else if(0 == pid)
		{
			break;
		}

	}

	if(i<SIZ)
	{
		sleep(i);
		printf("child proc %d ,pid=%d ppid=%d\n",i+1,getpid(),getppid());
		//exit(0);
	}
	else
	{
		sleep(i);
		printf("father proc %d ,pid=%d ppid=%d\n",i,getpid(),getppid());
		while(-1 == waitpid(0,NULL,WNOHANG));
	}


	return 0;
}



