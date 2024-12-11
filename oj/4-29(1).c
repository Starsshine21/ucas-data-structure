#include <stdio.h>
#include <stdlib.h>


typedef struct LNode{
	char chdata;
	struct LNode *next, *succ;
	int length;
}LNode, *LinkList;

LinkList InitLink()
{
	LinkList L; 
	L = (LNode *)malloc(sizeof(LNode));
	L->next = NULL;
	L->succ = NULL;
	L->length = 0;
	return L;	
}
LinkList CreateList()
{
	LNode *L, *q;
	L = (LNode *)malloc(sizeof(LNode));
	L->next = NULL;
	L->length = 0;
	q = L;
	LNode *p;
	char c;
	while(1)
	{
		p = (LNode *)malloc(sizeof(LNode));
		if((c=getchar()) == '\n')
			break;
		p->chdata = c;
		q->next = p;
		q = p;
		L->length ++;
	}
	q->next = NULL;
	return L;
} 

void GetNext (LinkList M)
{
 	int j, k;
 	LNode *p,*q;
	p = q = M->next;
	p->succ = M;
	if(M->length > 1) 
		p->next->succ = p;
	if(M->length > 2)
		if(p->chdata == p->next->chdata)
			p->next->next->succ = p->next;
		else
			p->next->next->succ = p;
	if(M->length > 1)
		p = p->next;
	while(p->next) 
	{
	 	if(q == M || q->chdata == p->chdata) 
		{
	    	p = p->next;
	    	q = q->next;
	 		p->succ = q;
		}
		else 
			q = q->succ;
	}
}



int check(LinkList L, LinkList M)
{
	int i,j;
	i = -1;
	LNode *p = L->next;
	LNode *q = M->next;
	while(p)
	{
		while(p->chdata == q->chdata)
		{
			i++;
			p = p->next;
			q = q->next;
			if(q == NULL)
				return (i-M->length+1);
			if(p == NULL)
				break;
		}
		if(q == M->next)
		{
			i++;
			p = p->next;
		}
		else
			q = q->succ;
	}
	return -1;
}

int main()
{
	int l1,l2;
	scanf("%d ",&l1);
	scanf("%d",&l2);
	getchar();
	LinkList L = CreateList();
	LinkList M = CreateList();
	if(l1>=l2)
	{
		GetNext(M);
		printf("%d",check(L,M));
	}
	else
		printf("-1");
	return 0;
}
