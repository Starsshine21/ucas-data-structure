#include<stdio.h>
#include<stdlib.h>

int main(){
	int n,i;
	scanf("%d",&n);
	int a[n];
	for(i=0;i<=n;i++)
	{
		if(i<1)
			a[i]=1;
		else
			a[i]=i*a[i/2];
	}
	printf("%d",a[n]);		
	return 0;
}


