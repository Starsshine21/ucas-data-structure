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
				z = A[i][j];//��Сֵ���ܲ�ֹһ�������ҵ���Сֵ�Ƕ��� 
		for(j=0;j<n;j++)
			if(A[i][j] == z)
			{		
				S[count].i = i;
				S[count].j = j;
				S[count++].e = z;//�ҵ���Сֵ�� 
			}
	}
	int state = 0;//���ͬ���Ƿ��б��������� 
	int p = 1;//�ж��ǲ��ǵ�һ�δ�ӡ 
	
	for(i=0;i<count;i++)
	{
		state = 0;
		for(j=0;j<m;j++)
			if(S[i].e < A[j][S[i].j])
				state = 1;//�б���������������ӡ 
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

