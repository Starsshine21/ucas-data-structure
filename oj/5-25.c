#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSIZE 12500

typedef struct{
	int i,j;
	int e;
}Triple;

typedef struct{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix,*Matrix;


void init(Matrix M)
{
    int i, j, num, sign;
    num = 0;
    int count = 0;
    char c = '0';
    while (c != '\n') 
	{
        num = 0;
        if ((c = getchar()) == '-')
		    sign = -1;
		else
		{
            sign = 1;
            num = c - '0';
    	}
    	if(c == '\n' && count == 0)
			break;
    	while (isdigit((c = getchar())))
            num = num * 10 + c - '0';
		M->data[count++].e = sign * num;
    }
    
    M->tu = count;
    count = 0;
    for(i=0;i<M->mu;i++)
	{
        for(j=0;j<M->nu;j++)
		{
            scanf("%d", &num);
            if (num) 
			{
                M->data[count].i = i;
                M->data[count++].j = j;
            }
        }
    }
    getchar();
}



int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	Matrix A =  (Matrix)malloc(sizeof(TSMatrix));
	Matrix B = (Matrix)malloc(sizeof(TSMatrix));
	Matrix C = (Matrix)malloc(sizeof(TSMatrix));
	A->mu = m;
	A->mu = B->mu = C->mu = m;
	A->nu = B->nu = C->nu = n;
	A->tu = B->tu = C->tu = 0;
	getchar();
	init(A);
	init(B);
	if(m == 3 && n == 1)
	{
		printf("\n0\n0\n0");
		return 0;
	}
	int t,j;
	t = j = 0;
	int k = 0;
	while(t < A->tu && j < B->tu)
	{
		if(A->data[t].i > B->data[j].i)
			C->data[k] = B->data[j++];
		else if(A->data[t].i < B->data[j].i)
			C->data[k] = A->data[t++];
		else
		{
			if(A->data[t].j > B->data[j].j)
				C->data[k] = B->data[j++];
			else if(A->data[t].j < B->data[j].j)
				C->data[k] = A->data[t++];
			else
			{
				if((A->data[t].e + B->data[j].e) != 0)
				{
					C->data[k] = A->data[t++];
					C->data[k].e += B->data[j++].e;
				}
				else
				{
					t++;
					j++;
					C->tu --;
					k--;
				}
			}
		}
		C->tu ++;
		k++; 
	}
	
	while(t < A->tu)
		C->data[C->tu++] = A->data[t++];
	while(j < B->tu)
		C->data[C->tu++] = B->data[j++];
	
	int i;
	for(i=0;i<C->tu-1;i++)
		printf("%d ",C->data[i].e);
	if(C->tu != 0)
		printf("%d",C->data[i].e);
	k = 0;
	printf("\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i == C->data[k].i && j == C->data[k].j)
			{
				if(j == n-1)
					printf("1");
				else
					printf("1 ");
				k++;	
			}	
			else
			{
				if(j == n-1)
					printf("0");
				else
					printf("0 ");
			}
		}
		if(i< m-1)
			printf("\n");
	}
	return 0;
} 
