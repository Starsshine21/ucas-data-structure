#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100  //栈空间初始分配量
#define INCREMENTSIZE 10  //栈空间分配增量

typedef  int Status;
typedef  int  ElemType ;
typedef struct { 
    	int top;    // 栈顶指针  
	ElemType  *base;  // 栈不存在时值为NULL     
	int   stacksize ;        // 当前已分配空间
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
	    //若栈已满，则增加INCREMENTSIZE个存储单元
	    s->base=(ElemType *)realloc(s->base,(s->stacksize + INCREMENTSIZE)*sizeof(ElemType));
	    if(!s->base) 
			return 1;
	    s->stacksize += INCREMENTSIZE;
	}
	s->base[s->top++] = e;  //e成为新的栈顶元素，栈顶指针加1
			         // 等于s->base[s->top]=e; s->top++；
	return 0;
}

Status Pop(SqStack *s)
{
	if(s->top==0) 
		return 1; //栈空，返回出错标志
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
	S = InitStack();
	char a;
	char e;
	int judge;
	while(1)
	{
		scanf("%c",&a);
		if(a == '&')
			break;
		Push(&S,a);
	}
	while(S.top > 0)
	{
		scanf("%c",&a);
		if(a == '@')
			break;
		if(GetTop(&S) == a)
			Pop(&S);
		else
			break;
	}
	if(S.top == 0 && getchar() == '@')
		printf("1");
	else
		printf("0");
}

