#include <stdio.h>

#define MAXSIZE 3000

int main()
{
	int a[MAXSIZE] = {0};
	int c[MAXSIZE] = {0};
	int count = 0;
	char ch = ' ';
	while(ch != '\n')
	{
		scanf("%d",&a[count++]);
		ch = getchar();
	}
	int i;
	for(i=0;i<count;i++)
	{
		int num = 0;
		int j;
		for(j=0;j<count;j++)
			if(a[i] > a[j])
				num++;
		c[i] = num;
	}
	for(i=0;i<count-1;i++)
		printf("%d ",c[i]);
	printf("%d",c[count-1]); 
}
