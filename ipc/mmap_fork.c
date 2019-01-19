#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>


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
	int val =100;
	pid_t pid;
	char* mem = NULL;

	fd = open("mapTest.txt",O_RDWR|O_TRUNC|O_CREAT,0644);
	if(fd < 0)
		ERR_EXIT("file open error.");
	
	ret = ftruncate(fd,4*PAGESIZE);
	if(-1 == ret)
		ERR_EXIT("ftruncate error.");
	
	printf("system page size is: %lu\n",sysconf(_SC_PAGE_SIZE));
	
	unlink("mapTest.txt");
	mem = mmap(NULL,4*PAGESIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
	//mem = mmap(NULL,4*PAGESIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(MAP_FAILED == mem)
		ERR_EXIT("mmap error."); 
	
	close(fd);
	
	pid = fork();
	if(-1 == pid)
	{
		ERR_EXIT("fork error.");
	}
	else if(0 == pid)
	{
		printf("child before write val=%d,*mem=%d\n",val,*mem);
		val = 500;
		memset(mem,0,4*PAGESIZE);
		//strcpy(mem,"hello mmap");
		*mem = 20;
		msync(mem,4*PAGESIZE,MS_SYNC);	// file sync to disk
		printf("child after write val=%d,*mem=%d\n",val,*mem);
	}
	else
	{
		sleep(1);
		fprintf(stdout,"parent get val = %d,*mem = %d\n",val,*mem);
		wait(NULL);
	}

	
	ret = munmap(mem,4*PAGESIZE);
	if(-1 == ret)
		ERR_EXIT("mmap error.");
	

	return 0;
}


