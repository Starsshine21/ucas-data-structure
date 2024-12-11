#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define INFINITY 1000

typedef struct{
	int vexnum;//点数
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
}AGraph,*Graph;

int dist[MAX_VERTEX_NUM];
int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void Dijkstra(Graph g,int v0,int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int dist[]) 
{
	int i=0,j, v,w,min; 
	int final[MAX_VERTEX_NUM]; 
	for (v=1; v<=g->vexnum; v++) 
	{ //初始化
		final[v] = 0; 
		dist[v] = g->arcs[v0][v]; 
		for (w=0; w<g->vexnum; w++) 
			P[v][w] = 0; // 设空路径
	 	if (dist[v] < INFINITY)
		{ 
			P[v][v0] = 1;
			P[v][v] = 1; //起点和终点都要在 
		}
	}
	dist[v0] = 0; 
	final[v0] = 1; //初始化，v0顶点属于S集 
	for (i=2; i<=g->vexnum; i++)
	{ //其余g->vexnum-1个顶点
		min = INFINITY; //当前所知离v0顶点的最近距离
		for (w=0; w< g->vexnum; w++) 
			if (!final[w] & w != v0) //w顶点在V-S中 
				if (dist[w]<min) // w顶点离v0顶点更近
					{
						v = w;
						min = dist[w]; 
					}
		final[v] = 1; // 离v0顶点最近的v加入S集
		 //更新当前最短路径及距离
		for (w=1; w<=g->vexnum; w++)
	 		if (!final[w]&&(min+g->arcs[v][w] <dist[w]))
			{
				// 对w∈V-S，修改dist[w]和P[w]
				dist[w] = min + g->arcs[v][w]; 
				for(j=0;j<g->vexnum;j++)
					P[w][j] = P[v][j];  //第v行赋值于第w行
				P[w][w] = 1;// P[w] = P[v]+[w]
			}
	}
}

int main()
{
	Graph G = (Graph)malloc(sizeof(AGraph));
	int v0;
	scanf("%d %d",&G->vexnum,&v0);
	getchar();
	char c;
	int i,j;
	int weight;
	for(i=1;i<=G->vexnum;i++)
		for(j=1;j<=G->vexnum;j++)
			G->arcs[i][j] = INFINITY;
	while((c=getchar()) != EOF)
	{
		i = c - '0';
		scanf("-%d %d",&j,&weight);
		G->arcs[i][j] = weight;
		c = getchar();
	}
	Dijkstra(G,v0,P,dist);
	if(G->vexnum != v0)
	{
		for(i=1;i<G->vexnum;i++)
			if(i != v0)
				printf("%d,",dist[i]);
		printf("%d",dist[G->vexnum]);
	}
	else
	{
		for(i=1;i<G->vexnum-1;i++)
			if(i != v0)
				printf("%d,",dist[i]);
		printf("%d",dist[G->vexnum-1]);
	}
}

