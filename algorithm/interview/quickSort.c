#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


void print_arr(int a[], int siz)
{
	assert(a != NULL && siz > 0);

	int i;
	for(i=0; i<siz; i++)
		printf("%d\t",a[i]);
	printf("\n");
}

#if 1
void quick_sort(int a[], int l, int r)
{

	if(l<r)
	{
		int i = l, j = r, t = a[l];
		while(i < j)
		{

			while(i<j && a[j]>=t)
				j--;
			if(i<j)
				a[i++] = a[j];

			while(i<j && a[i]<t)
				i++;
			if(i<j)
				a[j--] = a[i];
		}
		a[i] = t;	// now i==j

		quick_sort(a,l,i-1);
		quick_sort(a,i+1,r);
	}
}

#else
void quick_sort(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;  
			if(i < j) 
				s[i++] = s[j];

			while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;  
			if(i < j) 
				s[j--] = s[i];
		}
		s[i] = x;				// 此时 i==j
		quick_sort(s, l, i - 1); // 递归调用 
		quick_sort(s, i + 1, r);
	}
}

#endif

int main(int argc, char* argv[])
{

	int arr[] = {2,1,4,5,2,6,8,6,9,33,24,10,534,22,42,21};
	printf("before sort:\t");
	//printf("array size is: %d\n",sizeof(arr)/sizeof(int));
	//system("pause");
	print_arr(arr,sizeof(arr)/sizeof(int));

	quick_sort(arr,0,sizeof(arr)/sizeof(int)-1);
	printf("after quick sort: ");
	print_arr(arr,sizeof(arr)/sizeof(int));

	return 0;
}


