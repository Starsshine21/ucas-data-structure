#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100 
#define INCREMENTSIZE 10 

typedef  int Status;
typedef  char  ElemType ;
typedef struct { 
    	int top;     
	ElemType  *base;      
	int   stacksize ;       
}SqStack ;

SqStack InitStack()
{
	SqStack s;
    s.base = (ElemType *)malloc(INITSIZE * sizeof(ElemType));
    s.stacksize=INITSIZE;
    s.top=0;
    return s;
}


Status Push(SqStack *s,ElemType e)
{
	if(s->top >= s->stacksize) 
	{ 
	    s->base=(ElemType *)realloc(s->base,(s->stacksize + INCREMENTSIZE)*sizeof(ElemType));
	    if(!s->base) 
			return 1;
	    s->stacksize += INCREMENTSIZE;
	}
	s->base[s->top++] = e;
	return 0;
}

Status Pop(SqStack *s, int t)
{
	s->top--; // ����s->top--; *e=s->base[s->top]; 
	return 0;
}

char GetTop(SqStack *s) 
{ 
	if(s->top==0) 
		return 1; // ջ�գ����س����־
	return s->base[s->top-1]; 
}

int main()
{
	int t = 0;
	SqStack S;
	S = InitStack();
	char x;
	while((x = getchar()) != '\n')
	{
		if(x == '(')
			Push(&S,x);
		else if(x == ')')
			Pop(&S,t);
		if(S.top < 0)
		{
			t = 1;
			break;
		}
	}
	if(t == 0 && S.top == 0)
		printf("1");
	else
		printf("0");
 } 
