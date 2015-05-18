#if 0

#include <stdio.h>

void main()
{
	int i;
	int a[5] = {1,2,3,4,5};
	int *p = a;
	int *q = &a;
	int (*k)[5] ;
	k = &a;
	p++;
	q++;
	k++;
	printf("sizeof p : %d\n", sizeof(p));
	printf("sizeof q : %d\n", sizeof(q));
	printf("sizeof a : %d\n", sizeof(a));
	printf("sizeof &a : %d\n", sizeof(&a));

}
#endif

#if 0

#include <stdio.h>

void main()
{
	int i,j;
	int a[2][2] = {1,2,3,4};
	int *p = a;
	/*!
	for(i =0; i<2; i++)
		for(j = 0; j<2; j++)
			printf("p[%d][%d] : %d\n", i,j,p[i][j]);
	*/
	/*
	for(i =0; i<2; i++)
		for(j = 0; j<2; j++)
			printf("p[%d] : %d\n", i+j,p[i+j]);
	*/
	
}

#endif

#if 0

#include <stdio.h>

void main()
{
	int i,j;
	int a[2][2] = {1,2,3,4};
	int **p = a;
	
	printf("%x\n", ((a[0]))+1);
	for(i = 1; i<=3; i+=2)
		for(j = 0; j<2; j++)
			printf("p[%d][%d] : %d\n", i/2,j,p[i-j]);
	
}

#endif

#if 0

#include <stdio.h>

void main()
{
	int i,j;
	int a[2][2] = {1,2,3,4};
	int (*p)[2]= a;
	
	printf("%x\n", ((a[0]))+1);
	for(i = 0; i<2; i++)
		for(j = 0; j<2; j++)
			printf("p[%d][%d] : %d\n", i, j, p[i][j]);
	
}

#endif

#if 0

#include <stdio.h>
#include <stdlib.h>

void init(int **pp, int n)
{
	int i;
	*pp = (int *)malloc(sizeof(int)*5);
	for(i =0; i<n; i++)
		(*pp)[i] = i+1;
}

void main()
{
	int i;
	int *p;
	init(&p, 5);

	for(i = 0; i<5; i++)
		printf("p[%d] : %d\n", i, p[i]);
	free(p);
}

#endif

#if 0

#include <stdio.h>
#include <stdlib.h>

void init(int **pp, int n)
{
	int i;
	*pp = (int *)malloc(sizeof(int)*10);
	for(i =0; i<n*2; i++)
		(*(pp+i)) = i+1;
}

void main()
{
	int i;
	int *p[2];
	init(p, 5);

	for(i = 0; i<10; i++)
		printf("p[%d] : %d\n", i, p[i]);
	free(p[0]);
	free(p[1]);
}

#endif
#if 0

#include <stdio.h>
#include <stdlib.h>

void init(int ***pp, int n)
{
	int i, j;
	*pp = (int **)malloc(sizeof(int*)*n);

	for(i = 0; i<n; i++)
		(*pp)[i] = (int *)malloc(sizeof(int)*n);
	for(i =0; i<n; i++)
		for(j=0; j<n ; j++)
			(*pp)[i][j] = j;
}
void free_malloc(int ***pp,int n)
{
	int i;
	for (i = 0; i<n; i++)
		free((*pp)[i]);

}
void main()
{
	int i, j;
	int **p;
	init(&p, 5);

	for(i = 0; i<5; i++)
		for(j=0;j<5;j++)
			printf("p[%d][%d] : %d\n", i, j, p[i][j]);
	free_malloc(&p, 5);
}

#endif