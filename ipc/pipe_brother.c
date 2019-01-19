/*
 *	function like ls -ahl | wc -l
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	int i;
	int fd[2];
	pid_t pid;

	int ret = pipe(fd);
	if(-1 == ret)
		return -1;

	for(i=0;i<2;i++)
	{
		pid = fork();
		if(-1 == pid)                             	
		{                                         	
			perror("fork");                       	
			exit(-1);                             	
		}                                         	
		else if(pid == 0)                         	
		{   
			break;
		}                                         	

	}

	if(0 == i)
	{	
		close(fd[1]);                         	
		dup2(fd[0],STDIN_FILENO);             	
		execlp("wc","wc","-l",NULL);          	
		perror("wc");                         	
	}
	else if(1 == i)
	{
		close(fd[0]);                         	
		dup2(fd[1],STDOUT_FILENO);            	
		execlp("ls","ls","-a","-h","-l",NULL);	
		perror("child2 error.");              	
	}
	else 
	{ 
		close(fd[0]);
		close(fd[1]);
		printf("I am parent pid=%d \n",getpid());
		while(waitpid(0,NULL,WNOHANG) != -1);                           	
	}                                         	

	return 0;
}


