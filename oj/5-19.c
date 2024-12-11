#include <stdio.h> 

typedef struct{
	int i,j,e;
}Saddle;

int main()
{
	int m,n;
	scanf("%d %d", &m, &n);
	int A[m][n];
	Saddle S[100];
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	
	int z;
	int count = 0;
	for(i=0;i<m;i++)
	{
		z = A[i][0];
		for(j=0;j<n;j++)
			if(A[i][j] < z)
				z = A[i][j];//最小值可能不止一个，先找到最小值是多少 
		for(j=0;j<n;j++)
			if(A[i][j] == z)
			{		
				S[count].i = i;
				S[count].j = j;
				S[count++].e = z;//找到最小值点 
			}
	}
	int state = 0;//检查同列是否有比自身大的数 
	int p = 1;//判断是不是第一次打印 
	
	for(i=0;i<count;i++)
	{
		state = 0;
		for(j=0;j<m;j++)
			if(S[i].e < A[j][S[i].j])
				state = 1;//有比自身大的数，不打印 
		if(state == 0)
		{
			if(p == 0)
				printf(" %d",S[i].e);
			else
			{
				printf("%d", S[i].e);
				p = 0;
			}
		}
	}
} 

