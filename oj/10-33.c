#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 30

typedef struct LNode{
	int data;
	struct LNode* next;
}LNode, *LinkList;

void Select(LinkList p)
{
	int min = p->next->data;
	LinkList t = p;
	if(!p->next->next)
	{
		printf("%d",min);
		return;
	}
	while(p->next)
	{
		if(p->next->data < min)
		{
			min = p->next->data;
			t = p;
		}
		p = p->next;
	}
	printf("%d ",min);
	t->next = t->next->next;
	return;
}

int main()
{
	LinkList L = (LinkList)malloc(sizeof(LNode));
	LinkList q = L;
	char c = ' ';
	int count = 0;
	while(c != '\n')
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->next = NULL;
		q->next = p;
		q = p;
		c = getchar();
		count ++;
	}
	int i;
	for(i=0;i<count;i++)
		Select(L);	
	
	return 0;
}
