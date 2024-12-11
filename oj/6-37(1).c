#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000
#define  INCREMENTSIZE 5
#define INITSIZE 100

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


typedef  char  ElemType ;
typedef struct SqStack{ 
    int top;     
	BiTree  *base;      
	int   stacksize ;      
}SqStack ;

SqStack InitStack()
{
	SqStack s;
    s.base = (BiTree*)malloc(INITSIZE * sizeof(BiTree));
    s.stacksize=INITSIZE;
    s.top=0;
    return s;
}


int Push(SqStack *s,BiTree e)
{
	if(s->top >= s->stacksize) 
	{ 
	    s->base = (BiTree*)realloc(s->base,(s->stacksize + INCREMENTSIZE)*sizeof(BiTree));
	    if(!s->base) 
			return 1;
	    s->stacksize += INCREMENTSIZE;
	}
	s->base[s->top++] = e; 
	return 0;
}

int Pop(SqStack *s, BiTree *p)
{
	if(s->top==0) 
		return 1; //栈空，返回出错标志
	s->top--;
	*p = s->base[s->top];
	return 0;
}

BiTree create(int *L, int *R, char *C , int i)
{
	BiTree t = (BiTree)malloc(sizeof(BiTNode));
	t->data = C[i];
	if(L[i] != -1)
		t->lchild = create(L,R,C,L[i]);
	else
		t->lchild = NULL;
	if(R[i] != -1)
		t->rchild = create(L,R,C,R[i]);
	else
		t->rchild = NULL;
	return t;
}


void preorder(BiTree t)
{
    SqStack S; 
    S = InitStack(S);
    int i = 0;
    BiTree p = t;
    char temp= t->data; 
    Push(&S,p);
    while(1)
    {
	    if(p)
	    {
	   		printf("%c ",p->data);   
	   		if(p->rchild != NULL) 
			   	Push(&S,p->rchild);
	   		p=p->lchild;
	    }
	   	else
	   		Pop(&S,&p); 
	   	if(S.top == 0) 
	   		break;
	}
}

void main()
{
	char C[MAXSIZE];
	int L[MAXSIZE] = {0};
	int R[MAXSIZE] = {0};
	int count = 0;
	char c;
	int  max = 1;
	int i = 1;
	while((i-1) != max)
	{
		C[i] = getchar();
		scanf("%d",&L[i]);
		scanf("%d",&R[i]);
		if(L[i] > max)
			max = L[i];
		if(R[i] > max)
			max = R[i];
		i ++;
		c = getchar();
	}
	BiTree t = create(L,R,C,1);
	preorder(t);
}
