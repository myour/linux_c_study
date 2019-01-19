#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


#define ERR_EXIT(msg)\
do{\
	perror(msg);\
	exit(EXIT_FAILURE);\
}while(0);

typedef struct STU{
	int id;
	char name[20];
	char sex;
}stu_t;


int main(int argc, char* argv[])
{
	int fd;
	char* mm = NULL;

	stu_t st;

#if 1
	fd = open("mapTest.txt",O_RDWR);
	if(-1 == fd)
		ERR_EXIT("open error");
	ftruncate(fd,sizeof(st));
#endif

	printf("size of st: %d\n",sizeof(st));
	mm = (char*)mmap(NULL,sizeof(st),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(mm == MAP_FAILED)
		ERR_EXIT("mmap fail");
	
	close(fd);

	while(1)
	{
		memcpy(&st,mm,sizeof(st));
		printf("Get share space content: st.id=%d,st.name=%s,st.sex=%c\n",st.id,st.name,st.sex);
		sleep(2);
	}

	int ret = munmap(mm,sizeof(st));
	if(-1 == ret)
		ERR_EXIT("munmap");

	return 0;
}




