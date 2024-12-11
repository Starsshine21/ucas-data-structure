# include <stdio.h>
# include <stdlib.h>
# define LIST_INIT_SIZE 100
# define LISTINCREMENT 10

typedef char ElemType;
typedef struct
{
	ElemType * elem;
	int length;
	int listsize;
}SqList;

SqList IntiList_Sq()
{
	SqList L;
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));

	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return L;
}

int GetList(SqList* pL)
{
	char a;
	do{
		scanf("%c", &a);
		pL->elem[pL->length] = a; 
		(pL->length) ++;
	}while(getchar() != '\n');
	
	return 0;
}

void compare(SqList A,SqList B)
{
	int i = 0;
	while(A.elem[i] == B.elem[i])
	{
		i++;
		A.length --;
		B.length --;
	}
	if(A.length == 0 && B.length != 0)
		printf("1");
	else if(A.length != 0 && B.length == 0)
		printf("2");
	else if(A.length == 0 && B.length == 0)
		printf("0");
	else if(A.length != 0 && B.length != 0)
	{
		if(A.elem[i] > B.elem[i])
			printf("2");
		else
			printf("1");
	}
}


int main()
{
	SqList A,B;
	
	A = IntiList_Sq();
	B = IntiList_Sq();
	GetList(&A);
	GetList(&B);
	compare(A,B);
	return 0;
}

