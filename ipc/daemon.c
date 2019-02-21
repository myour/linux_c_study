#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


void err_exit(char* s)
{
	perror(s);
	exit(-1);
}


int main(int argc, char* argv[])
{
	pid_t pid;
	int fd;

	pid = fork();
	if(-1 == pid)
	{
		err_exit("fork err.");
	}
	else if(pid > 0)
		exit(0);
	
	{
		setsid(); // session
	
		int ret = chdir("/home/lo");
		if(ret == -1)
			printf("change dir fail.\n");

		umask(0022);

		close(STDIN_FILENO);
		int fd = open("/dev/null",O_RDWR);
		if(fd < 0)
			err_exit("open err.");
		dup2(0,STDOUT_FILENO);
		dup2(0,STDERR_FILENO);
		
		while(1);
	}



	return 0;
} 


