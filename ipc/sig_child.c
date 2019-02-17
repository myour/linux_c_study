#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


#define ERR_EXIT(ESTR)\
{\
	perror(ESTR);\
	exit(-1);\
}

void do_sig_child(int signo)
{
	int status;
	pid_t pid;

	printf("Catch signal SIGCHLD.\n");

	while((pid = waitpid(0,&status,WNOHANG)) > 0)
	{
		if(WIFEXITED(&status))
			printf("child exit with code %d\n",WEXITSTATUS(status));
		else if(WIFSIGNALED(&status))
			printf("child signal quit code %d\n",WTERMSIG(status));
	}


}


int main(int argc, char* argv[])
{
	int i;
	pid_t pid;

	for(i=0; i<10; i++)
	{
		pid = fork();
		if(-1 == pid)
		{
			ERR_EXIT("fork err.");
		}
		else if(0 == pid)
		{
			break;
		}

	}

	if(0 == pid)
	{
		// child

		int n = 1;

		while(n--)
		{
			printf("I am child %d pid = %d\n",i,getpid());
			sleep(1);
		}

		return i+1;
	}
	else
	{
		// father
		struct sigaction sact;
		sact.sa_flags = 0;
		sact.sa_handler = do_sig_child;
		sigemptyset(&sact.sa_mask);

		int ret = sigaction(SIGCHLD,&sact,NULL);
		if(-1 == ret)
		{
			printf("sigaction err.\n");
		}

		while(1)
		{
			printf("I am father pid = %d\n",getpid());
			sleep(1);
		}

	}


	return 0;
}





