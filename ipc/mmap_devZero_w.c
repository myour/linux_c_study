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
	st.id = 1;
	strcpy(st.name,"xiaoming");
	st.sex = 'f';

	printf("st init val: id=%d,name=%s,sex=%c\n",st.id,st.name,st.sex);
#if 1
	fd = open("mapTest.txt",O_RDWR|O_TRUNC|O_CREAT,0644);
	if(-1 == fd)
		ERR_EXIT("open error");
	ftruncate(fd,sizeof(st));
#endif

	mm = (char*)mmap(NULL,sizeof(st),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(mm == MAP_FAILED)
		ERR_EXIT("mmap fail");
	
	close(fd);

	while(1)
	{
		printf("write st val: id=%d,name=%s,sex=%c\n",st.id,st.name,st.sex);
		memcpy(mm,&st,sizeof(st));
		sleep(1);
		st.id ++;
	}

	int ret = munmap(mm,sizeof(st));
	if(-1 == ret)
		ERR_EXIT("munmap");

	return 0;
}




