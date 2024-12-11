#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSTRLEN 100

typedef struct str{
    char ch[INITSTRLEN];
    int length;
}STR,*SString;

SString StrCreate()
{
	SString s;
	s = (SString)malloc(sizeof(STR));
	char x;
	int i = 0; 
	s->length = 0;
	while((x=getchar())!= ' ' && x != '\n')
		s->ch[i++] = x;
	s->length = i;
	return s; 
}

int StrCompare(SString S, SString T)
{
	int i = 0;
	while(S->length > 0 && T->length > 0)
	{
		if(S->ch[i] == T->ch[i])
		{
			S->length--;
			T->length--;
			i++;
		}
		else if(S->ch[i] > T->ch[i])
			return 1;
		else
			return -1;
	}
	if(S->length == T->length == 0)
		return 0;
	else if(S->length == 0 && T->length > 0)
		return -1;
	else if(S->length > 0 && T->length == 0)
		return 1;
}

int main()
{
	SString S = StrCreate();
	SString T = StrCreate();
	int i;
	i = StrCompare(S,T);
	printf("%d",i);
}
