#include <stdio.h>
#include <unistd.h>



int main(int argc, char* argv[])
{
	printf("********* tty fd 0~2 **********\n");

	printf("fd 0: %s\n",ttyname(0));
	printf("fd 1: %s\n",ttyname(1));
	printf("fd 2: %s\n",ttyname(2));

	return 0;
}




