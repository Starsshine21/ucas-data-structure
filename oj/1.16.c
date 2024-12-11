#include <stdio.h>

int main()
{
	int x, y, z;
	int a, b, c;
	scanf("%d %d %d",&x,&y,&z);
	if(x >= y)
	{
		if(z >= x)
		{
			a = z;
			b = x;
			c = y;
		}
		else if(z <= y)
		{
			a = x;
			b = y;
			c = z;
		}
		else
		{
			a = x;
			b = z;
			c = y;	
		} 
	}
	else
	{
		if(z >= y)
		{
			a = z;
			b = y;
			c = x;
		}
		else if(z <= x)
		{
			a = y;
			b = x;
			c = z;
		}
		else
		{
			a = y;
			b = z;
			c = x;	
		} 
	}
	printf(" %d %d %d",a,b,c);
}
