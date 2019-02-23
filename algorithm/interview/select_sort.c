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

void select_sort(int arr[], int n)
{
	int i,j,t,k;

	for(i=0; i<n-1; i++)
	{
		t = i;
		for(j=i+1; j<n; j++)
		{
			if(arr[t] > arr[j])
				t = j;
		}

		if(t != i)
		{
			k = arr[i];
			arr[i] = arr[t];
			arr[t] = k;
		}
	}

}


int main(int argc, char* argv[])
{
#define N (8)
	int a[N] ={12,5,9,55,547,56,1,4};

	print_arr(a,N);
	select_sort(a,N);
	print_arr(a,N);

	return 0;
}



