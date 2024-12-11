#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

void main()
{
	char c;
	int a,b;
	int i = 1;
	char A[MAXSIZE] = {0};
	int B[MAXSIZE] = {0};
	int C[MAXSIZE] = {0};
	int max = 1;
	while((i-1) != max || max == 0)
	{
		A[i] = getchar();
		scanf("%d",&B[i]);
		scanf("%d",&C[i]);
		if(B[i] > max)
			max = B[i];
		if(C[i] > max)
			max = C[i];
		i ++;
		c = getchar();
	}
	int count = i-1;
	int state = 0;
	for(i=1;i<=count;i++)
	{
		if(B[i] == -1 && C[i] != -1)
		{
			state = 1;
			break;
		}
		else if(B[i] != -1 && C[i] != -1)
			;
		else if(B[i] != -1 && C[i] == -1)
		{
			int j = 1;
			int k = 1;
			while(B[j] != i && j < count + 1)
				j++;
			while(C[k] != i && k < count + 1)
				k++;
			if(j > count)//左边没有，是右子树 
			{
				if(B[B[k]] != -1 && C[B[k]] != -1)
					state = 0;
				else
				{
					state = 1;	
					break;
				}
			}	
			else 
			{
				if(B[B[k]] == -1 && C[B[k]] == -1)
					state = 0;
				else
				{
					state = 1;	
					break;
				}
			}
		}
		else//空的
		{
			//是左子树，右子树为空；是右 
		 } 
	}
	if(state == 0)
		printf("YES");
	else
		printf("NO");
}





