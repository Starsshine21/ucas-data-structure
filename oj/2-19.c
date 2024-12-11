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


LinkList DELETE(LinkList L,int m,int n)
{
	LNode *p = L;
	
	while(p->next)
	{
		if(p->next->data > m && p->next->data < n)
			p->next = p->next->next;
		else
			p = p->next;
	}
	
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
	LinkList L, head;
	L = CreateList();
	scanf("%d %d", &m, &n);
	
	L = DELETE(L,m,n);
	
	if(L->next==NULL)
		printf("NULL");
	
	else
	{
		for(head=L->next;head;head=head->next)
			printf("%d ",head->data);
		return 0;
	}		
}
