#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

int n = 0;

typedef struct BiTNode{
	int data;
	struct BiTNode *lchild, *rchild, *pred, *succ;
}BiTNode, *BiTree;

BiTree create(int *A, int *B, int *C, int i)
{
	
}

void main()
{
	int num;
	scanf("%d",&num);
	int i;
	int A[MAXSIZE] = {0};
	int B[MAXSIZE] = {0};
	int C[MAXSIZE] = {0};
	for(i=0;i<num;i++)
	{
		scanf("%d",&A[i]);
		scanf("%d",&B[i]);
		scanf("%d",&C[i]);
	}
	i = 0;
	BiTree t[MAXSIZE];
	while(n < num)
		t[i++] = create(A,B,C,n);
	int count = i;
}
