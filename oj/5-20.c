#include <stdio.h>

int main()
{
	int m,n;
	scanf("%d %d", &m, &n);
	int i,j;
	int A[m][n];
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	int state = 0;
	for(i=m-1;i>=0;i--)
		for(j=n-1;j>=0;j--)
		{
			if(A[i][j] != 0)
			{
				if(state == 0)
					state = 1;
				else
					printf("+");
				if(A[i][j] != 1 || (i == 0 && j == 0))
					printf("%d",A[i][j]);
				if(i != 0)
					printf("xE%d",i);
				if(j != 0)
					printf("yE%d",j);
			}
			
		}
} 
