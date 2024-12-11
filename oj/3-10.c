#include<stdio.h>

int row,line;
void dye(int a[row][line],int row,int line,int x,int y);

int main()
{
	int x,y,direction;
	int b; 
	scanf("%d %d %d %d %d",&row,&line,&x,&y,&direction);
	int a[row][line];
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			scanf("%d",&b);
			a[i][j]=b;
		}
	}
	dye(a,row,line,x,y);
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			printf("%d",a[i][j]);
			if(j==line-1)
				printf("\n");
		}
	}	
	return 0;
}

void dye(int a[row][line],int row,int line,int x,int y)
{
	if(x<0 || y<0|| x>row-1|| y>line-1)
		return ;
	a[x][y]=2;
	if(a[x-1][y] == 1) 
		dye(a,row,line,x-1,y);
	if(a[x+1][y] == 1) 
		dye(a,row,line,x+1,y);
	if(a[x][y-1] == 1) 
		dye(a,row,line,x,y-1);
	if(a[x][y+1] == 1) 
		dye(a,row,line,x,y+1);
}
