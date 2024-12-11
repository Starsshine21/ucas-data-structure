#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30

typedef struct NodeLink {
    int data; 	//邻接点在表头结点数组中的位置(下标)
    struct NodeLink *next; //指向下一个表结点
    int MPL;
}NodeLink; // 表结点类型定义

typedef struct {
    // 图的顶点数、边数
    int vexnum,edgenum; 
    NodeLink *list[MAX_VERTEX_NUM];
}AGraph,*Graph;

void init_graph(Graph A)
{
    int i = 0;
    int c;
    NodeLink *v, *p, *q;
    char ch = ',';
    while (ch == ',') 
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
        ch = getchar();
        i++;
    }
}

int path(Graph A, int i)
{
	
}

void main()
{
	Graph A = (Graph)malloc(sizeof(AGraph));
	scanf("%d",&A->vexnum);
	getchar();
	memset(A->list, 0, sizeof(NodeLink *) * (A->vexnum + 1));
	init_graph(A);
	for(i=1;i<A->vexnum;i++)
		printf("%d,",path(A,i));
	printf("%d",path(A,i+1));
}
