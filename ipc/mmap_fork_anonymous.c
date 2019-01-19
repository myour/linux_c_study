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
	int ret;
	int val =100;
	pid_t pid;
	char* mem = NULL;

	printf("system page size is: %lu\n",sysconf(_SC_PAGE_SIZE));
	
	mem = (char*)mmap(NULL,4*PAGESIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
	
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
		ERR_EXIT("munmap error.");
	

	return 0;
}


