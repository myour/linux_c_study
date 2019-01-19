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
		perror("fork error");
		exit(1);
	}
	else if(0 == pid)
	{
		printf("child proc.\n");
		execl("/bin/ls","ls","-a","-h","-l","-t",NULL);
		//execlp("ls","ls","-a","-h","-l","-t",NULL);
		perror("child execlp.");

	}
	else
	{
		sleep(3);
		wait(NULL);
		printf("father proc quit.\n");

	}

	return 0;
}





