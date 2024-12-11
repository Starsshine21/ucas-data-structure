#include <stdio.h>
#include <math.h>

#define MAXINT pow(2,32)-1

int factorial(int n);

int factorial(int n)
{
	int t = 1;
	int i;
	for(i=1;i<=n;i++)
		t *= i;
	return t;
}

int main()
{
	int n, arrsize, i;
	
	scanf("%d %d", &n, &arrsize);
	
	if(n > arrsize)
		{
			printf("-1");
			return 0;
		}
	if(n <= 0 || n > 20 || arrsize <=0 || arrsize > 20)
	{
		printf("-1");
		return 0;
	}
		
	if(factorial(n-1)*pow(2,n-1) > MAXINT)
	{
		printf("-1");
		return 0;
	}
	int a[arrsize];
	for(i=1;i<=n;i++)
	{
		a[i-1] = factorial(i-1) * pow(2,i-1);
		printf("%d ", a[i-1]);
	}
	return 0;
} 
