#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSTRLEN 100

int len = 0;
typedef struct str{
    char ch[INITSTRLEN];
    int length;
}STR,*SString;


SString StrInit()
{
	SString s;
	s = (SString)malloc(sizeof(STR)); 
	char x;
	int i = 0;
	s->ch[0]='\0'; 
	s->length = 0; 
	while((x=getchar())!= '\n' && x != ' ')
		s->ch[i++] = x;
	s->length = i;
	return s; 
}

int find(SString S,SString T)
{
	int i,j;
	int count = 0;
	for(i=0;i<S->length;i++)
	{
		count = 0;
		while(T->ch[count] == S->ch[i+count] && count < T->length && (i+count) < S->length)
			count ++;
		if(count == T->length)
			return i;
	}
	return S->length;
}

int main()
{
	SString S = StrInit();
	SString T = StrInit();
	SString V = StrInit();
	int i;
	for(i=0;i<find(S,T);i++)
		printf("%c",S->ch[i]);
	if(find(S,T) != S->length)
		for(i=0;i<V->length;i++)
			printf("%c",V->ch[i]);
	for(i=find(S,T)+T->length;i<S->length;i++)
		printf("%c",S->ch[i]);
 } 
