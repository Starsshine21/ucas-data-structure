#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1000

typedef struct BiTNode{       
    int data;          
    struct BiTNode *lchild, *rchild;   
} BiTNode, *BiTree;



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

BiTree newcreate(int i, int *M, int *N) 
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	if (i == 0)
		t = NULL;
	else
	{
		t->data = i;
		t->lchild = newcreate(M[i-M[0]+1],M,N);
		t->rchild = newcreate(N[i-N[0]+1],M,N);
	}
	return t;
}


void printtree(BiTree t)
{
	if(t->lchild)
		printtree(t->lchild);
	printf("%d ",t->data);
	if(t->rchild)
		printtree(t->rchild);
}

BiTree Insert_tree(BiTree t,int insert)
{
	if(t->data == insert)
		return t;
	else
	{
		if(Insert_tree(t->lchild,insert))
			return Insert_tree(t->lchild,insert);
		else
			return Insert_tree(t->rchild,insert);
	}
}

void main()
{
	int L[MAXSIZE] = {0};
	int R[MAXSIZE] = {0};
	int M[MAXSIZE] = {0};
	int N[MAXSIZE] = {0};
	int count = 0;
	int a;
	char c;
	while(1)
	{
		scanf("%d",&a);
		L[count++] = a;
		if((c = getchar()) == '\n')
			break;
	}
	count = 0;
	while(1)
	{
		scanf("%d",&a);
		R[count++] = a;
		if((c = getchar()) == '\n')
			break;
	}
	count = 0;
	
	int insert;
	scanf("%d",&insert);
	
	while(1)
	{
		scanf("%d",&a);
		M[count++] = a;
		if((c = getchar()) == '\n')
			break;
	}
	count = 0;
	while(1)
	{
		scanf("%d",&a);
		N[count++] = a;
		if((c = getchar()) == '\n')
			break;
	}
	
	BiTree t = create(L[0],L,R);//原来的树
	BiTree u = newcreate(M[0],M,N);//插入的树 
	BiTree p = Insert_tree(t,insert);
	if(p->lchild)
	{
		u->rchild = p->lchild;	
		p->lchild = u;
	}	
	else
		p->lchild = u;
	printtree(t);
}
