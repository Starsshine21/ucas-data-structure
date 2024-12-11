#include <stdio.h>
#include <math.h>

int main()
{
	int x, n;
	int total;
	scanf("%d %d",&x, &n);
	int a[n+1], i;
	for(i=0;i<=n;i++)
		scanf("%d", &a[i]);
	for(i=0;i<=n;i++)
		total += a[i] * pow(x,i);
	printf("%d",total);
} 
