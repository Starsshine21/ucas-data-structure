#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 30

typedef struct BiTNode{
	int data;
	struct BiTNode * lchild, * rchild;
}BiTNode, *BiTree; 

BiTree create(int *A,int a, int b)
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	int mid = (a + b) / 2;
	t->data = A[mid];
	if(mid == a)
	{
		if(a == b)
		{
			t->lchild = t->rchild = NULL;
			return t;
		}
		else
		{
			t->lchild = NULL;
			t->rchild = create(A,b,b);
			return t;
		}
	}
	else
	{
		t->lchild = create(A,a,mid-1);
		t->rchild = create(A,mid+1,b);
		return t;
	}
}

int state = 1;
int printtree(BiTree t,int standard)
{
	if(t)
	{
		printtree(t->rchild,standard);
		if(t->data == standard)
		{
			printf("%d",t->data);
			state = 0;
		}
		else if(t->data < standard)
			state = 0;
		if(state)
			printf("%d ",t->data);
		printtree(t->lchild,standard);
	}
	return 0;
}

int main()
{
	int A[MAXSIZE] = {-1};
	int i = 0;
	int num = 0;
	char c;
	while(c != '\n')
	{
		if(isdigit(c = getchar()))
		{
			num = c - '0';
			while(isdigit(c=getchar()))
				num = num * 10 + c - '0';
			A[i++] = num;
		}
		else if(c == '-')
		{
			c = getchar();
			num = c - '0';
			while(isdigit(c=getchar()))
			num = num * 10 + c - '0';
			A[i++] = num * -1;
		}	
	}
	int count = i;
	int standard;
	scanf("%d",&standard);
	BiTree t = create(A,0,count-1);
	printtree(t,standard);
	return 0;
}
