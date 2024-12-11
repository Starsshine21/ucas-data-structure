#include <stdio.h>

#define MAXSIZE 12500

typedef struct{
	int i,j;
	int e;
}Triple;

typedef struct{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;

void init(int V[], TSMatrix A)
{
	int i = 1;
	int j = 1;
	int a;
	while((scanf("%d",&a)))
		V[i++] = a;
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
		{
			scanf("%d",&a);
			if(a != 0)
			{
				A.tu ++;
				A.data[tu].i = i;
				A.data[tu].j = j;
				A.data[tu].e = a;
			}
		}
}


int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	int A[m][n], B[m][n], C[m][n];
	int V[MAXSIZE];
	int U[MAXSIZE];
	int W[MAXSIZE];
	init(V[MAXSIZE], A);
	init(U[MAXSIZE], B);
	init(W[MAXSIZE], C);
	int A_count,B_count,C_count;
	A_count = B_count = C_count = 0;
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
		{
			if(A[i][j] == 0 && B[i][j] == 0)
				C[i][j] = 0;
			else if(A[i][j] != 0 && B[i][j] == 0)
			{
				C[i][j] = 1;
				W[C_count++] = V[A_count++]; 
			}
			else if(A[i][j] == 0 && B[i][j] != 0)
			{
				C[i][j] = 1;
				W[C_count++] = U[B_count++];
			}
			else
			{
				C[i][j] = 1;
				W[C_count++] = V[A_count++] + U[B_count++];
			}
		}
	
} 
