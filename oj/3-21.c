#include <stdio.h>
#include <stdlib.h>

#define OPSETSIZE 7 
#define INITSIZE 100
#define ElemType char
#define INCREMENTSIZE 5

typedef struct { 
    int top;      
	char  *base;     
	int   stacksize ;       
}SqStack ;

SqStack InitStack()
{
	SqStack s;
    s.base = (char *)malloc(INITSIZE * sizeof(char));
    s.stacksize=INITSIZE;
    s.top=0;
    return s;
}

char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'}; 

unsigned char Prior[OPSETSIZE][OPSETSIZE] = { 
 {'<','<','<','<',' ',' ',' '},
 {'<','<','<','<',' ',' ',' '},
 {'>','>','<','<',' ',' ',' '},
 {'>','>','<','<',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' '},
 {' ',' ',' ',' ',' ',' ',' '}, 
 {' ',' ',' ',' ',' ',' ',' '}};
 
int In(char Test, char* TestOp)
{
	int i;
	for (i=0; i< OPSETSIZE; i++) 
		if (Test == TestOp[i]) 
			return 0; 
	return 1; 
} 

int ReturnOpOrd(char op, char* TestOp) 
{ 
	int i;
	for(i=0; i< OPSETSIZE; i++) 
		if (op == TestOp[i]) 
			return i;  
	return 0;
}

char precede(char Aop, char Bop)
{ 
	return Prior[ReturnOpOrd(Aop,OPSET)][ReturnOpOrd(Bop,OPSET)]; 
}

int Push(SqStack *s, char e)
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

char Pop(SqStack *s)
{
	s->top--; // µÈÓÚs->top--; *e=s->base[s->top]; 
	return s->base[s->top];
}

char Gettop(SqStack *s)
{
	return s->base[s->top-1];
}

int main()
{
	SqStack S = InitStack();
	char a;
	while((a=getchar()) != '\n')
	{
		if(In(a,OPSET) == 0)
		{
			if(a == '(')
				Push(&S,a);
			else if(a == ')')
			{
				while(S.base[S.top-1]!= '(')
					printf("%c",Pop(&S));
				Pop(&S);	
			}
			else 
			{
				if(S.top > 0)
				{
					while((precede(a,Gettop(&S)) == '<' || precede(a,Gettop(&S)) == '=') && S.top > 0)
						printf("%c",Pop(&S));
					Push(&S,a);
				}
				else
					Push(&S,a);
			}
		}
		else
			printf("%c", a);
	}
	while(S.top > 0)
		printf("%c",Pop(&S));
}
