#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 30
#define MAXSIZE 30

typedef struct NodeLink {
    int data; 	//�ڽӵ��ڱ�ͷ��������е�λ��(�±�)
    struct NodeLink *next; //ָ����һ������
    int indegree;
}NodeLink; // �������Ͷ���

typedef struct {
    // ͼ�Ķ�����������
    int vexnum,edgenum; 
    NodeLink *list[MAX_VERTEX_NUM];
}AGraph,*Graph;


void init_graph(Graph A, int s[], int fst[], int lst[])
{
	int i,j;
	NodeLink *q, *p;
	for(i=1;i<=A->vexnum;i++)
	{
		A->list[i] = (NodeLink *)malloc(sizeof(NodeLink));
		A->list[i]->next = NULL;
		A->list[i]->indegree = 0;
	}
	for(i=1;i<=A->vexnum;i++)
	{
		if(fst[i] < lst[i])
		{
			for(j=fst[i];j<lst[i];j++)
			{
				NodeLink *v = (NodeLink *)malloc(sizeof(NodeLink));
				v->data = s[j];
				p = A->list[i];		
	            while(p->next) 
	                p = p->next;
	            v->next = p->next;
	            p->next = v;
		       	A->list[s[j]]->indegree ++;
			}
		}
	}
}

int Judgecycle(Graph A)
{
	int top = 0;
	int stack[A->vexnum];
	int i;
	for(i=A->vexnum-1;i>=0;i--)  	//for(i=0;i<g->vexnum;i++)
    {
	    if(A->list[i]->indegree == 0) 	//���Ϊ0�߽�ջ
		{
			stack[top] = i; 
			top++;
		}
	}
	int count = 0; // ������������
	NodeLink *p;
	while (top != 0) 
	{
    	top--; 
		i = stack[top]; 
		count ++;
		int j;
    	for(p=A->list[i];p;p=p->next)
		{
       		j = p->data; //��i�Ŷ����ÿ���ڽӵ����ȼ�1
        	if(--A->list[j]->indegree == 0)
			{ //����ȼ�Ϊ0������ջ
				stack[top] = j; 
				top++;
			}
        }
	} //while
	if(count < A->vexnum) 
		return 1; //��ͼ�л�·
	else 
		return 0;
}

void main()
{
	Graph A = (Graph)malloc(sizeof(AGraph));
	scanf("%d",&A->vexnum);
	int s[MAXSIZE];
	int fst[A->vexnum+1];
	int lst[A->vexnum+1];
	int num;
	int i = 1;
	scanf("%d",&num);
	scanf("%d",&num);
	s[0] = 0;
	while(num != 0)
	{
		s[i++] = num;
		scanf("%d",&num);
	}
	fst[0] = 0;
	for(i=1;i<=A->vexnum;i++)
		scanf("%d",&fst[i]);
	for(i=0;i<=A->vexnum;i++)
		scanf("%d",&lst[i]);
	memset(A->list, 0, sizeof(NodeLink *) * (A->vexnum + 1));
	init_graph(A,s,fst,lst);
	int state = Judgecycle(A);
	if(state == 1)
		printf("yes");
	else
		printf("no");
}
