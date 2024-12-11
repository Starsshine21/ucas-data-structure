#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30

typedef struct NodeLink {
    int data; 	//邻接点在表头结点数组中的位置(下标)
    struct NodeLink *next; //指向下一个表结点
    int visit;
}NodeLink; // 表结点类型定义

typedef struct {
    // 图的顶点数、边数
    int vexnum,edgenum; 
    NodeLink *list[MAX_VERTEX_NUM];
}AGraph,*Graph;


void init_graph(Graph A)
{
    char c = ',';
    int i = 0;
    NodeLink *v, *p, *q;
    while (c == ',') 
	{
        c = getchar() - '0';
        getchar();
        v = (NodeLink *)malloc(sizeof(NodeLink));
        v->visit = 0;
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

int DFS(Graph A,int i, int j)
{
	NodeLink *p;
    for (p = A->list[i]; p; p = p->next) 
	{
        if (p->data == j)
            return 1;
        if(p->visit == 0)
        {
        	p->visit = 1;
        	return DFS(A, p->data, j);
		}
	}
    return 0;
}

int main()
{
	Graph A = (Graph)malloc(sizeof(AGraph));
	scanf("%d",&A->vexnum);
    memset(A->list, 0, sizeof(NodeLink *) * (A->vexnum + 1));
	init_graph(A);
	int i,j;
	scanf("%d, %d",&i,&j);
	if(DFS(A,i,j) == 1)
    	printf("yes");
	else
		printf("no");
}

