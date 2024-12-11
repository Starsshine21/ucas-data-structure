#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int state = 0;

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree create()
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	char ch = getchar();
	if(ch == '^')
		return NULL;
	else
	{
		t->data = ch;
		t->lchild = create();
		t->rchild = create();
        return t;
	}
}



BiTree Find(BiTree t,char p,char q)
{
	if(!t)
		return NULL;
	if(t->data == p||t->data == q) 
		return t;
	BiTree left = Find(t->lchild,p,q); 
	BiTree right = Find(t->rchild,p,q); 

	if(left!=NULL && right!=NULL) 
	{      
        state = 1;
		return t;			 
	}
	else if(left==NULL && right==NULL)	
		return NULL;
	else 
	{
		if(state == 0)
		{
			state = 1;
			return t;
		}
		else
		{
			if(left != NULL)
				return left; 
			else
				return right;
		}
	}					
} 

void main()
{
	BiTree t = create();
	getchar();
	char p = getchar();
	getchar();
	char q = getchar();
	BiTree u = Find(t,p,q);
	printf("%c",u->data);
}
