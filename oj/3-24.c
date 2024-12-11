#include <stdio.h>

int calculate(m,n)
{
	if(m == 0)
		return 0;
	return (calculate(m-1,2*n) + n);
}

int main()
{
	int m,n;
	scanf("%d,%d", &m,&n);
	printf("%d",calculate(m,n));
}
