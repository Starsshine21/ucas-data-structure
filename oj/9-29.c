#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 30

typedef struct LinkNode{
	int data;
	struct LinkNode *next;
}LinkNode, *LinkList;

int i = 0;
int A[MAXSIZE] = {0};
LinkList CreateList()
{
	LinkList L = (LinkNode*)malloc(sizeof(LinkNode));
	LinkList q = L;
	char c ;
	int num;
	while(c != '\n')
	{
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		c = getchar();
		num = c - '0';
		c = getchar();
		while(isdigit(c))
		{
			c = getchar();
			num = num * 10 + c - '0';
		}
		p->data = num;
		q->next = p;
		q = p;
	}
	return L;
}

LinkList Judge(LinkList h, LinkList t, int num)
{
	LinkList p;
	if(num == t->data)
	{
		A[i++] = 1;
		return t;
	}
	else if(num > t->data)
	{
		p = t;
	}
	else
	{
		p = h;
	}
	while(p->data < num && p->next)
		p = p->next;
	if(p->data == num)
		A[i] = 1;
	else
		A[i] = 0;
	i++;
	return t;
}

int main()
{
	LinkList L = CreateList();
	LinkList h = L->next;
	LinkList t = L->next;
	char c;
	while(c != '\n')
	{
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		c = getchar();
		int num = c - '0';
		c = getchar();
		while(isdigit(c))
		{
			c = getchar();
			num = num * 10 + c - '0';
		}
		t = Judge(h,t,num);
	}
	int count = i;
	for(i=0;i<count-1;i++)
		printf("%d ",A[i]);
	printf("%d",A[count - 1]);
}
