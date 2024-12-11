#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree create()
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	char c = getchar();
	if(c != '#')
	{
		t->data = c;
		t->lchild = create();
		t->rchild = create();
	}
	else
	{
		t->data = c;
		t->lchild = NULL;
		t->rchild = NULL;
	}
	return t;
}

void printtree(BiTree t,int i,int k)
{
	int j = -1;
	if(t->data=='*' || t->data=='/')
		j = 1;
	else if(t->data=='+' || t->data=='-')
		j = 0;
	int state = (((j==0&&i==1)||(j==0&&i==0)||(j==1&&i==1))&&k==1)||(j==0&&i==1&&k==0);
	if(state == 1)
		printf("(");
	if(t->lchild)
		printtree(t->lchild,j,0);
	if(t->data != '#')
		printf("%c",t->data);
	if(t->rchild)
		printtree(t->rchild,j,1);
	if(state == 1)
		printf(")");
	return;
}

void main()
{
	BiTree t = create();
	printtree(t,-1,0);
}


 

