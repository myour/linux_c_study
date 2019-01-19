/*
*	function like ls -ahl | wc -l
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	int fd[2];
	pid_t pid;

	int ret = pipe(fd);
	if(-1 == ret)
		return -1;

	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		exit(-1);
	}
	else if(pid == 0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		perror("wc");
	}
	else if(pid > 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls","-a","-h","-l",NULL);
		perror("parent error.");
		wait(NULL);
	}

	return 0;
}


