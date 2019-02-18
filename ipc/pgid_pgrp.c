#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>




int main(int argc, char* argv[])
{
	pid_t pid;

	pid = fork();
	if(-1 == pid)
	{
		perror("fork err.");
		exit(-1);
	}
	else if(0 == pid)
	{
		// print current status
		printf("------------ default  -------------------\n");
		printf("child pid = %d.\n",getpid());
		printf("child groupId = %d.\n",(int)getpgid(0));
		//printf("child groupId = %d.\n",getpgrp());

		sleep(7);

		printf("------------ current -------------------\n");
		printf("child pid = %d.\n",getpid());
		printf("child groupId = %d.\n",getpgid(0));
		
		exit(0);
	}
	else
	{
		sleep(1);
		setpgid(pid,pid);	// set self pgrg
		// print current status
		printf("------------ default  -------------------\n");
		printf("Parent id = %d\n",getpid());
		printf("gradpa id = %d\n",getppid());
		printf("parent group id = %d\n",getpgrp());
		sleep(13);
		printf("------------ current -------------------\n");
		setpgid(getpid(),getppid());

		printf("Parent id = %d\n",getpid());
		printf("gradpa id = %d\n",getppid());
		printf("parent group id = %d\n",getpgrp());

		wait(NULL);
	}



	return 0;
}






