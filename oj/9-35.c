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

int state = 0;
int printtree(BiTree t,int bottom, int top)
{
	if(t)
	{
		printtree(t->lchild,bottom,top);
		if(t->data < top && t->data > bottom)
		{
			if(state == 0)
			{
				state = 1;
				printf("%d",t->data);
			}
			else
				printf(" %d",t->data);
		}
		else
			state = 0;

		printtree(t->rchild,bottom,top);
	}
	return 0;
}

int main()
{
	int A[MAXSIZE] = {-1};
	int i = 0;
	int num = 0;
	char c = '0';
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
	int top,bottom;
	scanf("%d",&bottom);
	scanf("%d",&top);
	BiTree t = create(A,0,count-1);
	printtree(t,bottom,top);
	return 0;
}
