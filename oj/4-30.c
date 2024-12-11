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
	int i;
	s->ch[0]='\0'; 
	s->length = 0; 
	while((x=getchar())!= '\n')
		s->ch[i++] = x;
	s->length = i;
	return s; 
}

int repeat(SString S)
{
	int i,j;
	int temp_len = 0;
	int init = S->length;
	for(i=1;i<S->length;i++)
	{
		for(j=0;j<i;j++)
		{
			temp_len = 0;
			while(S->ch[i+temp_len] == S->ch[j+temp_len] && (j+temp_len) < S->length)
				temp_len ++;
			if(temp_len > len || (temp_len == len && j < init)) 
			{
				len = temp_len;
				init = j;
			}
		}
	}
	if(len == 0)
		return -1;
	else
		return init;
}

int main()
{
	SString S = StrInit();
	int i;
	if(repeat(S) == -1)
		printf("-1");
	else
	{
		for(i=0;i<len;i++)
			printf("%c",S->ch[i+repeat(S)]);
		printf(" %d",repeat(S));
	}
	return 0;
} 
