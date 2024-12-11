#include<stdio.h> 

#define MAXSIZE 100000

typedef struct{
	int rc;
	int next;
} SLNode;

typedef struct{
	SLNode r[MAXSIZE+1];
	int length;
}SLinkListType;

int main()
{
	SLinkListType SL;
	scanf("%d",&SL.length);
	int i,j,k;
	for(i=1;i<=SL.length;i++)
		scanf("%d",&SL.r[i]);
	SL.r[0].next = 1;
	SL.r[1].next = 0;
	for (i=2; i<=SL.length; ++i){
        for (j=0, k = SL.r[0].next; SL.r[k].rc<=SL.r[i].rc; j=k, k=SL.r[k].next );
        {
			SL.r[j].next = i;  
			SL.r[i].next = k; 
  		}
	}
	j = 0;
	for(i=0;i<SL.length-1;i++)
	{
		j = SL.r[j].next;
		printf("%d ",SL.r[j].rc);
	}
	j = SL.r[j].next;
	printf("%d",SL.r[j].rc);
	return 0;
}

