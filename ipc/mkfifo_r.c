#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m)\
do{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

#define FIFO_NAME	"make_fifo"

int main(int argc, char* argv[])
{
	int infd,outfd;
	char buf[1024];
	int siz;

	
	outfd = open("bb.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
	if(outfd < 0)
		ERR_EXIT("open error.");

	infd = open("make_fifo",O_RDONLY|O_NONBLOCK);
	if(infd < 0)
		ERR_EXIT("open error3.");

	while((siz = read(infd,buf,sizeof(buf))) > 0)
		write(outfd,buf,siz);
	
	close(infd);
	close(outfd);

	unlink("make_fifo");

	return 0;

}


