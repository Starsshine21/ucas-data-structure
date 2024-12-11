#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 30

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;

BiTree create(int *A, int *B, int *C, int i)
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	t->data = A[i];
	if(B[i] == -1)
		t->lchild = NULL;	
	else
		t->lchild = create(A,B,C,B[i]);
	if(C[i] == -1)
		t->rchild = NULL;
	else
		t->rchild = create(A,B,C,C[i]);
	return t;
}

int state = 1;
int Judge(BiTree t)
{
	if(t == NULL)
		return 1;
	if(t->lchild)
	{
		if(t->data > t->lchild->data)
			state = Judge(t->lchild);
		else
			state = 0;
	}
	if(t->rchild)
	{
		if(t->data < t->rchild->data)
			state = Judge(t->rchild);
		else
			state = 0;			
	}
	return state;
}

int main(void)
{
    int i = 0;
	int A[MAXSIZE] = {0};
	int B[MAXSIZE] = {0};
	int C[MAXSIZE] = {0};
	int max = 1;
	while((i-1) != max || max == 0)
	{
		scanf("%d",&A[i]);
		scanf("%d",&B[i]);
		scanf("%d",&C[i]);
		if(B[i] > max)
			max = B[i];
		if(C[i] > max)
			max = C[i];
		i ++;
	}
    BiTree t = create(A,B,C,0); 
    printf("%d", Judge(t));
    return 0;
}

