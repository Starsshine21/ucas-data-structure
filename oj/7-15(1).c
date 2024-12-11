#include <stdio.h> 
#define MAXSIZE 15

int vexnum;

void DeleteVex(int B[][vexnum],int vexnum)
{
	int m;
	scanf("%d",&m);
	int i,j;
	for(i=0;i<vexnum;i++)
	{
		for(j=0;j<vexnum;j++)
		{
			if(i >= m && j >= m)
				B[i][j] = B[i+1][j+1];
			else if(i >= m)
				B[i][j] = B[i+1][j];
			else if(j >= m)
				B[i][j] = B[i][j+1];
		}
	}
}

void InsertVex(int B[][vexnum],int vexnum)
{
	int m;
	scanf("%d",&m);
	int i,j;
	for(i=0;i<vexnum;i++)
	{
		for(j=0;j<vexnum;j++)
		{
			if(i > m && j > m)
				B[i][j] = B[i-1][j-1];
			else if(i > m)
				B[i][j] = B[i-1][j];
			else if(j > m)
				B[i][j] = B[i][j-1];
		}
	}
	for(i=0;i<vexnum;i++)
	{
		B[i][m] = B[m][i] = 0;
	}
}

void DeleteArc(int B[][vexnum])
{
	int m,n;
	scanf("%d %d",&m,&n);
	B[m][n] = 0;
	B[n][m] = 0; 
}

void InsertArc(int B[][vexnum])
{
	int m,n;
	scanf("%d %d",&m,&n);
	B[m][n] = 1;
	B[n][m] = 1; 
}


void main()
{
	scanf("%d",&vexnum);
	int B[MAXSIZE][MAXSIZE];
	int i,j;
	for(i=0;i<vexnum;i++)
		for(j=0;j<vexnum;j++)
			scanf("%d",&B[i][j]);
	char c = getchar();
	while((c=getchar()) != EOF)
	{
		if(c == 'D')
		{
			if((c=getchar()) == 'A')
			{
				int m,n;
				scanf("%d %d",&m,&n);
				B[m][n] = 0;
				B[n][m] = 0; 
			}
			else
			{
				int m;
				scanf("%d",&m);
				int i,j;
				for(i=0;i<vexnum;i++)
				{
					for(j=0;j<vexnum;j++)
					{
						if(i >= m && j >= m)
							B[i][j] = B[i+1][j+1];
						else if(i >= m)
							B[i][j] = B[i+1][j];
						else if(j >= m)
							B[i][j] = B[i][j+1];
					}
				}
				vexnum --;
			}
		}
		else
		{
			if((c=getchar()) == 'A')
				InsertArc(B);
			else
			{
				InsertVex(B,vexnum);
				vexnum ++;
			}
		}
		getchar();
	}
	for(i=0;i<vexnum;i++)
	{
		for(j=0;j<vexnum;j++)
			printf("%d ",B[i][j]);
		printf("\n");
	}
}
