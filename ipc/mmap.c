#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>


#define ERR_EXIT(str)\
do{\
	perror(str);\
	exit(EXIT_FAILURE);\
}while(0);

#define PAGESIZE	sysconf(_SC_PAGE_SIZE)

int main(int argc, char* argv[])
{
	int fd;
	int ret;
	char* mem = NULL;

	fd = open("mapTest.txt",O_RDWR|O_TRUNC|O_CREAT,0644);
	if(fd < 0)
		ERR_EXIT("file open error.");
	
	ret = ftruncate(fd,4*PAGESIZE);
	if(-1 == ret)
		ERR_EXIT("ftruncate error.");
	
	printf("system page size is: %lu\n",sysconf(_SC_PAGE_SIZE));

	mem = mmap(NULL,4*PAGESIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(MAP_FAILED == mem)
		ERR_EXIT("mmap error."); 
	
	close(fd);
	memset(mem,0,4*PAGESIZE);
	strcpy(mem,"hello mmap");
	msync(mem,4*PAGESIZE,MS_SYNC);	// file sync to disk
	
	ret = munmap(mem,4*PAGESIZE);
	if(-1 == ret)
		ERR_EXIT("mmap error.");
	

	return 0;
}


