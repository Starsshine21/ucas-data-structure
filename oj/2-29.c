#include <stdio.h>
#include <stdlib.h>


typedef char ElemType;

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
		scanf("%c",&(p->data));
		q->next = p;
		q = p;
		if(getchar() == '\n')
			break;
	}
	q->next = NULL;
	return L;
}

int check(char d, LinkList B, LinkList C)
{
	int count = 0;
	LNode *b = B;
	
	LNode *c = C;
	while(b->next)
	{
		if(b->next->data == d)
		{
			count ++;
			break;
		}
		else
			b = b->next; 
	}
	while(c->next)
	{
		if(c->next->data == d)
		{
			count ++;
			break;
		}
		else
			c = c->next; 
	}
	if(count == 2)
		return 1;
	else
		return 0;
}

LinkList DELETE(LinkList A, LinkList B, LinkList C)
{
	LNode *p = A;
	int t;
	while(p->next)
	{
		t = check(p->next->data, B, C);
		if(t)
			p->next = p->next->next;
		else
			p = p->next;
	}
	return A;
	
}

int main()
{
	LinkList A,B,C,head;
	A = CreateList();
	B = CreateList();
	C = CreateList();
	
	DELETE(A,B,C);
	
	if(A->next==NULL)
		printf("NULL");
	else
	{
		for(head=A->next;head;head=head->next)
		{
			if(head->next==NULL)
				printf("%c",head->data);
			else
				printf("%c,",head->data);
		}
			
		return 0;
	}	
}
