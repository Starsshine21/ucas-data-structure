#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


BiTree Pre_and_in(char *A,char *B ,int n){
	BiTree b;
	char *p;
	int k;
	if(n <= 0)
		return NULL;
	b = (BiTree)malloc(sizeof(BiTNode));
	b->data = *A;
	for(p = B;p < B+n;p++)
		if(*p == *A)
			break;
	k = p - B;//左子树节点数
	b->lchild = Pre_and_in(A+1,B,k);
	b->rchild = Pre_and_in(A+k+1,B+k+1,n-k-1);
	return b;
}

void postorder(BiTree t)
{
	if(!t)
		return;
	postorder(t->lchild);
	postorder(t->rchild);
	printf("%c",t->data);
} 


void main()
{
	char A[MAXSIZE] = {0};
	char B[MAXSIZE] = {0};
	char c;
	int count = 0;
	while((c=getchar()) != '\n')
		A[count++] = c;
	count = 0;
	while((c=getchar()) != '\n')
		B[count++] = c;
	BiTree t = Pre_and_in(A,B,count);
	postorder(t);
}
