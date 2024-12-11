#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 40

typedef struct NodeLink {
	int num;
    char data; 	//邻接点在表头结点数组中的位置(下标)
    struct NodeLink *next; //指向下一个表结点
}NodeLink; // 表结点类型定义

typedef struct {
    // 图的顶点数、边数
    int vexnum,edgenum; 
    NodeLink *list[MAXSIZE];
}AGraph,*Graph;

int note = 0;
char result[MAXSIZE];

int TraverseGraph(Graph G, int i)
{
	NodeLink *p, *q;
	result[note] = G->list[i]->data; 
	note++;
	if(G->list[i]->data >= 'a' && G->list[i]->data <= 'z')
		return;
	p = G->list[i]->next;
	while(p)
	{
		TraverseGraph(G, p->num);
		p = p->next;
	}
	return 0;
}

int main()
{
	Graph G = (Graph)malloc(sizeof(AGraph));
	int i;
	char c;
	NodeLink *p, *q;
	scanf("%d",&G->vexnum);
	getchar();
	for(i=0;i<G->vexnum;i++)
	{
		G->list[i] = (NodeLink *)malloc(sizeof(NodeLink));
		G->list[i]->num = i;
		G->list[i]->next = NULL;
	}
	for(i=0;i<G->vexnum;i++)
	{
		G->list[i]->data = getchar();
		while((c = getchar())!= '\n')//行内处理 
		{
			if(c >= '0' && c <= '9')
			{
				p = (NodeLink *)malloc(sizeof(NodeLink));
				p->num = c - '0';
				p->next = NULL;
				q = G->list[i];
				while(q->next)
					q = q->next;
				q->next = p;
			}
		}
	}
	TraverseGraph(G, 0);
	for(i=note-1; i>=0; i--)
		printf("%c", result[i]);
	return 0;
}
