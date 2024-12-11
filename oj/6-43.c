#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

typedef struct BiTNode{
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree create(int i, int *M, int *N) 
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	if (i == 0)
		t = NULL;
	else 
	{
		t->data = i;
		t->lchild = create(M[i],M,N);
		t->rchild = create(N[i],M,N);
	}
	return t;
}

void exchange(BiTree t)
{
	BiTree temp;
	if (t != NULL) 
	{
		exchange(t->lchild);
		exchange(t->rchild);
		temp = t->lchild;
		t->lchild = t->rchild;
		t->rchild = temp;
	}
}

void putout(int *M,int *N, BiTree t)
{
	if(t != NULL)
	{
		int i = t->data;
		if(t->lchild)
		{
			M[i] = t->lchild->data;		
			putout(M,N,t->lchild);
		}
		if(t->rchild)
		{
			N[i] = t->rchild->data;
			putout(M,N,t->rchild);
		}
	}
	else
		t->data = 0;
}

void main() {
	int L[MAXSIZE] = {0};
	int M[MAXSIZE] = {0};
	int N[MAXSIZE] = {0};
	int l[MAXSIZE] = {0};
	int r[MAXSIZE] = {0};
	int count = 0;
	int a;
	char c = '0';
	int line = 0;
	while(line != 2)
	{
		scanf("%d",&a);
		L[count++] = a;
		if((c = getchar()) == '\n')
			line ++;
	}
	int i;
	for(i=0;i<(count/2);i++)
		M[i] = L[i];
	for(i = (count/2);i<count;i++)
		N[i - count/2] = L[i];	
	BiTree t = create(M[0],M,N);
	exchange(t);
	
	l[0] = r[0] = M[0];
	putout(l,r,t);
	for(i=0;i<(count/2 - 1);i++)
		printf("%d ",l[i]);
	printf("%d",l[count/2 - 1]);
	printf("\n");
	for(i=0;i<(count/2 - 1);i++)
		printf("%d ",r[i]);
	printf("%d",r[count/2 - 1]);
	
}

