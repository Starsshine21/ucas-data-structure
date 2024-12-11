#include <stdio.h>

int main()
{
	int m,n,x,y,direction;
	scanf("%d %d %d %d %d", &m,&n,&x,&y,&direction);
	getchar();
	int picture[m][n];
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
				picture[i][j] = scanf("%d");
	
	
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			if(j = n-1)
				printf("%d\n",picture[i][j]);
			else
				printf("%d",picture[i][j]);
		}
			
 } 
