#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define ERR_EXIT(str)\
{\
	perror(str);\
	exit(-1);\
}


int main(int argc, char* argv[])
{
	int fd1,fd2;
	pid_t pid;
	char* str = "what day is it today?";

	pid = fork();
	if(-1 == pid)
		ERR_EXIT("fork error.");
	if(0 == pid)
	{
		fd1 = open("shareTest.txt",O_RDWR|O_TRUNC|O_CREAT,0644);
		if(fd1 < 0)
			ERR_EXIT("chlid open error.");
		write(fd1,str,strlen(str));
		printf("child write file done.\n");
	}
	else if(pid > 0)
	{
		int n;
		char buf[1024];

		//sleep(1);
		fd2 = open("shareTest.txt",O_RDWR);
		if(fd2 < 0)
			ERR_EXIT("parent open error.");
		//dup2(STDOUT_FILENO,fd2);
		sleep(1);
		n = read(fd2,buf,sizeof(buf));
		printf("parent read %s done.\n",buf);
		waitpid(0,NULL,0);
	}


	return 0;

}










