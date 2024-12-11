#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN +1];


void StrAssign(SString T)
{
	char x;
	int i = 1;
	while((x=getchar()) != '\n')
		T->ch[i++] = x;
	T->ch[0] = i - 1;
}
//
//SString reverse(SString T)
//{
//	
//}


int main()
{
	SString S;
	StrAssign(S);
//	T = reverse(&T);
	int i;
	for(i=0;i<S[0];i++)
		printf("%c",S[i+1]);
	return 0;
 } 
