#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

#define MAXSIZE 30

typedef struct BiTNode{
	int data;
	struct BiTNode * lchild, * rchild;
}BiTNode, *BiTree;

int num = 0;
BiTree create_A(int *A)
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	t->data = A[num++];
	if(A[num] != -1)
		t->lchild = create_A(A);
	else
	{
		t->lchild = NULL;
		num ++;
	}
	if(A[num] != -1)
		t->rchild = create_A(A);
	else
	{
		num ++;		
		t->rchild = NULL;
	}
	return t;
}

int num_B = 0;
BiTree create(int *A)
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	t->data = A[num_B++];
	if(A[num_B] != -1)
		t->lchild = create(A);
	else
	{
		t->lchild = NULL;
		num_B ++;
	}
	if(A[num_B] != -1)
		t->rchild = create(A);
	else
	{
		num_B ++;		
		t->rchild = NULL;
	}
	return t;
}

BiTree insert(BiTree a, int x)
{
	if(!a)
	{
		a = (BiTree)malloc(sizeof(BiTNode));
		a->data = x;
		a->lchild = a->rchild = NULL;
		return a;	
	}
	else
	{
		if(x <= a->data)
			a->lchild = insert(a->lchild,x);
		else
			a->rchild = insert(a->rchild,x);
		return a;
	}
}

BiTree combine(BiTree a, BiTree b)
{
	if(b)
	{
		combine(a,b->lchild);
		a = insert(a,b->data);
		combine(a,b->rchild);
	}
	return a;
}

int state = 1;
int printtree(BiTree t)
{
	if(t)
	{
		printtree(t->lchild);
		if(state)
		{
			printf("%d",t->data);
			state = 0;
		}
		else
			printf(" %d",t->data);
		printtree(t->rchild);
	}
	return 0;
}


int main()
{
	int A[MAXSIZE] = {-1};
	int B[MAXSIZE] = {-1};
	int i = 0;
	int number = 0;
	char c = '0';
	while(c != '\n')
	{
		if(isdigit(c = getchar()))
		{
			number = c - '0';
			while(isdigit(c=getchar()))
				number = number * 10 + c - '0';
			A[i++] = number;
		}
		else if(c == '-')
		{
			A[i++] = -1; 
			getchar();
			c = getchar();
		}	
	}
	c = ' ';
	int count_1 = i;
	i = 0;
	while(c != '\n')
	{
		if(isdigit(c = getchar()))
		{
			number = c - '0';
			while(isdigit(c=getchar()))
				number = number * 10 + c - '0';
			B[i++] = number;
		}
		else if(c == '-')
		{
			B[i++] = -1; 
			getchar();
			c = getchar();
		}	
	}
	int count_2 = i;
	BiTree a = create_A(A);
	BiTree b = create(B);
	BiTree t = combine(a,b);
	printtree(t);
	return 0;
}
