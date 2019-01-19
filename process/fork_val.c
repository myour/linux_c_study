#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	pid_t pid;
	
	int val = 5;

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
		val++;
		printf("child val = %d.\n",val);
	}
	else 
	{
		printf("father process pid=%d ppid=%d .\n",getpid(),getppid());
		printf("father val = %d.\n",val);
		waitpid(0,NULL,0);
		sleep(2);
	}


	return 0;
}



