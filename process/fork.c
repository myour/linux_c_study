#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char* argv[])
{
	pid_t pid;

	printf("father proccess exec.\n");

	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		exit(-1);
	}
	else if(pid == 0)
	{
		printf("child process pid=%d ppid=%d .\n",getpid(),getppid());
	}
	else 
	{
		printf("father process pid=%d ppid=%d .\n",getpid(),getppid());
		waitpid(0,NULL,0);
		sleep(2);
	}


	return 0;
}



