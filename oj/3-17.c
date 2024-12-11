#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100  //ջ�ռ��ʼ������
#define INCREMENTSIZE 10  //ջ�ռ��������

typedef  int Status;
typedef  int  ElemType ;
typedef struct { 
    	int top;    // ջ��ָ��  
	ElemType  *base;  // ջ������ʱֵΪNULL     
	int   stacksize ;        // ��ǰ�ѷ���ռ�
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
	    //��ջ������������INCREMENTSIZE���洢��Ԫ
	    s->base=(ElemType *)realloc(s->base,(s->stacksize + INCREMENTSIZE)*sizeof(ElemType));
	    if(!s->base) 
			return 1;
	    s->stacksize += INCREMENTSIZE;
	}
	s->base[s->top++] = e;  //e��Ϊ�µ�ջ��Ԫ�أ�ջ��ָ���1
			         // ����s->base[s->top]=e; s->top++��
	return 0;
}

Status Pop(SqStack *s)
{
	if(s->top==0) 
		return 1; //ջ�գ����س����־
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

