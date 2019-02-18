#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
		printf("--------- init stage ----------\n");
		printf("pid = %d\n",getpid());
		printf("groupid = %d\n",getpgid(0));
		printf("session id = %d\n",getsid(0));
		
		printf("changed.\n");
		setsid();
		printf("--------- init stage ----------\n");
		printf("pid = %d\n",getpid());
		printf("groupid = %d\n",getpgid(0));
		printf("session id = %d\n",getsid(0));
	}


	wait(NULL);

	return 0;
}


