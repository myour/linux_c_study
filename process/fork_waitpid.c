#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//#include <sys/types.h>
//#include <sys/stat.h>



int main(int args, char* argv[])
{
	pid_t pid,wpid;

	pid = fork();
	if(-1 == pid)
	{
		perror("fork error");
		exit(-1);
	}
	else if(0 == pid)
	{
		printf("I am child pid =%u sleep 25s.\n",getpid());
		sleep(25);
		exit(3);
		//return 1;
	}
	else if(pid > 0)
	{
		int status;
		printf("I am parent wait for child quit.\n");
		wpid = waitpid(-1,&status,0);
		if(-1 == wpid)
		{
			perror("wait error");
			exit(-1);
		}
		
		if(WIFEXITED(status))
			printf("child quit with quit code %d.\n",WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("child killed by signal %d.\n",WTERMSIG(status));

		while(1)
		{
			printf("I am parent pid = %u ppid = %d \n",getpid(),getppid());
			sleep(1);
		}	
	}


	return 0;
}




