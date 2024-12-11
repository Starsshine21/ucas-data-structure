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


LinkList DELETE(LinkList L,int i)
{
	int j;
	LNode *p;
	p = L;
	if(i == 0)
		L = p->next;
	else
	{
		for(j=0;j<i;j++)
			p = p->next;
		p->next = p->next->next;
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
	int i;
	LinkList L, head;
	L = CreateList();
	scanf("%d", &i);
	L = DELETE(L,i);
	if(L->next==NULL)
		printf("NULL");
	
	else
	{
		for(head=L->next;head;head=head->next)
			printf("%d ",head->data);
		return 0;
	}		
}
