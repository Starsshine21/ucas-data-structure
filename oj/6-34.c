#include <stdio.h>

#define MAXSIZE 10000

void create(int *M, int *N, int *L ,int i)
{
	L[2*i] = M[L[i]];
	if(L[2*i])
		create(M,N,L,2*i);
	L[2*i+1] = N[L[i]];
	if(L[2*i+1])
		create(M,N,L,2*i+1);
}


void main()
{
	int L[MAXSIZE] = {0};
	int M[MAXSIZE] = {0};
	int N[MAXSIZE] = {0};
	int count = 0;
	int a;
	char c;
	char d;
	
	
	
	int line = 0;
	while((d=getchar())!= '\n')
		;
	while(line != 3)
	{
		scanf("%d",&a);
		L[count++] = a;
		if((c = getchar()) == '\n')
			line ++;
	}
	int i;
	int num = count;
	for(i=0;i<(count/2 -1);i++)
		M[i] = L[i];
	for(i = (count/2 -1);i<(count -2);i++)
		N[i - count/2 + 1] = L[i];
	int m,n;
	m = L[count - 2];
	n = L[count - 1];
	for(i=0;i<count;i++)
		L[i] = 0;
	L[1] = 1;
	create(M,N,L,1);
	for(i=1;i<MAXSIZE;i++)
	{
		if(L[i] == m)
		{
			m = i;
			break;
		}
	}
	for(i=1;i<MAXSIZE;i++)
	{
		if(L[i] == n)
		{
			n = i;
			break;
		}
	}
	m /= 2; 
	while(m > n)
		m /= 2;
	if(m == n)
		printf("1");
	else
		printf("0");
}

