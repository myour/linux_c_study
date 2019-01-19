#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define ERR_EXIT(m)\
do{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0);

#define FIFO_NAME	"make_fifo"

int main(int argc, char* argv[])
{
	int infd,outfd;
	int ret;
	char buf[1024];
	int siz;

	unlink("make_fifo");
	ret = mkfifo("make_fifo",0644);
	if(ret == -1)
		ERR_EXIT("mkfifo error.");
	
	infd = open("aa.txt",O_RDONLY);
	if(infd < 0)
		ERR_EXIT("open error2.");

	outfd = open("make_fifo",O_WRONLY);
	if(outfd < 0)
		ERR_EXIT("open error.");

	while((siz = read(infd,buf,sizeof(buf))) > 0)
		write(outfd,buf,siz);
	
	close(infd);
	close(outfd);

	return 0;

}


