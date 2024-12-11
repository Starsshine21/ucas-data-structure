#include <stdio.h>
#include <stdlib.h>

typedef struct letter
{
    char w;            //��ĸ
    int count;         //���ִ���
    struct Node *next; //ָ����һ�����
}Letter;

typedef struct Node
{
    Letter ac[27]; //A~Z��$
}Node, *LinkNode;

void InitialNode(Node *L)
{
    int i;
    L->ac[0].w = '$';
    L->ac[0].count = 0;
    L->ac[0].next = NULL;
    for (i = 1; i < 27; i++)
    {
        L->ac[i].w = 'a' + i - 1;
        L->ac[i].count = 0;
        L->ac[i].next = NULL;
    }
}

void InsertWord(Node *L)
{
    int depth, caldepth = 0, pos;
    Node *p, *q;
    char c;
    scanf("%d", &depth);
    c = getchar();
    while ((c = getchar()) != '\n')
    {
    	caldepth = 0;
    	q = L;
        while (c != ';' && c != '\n' && caldepth < depth)
        {
            pos = c - 'a' + 1;
            if (q->ac[pos].next == NULL)
            {
                p = (Node *)malloc(sizeof(Node));
                InitialNode(p);
                q->ac[pos].next = p;
            }
            else
                p = q->ac[pos].next;
            q->ac[pos].count++;
            c = getchar();
            q = p;
            caldepth++;
        }
        if (c != ';')
        {
        	if(c == '\n'){
        		q->ac[0].count++;
        		break;
			}		
            pos = c - 'a' + 1;
            q->ac[pos].count++;
            while ((c = getchar()) != ';' && c != '\n')
                ;
            if(c == '\n')
            	break;
        }
        else
            q->ac[0].count++;
    }
}

int FindElem(Node *L)
{
    int count = 0, i;
    for (i = 0; i < 27; i++)
    {
        if (L->ac[i].count != 0)
            count += L->ac[i].count;
    }
    return count;
}

int printstate = 0;
void Traverse(Node *L)
{
    Node *p;
    int i;
    for (i = 1; i < 27; i++)
    {
        if (L->ac[i].next != NULL)
        {
        	if(printstate == 0)
        	{
        		printf("%d", FindElem(L->ac[i].next));
        		printstate = 1;
			}else
				printf(",%d", FindElem(L->ac[i].next));
            
            Traverse(L->ac[i].next);
        } 
    }  
}

int main()
{
    LinkNode L = (LinkNode)malloc(sizeof(Node));
    char c;
    while(c != EOF)
    {
    	if(c == '1')
    		insert(L);
    	else if(c == '2')
    		Delete(L);
    	else
    		find(L);
	}
    return 0;
}
