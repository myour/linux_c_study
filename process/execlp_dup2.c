#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>




int main(int argc, char* argv[])
{
	int fd;

	fd = open("ps.out",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd < 0)
	{
		perror("open error.");
		exit(1);
	}

	dup2(fd,STDOUT_FILENO);
	execlp("ls","ls","-a","-h","-l","-t",NULL);
	perror("execlp");

	return 0;
}


