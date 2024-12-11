#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define INFINITY 1000

typedef struct{
	int vexnum;//����
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
}AGraph,*Graph;

int dist[MAX_VERTEX_NUM];
int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void Dijkstra(Graph g,int v0,int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int dist[]) 
{
	int i=0,j, v,w,min; 
	int final[MAX_VERTEX_NUM]; 
	for (v=1; v<=g->vexnum; v++) 
	{ //��ʼ��
		final[v] = 0; 
		dist[v] = g->arcs[v0][v]; 
		for (w=0; w<g->vexnum; w++) 
			P[v][w] = 0; // ���·��
	 	if (dist[v] < INFINITY)
		{ 
			P[v][v0] = 1;
			P[v][v] = 1; //�����յ㶼Ҫ�� 
		}
	}
	dist[v0] = 0; 
	final[v0] = 1; //��ʼ����v0��������S�� 
	for (i=2; i<=g->vexnum; i++)
	{ //����g->vexnum-1������
		min = INFINITY; //��ǰ��֪��v0������������
		for (w=0; w< g->vexnum; w++) 
			if (!final[w] & w != v0) //w������V-S�� 
				if (dist[w]<min) // w������v0�������
					{
						v = w;
						min = dist[w]; 
					}
		final[v] = 1; // ��v0���������v����S��
		 //���µ�ǰ���·��������
		for (w=1; w<=g->vexnum; w++)
	 		if (!final[w]&&(min+g->arcs[v][w] <dist[w]))
			{
				// ��w��V-S���޸�dist[w]��P[w]
				dist[w] = min + g->arcs[v][w]; 
				for(j=0;j<g->vexnum;j++)
					P[w][j] = P[v][j];  //��v�и�ֵ�ڵ�w��
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

