#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TElemType char


typedef struct BiTNode{       
    TElemType data;          
    struct BiTNode *lchild, *rchild;   
} BiTNode, *BiTree;

#define MAXSIZE 1000

//void create(int *L, int *R, int *C, int *D ,int i)
//{
//	
//	if(L[i] != -1)
//	{
//		D[2*i] = C[L[i]];
//		create(L,R,C,D,2*i);
//	}
//	else
//		D[2*1] = -1;
//	if(R[i] != -1)
//	{
//		D[2*i+1] = C[R[i]];
//		create(L,R,C,D,2*i+1);
//	}
//	else
//		D[2*i + 1] = -1;
//}

void create(int *L, int *R, int *D ,int i)
{
	
	if(L[i] > 0)
	{
		D[2*i] = 1;
		create(L,R,D,2*i);
	}
	else
		D[2*i] = -1;
	if(R[i] > 0)
	{
		D[2*i+1] = 1;
		create(L,R,D,2*i+1);
	}
	else
		D[2*i + 1] = -1;
}


void main()
{
	char c;
	int a,b;
	int i = 1;
	char A[MAXSIZE] = {0};
	int B[MAXSIZE] = {0};
	int C[MAXSIZE] = {0};
	int D[MAXSIZE] = {0};
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
	
	create(B,C,D,1);
	int state = 0;
	for(i=1;i<=count;i++)
	{
		if(D[i] == -1)
		{
			state = 1;
			break;
		}
	}
	if(state == 0)
		printf("Yes");
	else
		printf("No");
}
