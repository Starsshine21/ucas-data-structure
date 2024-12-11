#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30

typedef struct NodeLink {
    int data; 	//�ڽӵ��ڱ�ͷ��������е�λ��(�±�)
    struct NodeLink *next; //ָ����һ������
}NodeLink; // �������Ͷ���

typedef struct {
    // ͼ�Ķ�����������
    int vexnum,edgenum; 
    NodeLink *list[MAX_VERTEX_NUM];
}AGraph,*Graph;


void init_graph(Graph A)
{
    int i = 0, c;
    NodeLink *v, *p, *q;
    while (i < A->edgenum) 
	{
        scanf("%d",&c);
        getchar();
        v = (NodeLink *)malloc(sizeof(NodeLink));
        scanf("%d",&v->data);
        p = A->list[c];
        if (!p || p->data < v->data) {
            v->next = A->list[c];
            A->list[c] = v;
        } 
		else
		{
            while(p && p->data > v->data) 
			{
                q = p;
                p = p->next;
            }
            v->next = p;
            q->next = v;
        }
        c = getchar();
        i++;
    }
}

void print_graph(Graph A)
{
	int start_with = (A->list[0]) ? 0 : 1;
    int i;
    NodeLink *v;
    for (i = start_with; i <= A->vexnum + start_with - 1; i++)
	{
        if (A->list[i])
            printf("%d ", i);
        else
            printf("%d", i);
        for (v = A->list[i]; v; v = v->next) {
            if (v->next)
                printf("%d,", v->data);
            else
                printf("%d", v->data);
        }
        if(i < A->vexnum + start_with - 1)
        	putchar('\n');
    }
}

int main()
{
	Graph A = (Graph)malloc(sizeof(AGraph));
	scanf("%d",&A->vexnum);
	getchar();
	scanf("%d",&A->edgenum);
    memset(A->list, 0, sizeof(NodeLink *) * (A->vexnum + 1));
	init_graph(A);
    print_graph(A);
}

