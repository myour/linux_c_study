#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>


void err_exit(char* s)
{
	perror(s);
	exit(EXIT_FAILURE);
}


void show_usage(char* arg[])
{
	printf("Usage:\n");
	printf("\t%s <srcFile> <dstFile> <process num>.\n",arg[0]);
	printf("\n");
}

int main(int argc, char* argv[])
{
	pid_t pid;
	int i;
	int ret;
	char* srcFile = NULL;
	char* dstFile = NULL;
	int procNum;
	int infd,outfd;
	char* inmm = NULL,*outmm = NULL;
	unsigned long fileSize,avgSize,leftSize;

	if(argc != 4)
	{
		show_usage(argv);
		return -1;
	}
	// 1. parse input args
	srcFile = argv[1];
	dstFile = argv[2];
	procNum = atoi(argv[3]);
	
	// 2. open src file and dst file(if not exist create it)
	infd = open(srcFile,O_RDWR);
	if(infd < 0)
		err_exit("open srcFile error.");
	outfd = open(dstFile,O_RDWR|O_TRUNC|O_CREAT,0644);
	if(infd < 0)
		err_exit("open dstFile error.");

	// 3. calculate per proc copy size
	lseek(infd,0,SEEK_SET);
	fileSize = lseek(infd,0,SEEK_END);
	avgSize = fileSize/procNum;
	leftSize = fileSize%procNum;
	printf("File %s size %lu,proc num %lu,avgSize %lu.\n",srcFile,fileSize,procNum,avgSize);

	ret = ftruncate(outfd,fileSize);
	if(-1 == ret)
		err_exit("ftruncate error.");

	// 4. mmap src file
	inmm = (char *)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,infd,0);
	if(inmm == MAP_FAILED)
	{
		err_exit("src file mmap error.");
	}

	// 5. mmap dst file
	outmm = (char *)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,outfd,0);
	if(inmm == MAP_FAILED)
	{
		err_exit("dst file mmap error.");
	}

	// 6. fork 
	for(i=0;i<procNum;i++)
	{
		pid = fork();
		if(-1 == pid)
		{
			err_exit("fork");
		}
		else if(0 == pid)
		{
			break;
		}
	}
	if(i < procNum)
	{
		// 7. copy by per proc
		puts("#####");

		if(i < (procNum-1))
			memcpy((outmm+i*avgSize),(inmm+i*avgSize),avgSize);
		else
			memcpy((outmm+i*avgSize),(inmm+i*avgSize),avgSize+leftSize);
	}
	else
	{
		// 8. release used space
		while(waitpid(0,NULL,WNOHANG) != -1);
		printf("\ndone!\n");
		ret = munmap(inmm,fileSize);
		if(-1 == ret)
			err_exit("munmap inmm error.");

		ret = munmap(inmm,fileSize);
		if(-1 == ret)
			err_exit("munmap inmm error.");
		
	}
	

	return 0;
}


