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

SString StrInit()
{
	SString s;
	s = (SString)malloc(sizeof(STR)); 
	char x;
	int i; 
	s->length = 0; 
	return s; 
}

int main()
{
	SString s = StrCreate();
	SString t = StrCreate();
	SString r = StrInit();
	int i,j;
	int position[50];
	int num_1,num_2;//第一个用于存储重复的位置，第二个用于计数r中元素
	num_1 = num_2 = 0; 
	int appear = 0;
	int state = 0;//0为未出现 
	for(i=0;i<s->length;i++)
	{
		appear = 0;
		for(j=0;j<t->length;j++)
			if(s->ch[i] == t->ch[j])
 				appear = 1;
		if(appear == 0)
		{
			int k;
			state = 0;
			for(k=0;k<i;k++)
				if(s->ch[k] == s->ch[i])
					state = 1;
			if(state == 0)
			{
				position[num_1++] = i;
				r->ch[num_2++] = s->ch[i]; 
				r->length ++;
			}
		}
	}
	
	if(r->length == 0)
		printf("-1");
	else
	{
		for(i=0;i<num_2;i++)
			printf("%c",r->ch[i]);
		printf(" ");
		for(i=0;i<num_1;i++)
			printf("%d",position[i]);
	}
}
