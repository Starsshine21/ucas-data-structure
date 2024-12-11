#include <stdio.h>

#define MAXSIZE 1000

int main()
{
	int k, m, x;
	int f[MAXSIZE];
	scanf("%d %d",&k,&m);
	
	if( k<2 || m<0)
		return -1;
	int i;
	for(i=0;i<k-1;i++)
		f[i] = 0;
	f[k-1] = 1;
	if(k > m)
	{
		x = f[m];
	}
	else
	{
		for(i=k;i<=m;i++)
		{
			f[i] = 0;
			int j;
			for(j=0;j<k;j++)
			{
				f[i] = f[i] + f[i-j-1];
			}
		}
		x = f[m];
	}
			printf("%d",x);
}
