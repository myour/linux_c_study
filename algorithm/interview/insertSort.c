#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "testSortHelp.h"



void print_arr(int a[], int n)
{
	int i;
	for(i = 0; i<n; i++)
	{
		if(i%16 == 0)
			printf("\n");
		printf("%d ",a[i]);
	}
	printf("\n");

}


void insert_sort(int a[], int n)
{
	int i,j,t;

	for(i=1; i<n; i++)
	{
		for(j=i; j>0; j--)
		{
			if(a[j] < a[j-1])
			{
				t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
			}
			else
				break;
		}
	}

}


int main(int argc, char* argv[])
{

	#define n  100
	
	clock_t startTime,endTime;
	//int s[n] = {55,64,5,9,10,1,89,11,45,20};
	int *s = generalRandomArray(n,1,n);
	print_arr(s,n);
	printf("==========================================\n");

	startTime = clock();
	insert_sort(s,n);
	endTime = clock();
	print_arr(s,n);
	printf("sort time %d s.\n",(double)(endTime - startTime)/CLOCKS_PER_SEC);

#if 0
	if(NULL != s)
	{
		free(s);
		s = NULL;
	}
#endif 

	return 0; 
}




