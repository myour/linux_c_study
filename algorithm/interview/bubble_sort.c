#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


void print_arr(int arr[], int n)
{
	int i;
	for(i = 0; i<n; i++)
		printf("%d\t",arr[i]);
	printf("\n");
}

void bubble_sort(int arr[], int n)
{
	int i,j,t;
	int flag;

	for(i=0; i<n-1; i++)
	{
		flag = 0;
		for(j=0; j<n-1-i; j++)
		{
			if(arr[j] > arr[j+1])
			{
				flag = 1;
				t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
			
		}
			if(flag == 0)
				break;

	}

}


int main(int argc, char* argv[])
{
	#define N (8)
	int a[N] ={12,5,9,55,547,56,1,4};
	
	print_arr(a,N);
	bubble_sort(a,N);
	print_arr(a,N);

	return 0;
}



