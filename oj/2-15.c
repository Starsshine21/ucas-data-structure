#include <stdio.h>
#include <stdlib.h>


typedef int ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

LinkList InitLink()
{
	LinkList L; 
	L = (LNode *)malloc(sizeof(LNode));
	L->next = NULL;
	return L;	
} 

LinkList CreateList()
{
	LNode *L, *q;
	L = (LNode *)malloc(sizeof(LNode));
	L->next = NULL;
	q = L;
	LNode *p;
	while(1)
	{
		p = (LNode *)malloc(sizeof(LNode));
		scanf("%d",&(p->data));
		q->next = p;
		q = p;
		if(getchar() == '\n')
			break;
	}
	q->next = NULL;
	return L;
}

int main()
{
	int m,n;
	scanf("%d %d", &m, &n);
	LinkList A, B;
	A = CreateList();
	B = CreateList();
	LinkList ha, hb;
	ha = A;
	hb = B;
	int i;
	for(i=0;i<n;i++)
		hb = hb->next;
	hb->next = ha->next;
	
	for(hb=B->next;hb;hb=hb->next)
		printf("%d ",hb->data);
	return 0;
}
