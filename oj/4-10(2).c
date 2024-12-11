#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSTRLEN 100

typedef struct str{
    char ch[INITSTRLEN];
    int length;
}*SString;


SString StrInit()
{
	SString s;
	s = (SString)malloc(sizeof(struct str)); 
	char x;
	int i;
	s->ch[0]='\0'; 
	s->length = 0; 
	while((x=getchar())!= '\n')
		s->ch[i++] = x;
	s->length = i;
	return s; 
}


void reverse (SString s)
{ 
	char tmp; 
	static int i=0;	
	if(i<s->length/2)
	{
 	    tmp=s->ch[i];
    	s->ch[i]=s->ch[s->length-i-1];
    	s->ch[s->length-i-1] = tmp;
    	i++;
    	reverse (s);
    }

}



int main()
{
	SString S;
	S = StrInit();
	reverse(S);
	int i;
	for(i=0;i<S->length;i++)
		printf("%c",S->ch[i]);
	return 0;
 } 
