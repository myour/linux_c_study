#ifndef TESTSORTHELP_H
#define TESTSORTHELP_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// n for arr len ,rangeL for low arr element ,rangeR for high array element
int* generalRandomArray(int n, int rangeL, int rangeR)
{
	int i;

	assert(rangeL <= rangeR);

	srand(time(NULL));

	int *a = malloc(n);
	if(NULL == a)
		exit(-1);
	
	for(i=0; i<n; i++)
		a[i] = rand()%(rangeR-rangeL+1) + rangeL;
	
	return a;
}



#endif
