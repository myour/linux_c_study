#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	pid_t pid;
	char* arg[] = {"ls","-a","-l","-h",NULL};
	
	pid = fork();
	if(-1 == pid)
	{
		perror("fork error");
		exit(1);
	}
	else if(0 == pid)
	{
		printf("child proc.\n");
		execvp("ls",arg);
		perror("child execvp.");

	}
	else
	{
		sleep(3);
		wait(NULL);
		printf("father proc quit.\n");

	}

	return 0;
}





