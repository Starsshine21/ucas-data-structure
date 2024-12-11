#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

typedef struct QNode{
	ElemType date;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct 
{
	QueuePtr rear;
}LinkQueue;

//循环队列构造函数,初始化空队列
LinkQueue CreateQueue()
{
	LinkQueue p;
	p.rear = (QNode*)malloc(sizeof(QNode));
	p.rear->next = p.rear;
	return p;
}


LinkQueue Insert_SqQueue(LinkQueue p,ElemType e)
{
	QNode *q;
	q = (QNode*)malloc(sizeof(QNode));
	q->date = e;
	q->next = p.rear->next;                    
	p.rear->next = q;                          
	p.rear = q;                                
	return p;
}


ElemType OutQueue(LinkQueue p)
{
	ElemType e;
	QNode *q;                                   
	q = p.rear->next;
	e = q->date;
	p.rear->next = q->next;
	return e;
}




int main()
{
	LinkQueue p;
	ElemType num;
	scanf("%d",&num);
	getchar();
	p = CreateQueue();		
	char a;
	int b;
	int i;
	for(i=0;i<num;i++)
	{
		scanf("%d",&b);
		a = getchar();
		p = Insert_SqQueue(p,b);			
	}
	b = OutQueue(p);
	for(i=0;i<num-1;i++)
	{
		b = OutQueue(p);
		printf("%d,",b);
	}
	b = OutQueue(p);
	printf("%d",b);
	return 0;
}

