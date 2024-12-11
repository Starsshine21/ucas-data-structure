#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 20

typedef struct NodeLink{
    int pos;
    struct NodeLink *next;
}NodeLink;

typedef struct{
    struct{
        int index;
        NodeLink *first;
    }v[MAXSIZE];
}SpaceList;

void PrintSpace(SpaceList *S)
{
	NodeLink *p;
	int i;
	int state = 0;
	for(i=0; i<MAXSIZE; i++)
	{
		if(S->v[i].first->next != NULL)
		{
			p = S->v[i].first;
			if(state == 0)
			{
				printf("%d ", S->v[i].index);
				state = 1;
			}else
				printf("\n%d ", S->v[i].index);
			while(p->next != NULL)
			{
				if(p->next->next == NULL)
					printf("%d", p->next->pos);
				else
					printf("%d ", p->next->pos);
				p = p->next;
			}

		}
	}
}

void InsertSpace(SpaceList S, int i, int insertpos)
{
	NodeLink *p, *pre, *q;
	p = S.v[i].first->next;
    pre = S.v[i].first;
	
	if(p != NULL)
   	while(insertpos > p->pos){
   		pre = p;
    	p = p->next;
    	if(p == NULL)
    		break;
	}
    q = (NodeLink *)malloc(sizeof(NodeLink));
   	q->pos = insertpos;
   	pre->next = q;
   	q->next = p;
}

void InOrder(SpaceList *S)
{
	int i, j;
	int interval;
	NodeLink *p, *pre;
	for(i=0; i<MAXSIZE; i++)
	{
		if(S->v[i].first->next != NULL)
		{
			interval = pow(2,S->v[i].index);
			p = S->v[i].first->next;
			pre = S->v[i].first;
			while(p->next != NULL)
			{
				if(p->next->pos - p->pos == interval && (p->pos % (int)pow(2,i+1)== 0))
				{
					InsertSpace(*S, i+1, p->pos);
					pre->next = p->next->next;
					p = p->next->next;
					if(p == NULL)
						break;
				}
				else
				{
					pre = p;
					p = p->next;
				}
			}
		}
	}
}

int main()
{
    SpaceList S;
    NodeLink *p, *q;
    p = q = NULL;
    int i;
    for(i=0; i<MAXSIZE; i++)
    {
        S.v[i].first = (NodeLink *)malloc(sizeof(NodeLink));
        S.v[i].first->pos = 0;
        S.v[i].first->next = NULL;
        S.v[i].index = i;
    }
    char c;
    int index;
    while((c = getchar()) != '\n')
    {
        index = c - '0';
        i = index;
        q = S.v[i].first;
        while((c = getchar()) != '\n')
        {	
            if(c == ' ')
            {
                p = (NodeLink *)malloc(sizeof(NodeLink));
                scanf("%d", &p->pos);
                q->next = p;
                q = p;
                p->next = NULL;
            }
        }
    }
    
    int insertpos;
    i = 0;
    while((c = getchar()) != EOF)
    {
    	index = c - '0';
    	i = index;
    	while((c = getchar()) != '\n')
    	{
    		if(c == ' ')
    		{
    			scanf("%d", &insertpos);
    			InsertSpace(S, i, insertpos);	
			}
		}
	}
	
	InOrder(&S);
	PrintSpace(&S);
	
	return 0;
}
