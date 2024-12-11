#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int state = 0;

typedef struct BiTNode{
	char data;
	struct BiTNode *child, *brother;
}BiTNode, *BiTree;

BiTree create(char *A, int *B, int *C, int i)
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	t->data = A[i];
	if(B[i] == -1)
		t->child = NULL;	
	else
		t->child = create(A,B,C,B[i]);
	if(C[i] == -1)
		t->brother = NULL;
	else
		t->brother = create(A,B,C,C[i]);
	return t;
}

void printtree(BiTree t, int deep)
{
	int i;
	if(state == 0)
		state = 1;
	else
		printf("\n");
	for(i=0;i<deep;i++)
		printf("-");
	printf("%c",t->data);
	if(t->child)
		printtree(t->child,deep + 1);
		if(t->brother)
	printtree(t->brother,deep);
}


int main()
{
	char c;
	int a,b;
	int i = 1;
	char A[MAXSIZE] = {0};
	int B[MAXSIZE] = {0};
	int C[MAXSIZE] = {0};
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
	BiTree t = create(A,B,C,1);
	printtree(t,0);
	return 0;
}
