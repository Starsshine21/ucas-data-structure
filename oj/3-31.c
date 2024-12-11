#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100 
#define INCREMENTSIZE 10 

typedef  int Status;
typedef  char  ElemType ;
typedef struct { 
    int top,bottom;     
	ElemType  *base;      
	int   stacksize ;       
}SqStack ;

SqStack InitStack()
{
	SqStack s;
    s.base = (ElemType *)malloc(INITSIZE * sizeof(ElemType));
    s.stacksize=INITSIZE;
    s.top = s.bottom = 0;
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
	s->top--; // 等于s->top--; *e=s->base[s->top]; 
	return 0;
}

char GetTop(SqStack *s) 
{ 
	if(s->top==0) 
		return 1; // 栈空，返回出错标志
	return s->base[s->top-1]; 
}

int main()
{
	SqStack S;
	char c;
	int t = 0;
	S = InitStack();
	while((c=getchar()) != '@')
		Push(&S,c);
	S.top -= 1;
	while(S.bottom <= S.top)
	{
		if(S.base[S.bottom] == S.base[S.top])
		{
			S.bottom ++;
			S.top --;
		}
		else
		{
			t = 1;
			break;
		}
	}
	if(t == 1)
		printf("0");
	else
		printf("1");
}
