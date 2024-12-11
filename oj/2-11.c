#include<stdio.h>


#define MAXSIZE 100
#define OK 1
#define ERROR 0


typedef int ElemType;
typedef int Status;
int Length;

typedef struct
{
    ElemType data[MAXSIZE];
    int Length;
}SqList;



SqList Create(SqList * L)
{
	int a,i;
    while(1)
    {
    	scanf("%d", &a);
	    L->data[L->Length]=a;
    	L->Length ++;
    	if(getchar() == '\n' )
    		break;
    }
    if(L->Length < 100)
    	return *L;
}

void print(SqList *L)
{
	int i;
    for(i=0;i<L->Length;i++)
    {
        printf("%d ",L->data[i]);
    }
}




Status Locate(SqList *L,ElemType e)
{
	int i;
    if(e<L->data[0])
    {
        return 0;
    }
    if(e>L->data[L->Length-1])
    {
        return L->Length;
    }
    else
    {
        for(i=0;i<L->Length;i++)
        {

            if(e>=L->data[i] && e<L->data[i+1])
            {
                return i+1;
            }
        }
    }
}



Status InsertList(SqList *L,ElemType local,ElemType e)
{
	int i;
    for(i=L->Length-1;i>=local;i--)
    {
        L->data[i+1]=L->data[i];
    }
    L->data[local]=e;
    L->Length++;
    return OK;
}



int main()
{
    SqList L;
    L->Length = 0;
    int x,local;
 
    Create(&L);
    

    scanf("%d",&x);
    local = Locate(&L,x);
    InsertList(&L, local, x);
    print(&L);
    return OK;
}
