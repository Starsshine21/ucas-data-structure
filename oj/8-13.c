#include<stdio.h>
#include<stdlib.h>

typedef struct Space{
    int tag;
    int start;
    int size;
    struct Space *next;
}Space, *Spaceptr;

void CreateSpace(Spaceptr L)
{
    Spaceptr q = L;
    char c;
    while((c = getchar()) != '\n')
    {
    	getchar();
        Spaceptr p = (Spaceptr)malloc(sizeof(Space));
        p->tag = 0;
        scanf("%d %d",&p->start,&p->size);
        q->next = p;
        q = p;
        getchar();
    }
    q->next = NULL;
}

void InsertSpace(Spaceptr L)
{
    Spaceptr q = L->next;
    Spaceptr p = L;
    char c; 
    int start,size;
    while((c = getchar()) != EOF)
    {
        scanf(" %d %d",&start,&size);
        while(q->start + q->size < start)
		{
            p = q;
            q = q->next;
        }           
        if(q->start <= start)
            q->size = q->size + size;
        else if(q->start > start)
        {
            if(q->start <= start + size)
            {
                q->size = q->start - start + q->size;
                q->start = start;
            }
			else
			{
                Spaceptr r = (Spaceptr)malloc(sizeof(Space));
                r->start = start;
                r->size = size;
                r->tag = 0;
                p->next = r;
                r->next = q;
            }
        }
        getchar();
    }
    p = L->next;
	while(p->next)
	{
		if(p->start + p->size == p->next->start)
		{
			p->size = p->size + p->next->size;
			p->next = p->next->next;
		}
		else
			p = p->next;
	}
}

void PrintSpace(Spaceptr L)
{
    Spaceptr p = L->next;
    int state = 0;
    while(p)
    {
    	if(!state)
		{
    		printf("%d %d %d", p->tag, p->start, p->size);
    		state = 1;
		}
		else
    		printf("\n%d %d %d", p->tag, p->start, p->size);
        p = p->next;
    }
}

void main()
{
    Spaceptr L = (Spaceptr)malloc(sizeof(Space));
    CreateSpace(L);
    InsertSpace(L);
    PrintSpace(L);
}
