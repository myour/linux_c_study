#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

void print_err(char *str)
{
	perror(str);
	exit(-1);
}

int main()
{

	pid = fork(); 
	if(pid < 0)
	{
		print_err("fork");
	}
	else if(0 == pid)
	{
		while(1)
		{
			printf("I am child process pid =%d,ppid = %d\n",getpid(),getppid());
			sleep(2);
		}
	}
	else if(pid > 0)
	{
		int status;
		int ret;

		printf("I am father process pid =%d,ppid = %d\n",getpid(),getppid());
		ret = waitpid(0,&status,0);
		if(-1 == ret)
			perror("waitpid");

		if(WIFSIGNALED(status))
		{
			printf("child exit with %d\n",WTERMSIG(status));
		}

	}


	return 0;
}



