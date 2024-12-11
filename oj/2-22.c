#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


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
	L->data = 0;
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

//LinkList reverse(LinkList L)
//{
//	LNode *p;
//	LinkList T;
//	int i = L->data;
//	for(i;i>0;i--)
//		T.data[L->data -i] = L.data[i];
//}
LinkList reverse(LinkList L){
    LNode *current_node, *next_node;
    current_node = L->next;
    L->next = NULL;
    while(current_node != NULL){
        next_node = current_node->next;
        current_node->next = L;
        L = current_node;
        current_node = next_node;   
    }
    return L; 
}

int main()
{
	LinkList L,head;
	L = CreateList();
	L = reverse(L);
	if(L->next==NULL)
		printf("NULL");
	else
	{
		for(head=L;head->next;head=head->next)
		{
			if(!head->next->data)
				printf("%c",head->data);
			else
				printf("%c,",head->data);
		}
	}
	return 0;
}
