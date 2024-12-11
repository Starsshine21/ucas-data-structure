#include <stdio.h>  
#include <stdlib.h>  
#define TRUE 1  
#define OK 1  
#define FALSE 0  
#define ERROR 0  
#define OVERFLOW -1  
  
typedef struct node {  
    char data;  
    struct node * next;  
    struct node * prior;  
    int freq;  
}DuNode,* DuList;  
  
int Print(DuList head)  
{  
    DuNode * p=head->next;  
    while (p != NULL)  
    {  
        printf("%c ", p->data);  
        p = p->next;  
    }  
    printf("\n");  
    return OK;  
}  
DuList Sort(DuList head,int m)  
{  
    int i,j;  
    DuNode *p=head->next;  
    DuNode *q;  
    for(i=1;i<m;i++)  
    {  
        p=head->next;  
        for(j=1;j<=m-i && p->next;j++)  
        {  
            if(p->freq < p->next->freq)  
            {  
                if(p->next->next==0)  
                {  
                    q=p->next;  
                    p->prior->next=q;  
                    q->prior=p->prior;  
                    p->prior=q;  
                    p->next=NULL;  
                    q->next=p;  
                    continue;  
                }  
                q=p->next;  
                p->prior->next=q;  
                q->prior=p->prior;  
                p->prior=q;  
                p->next=q->next;  
                q->next->prior=p;  
                q->next=p;  
            }  
            p=p->next;  
        }  
    }  
}  
DuList Locate(DuList head,char e)  
{  
    DuNode *p=head->next;  
    while(p!=NULL)  
    {  
        if(p->data==e)  
        {  
            return p;  
        }  
        p=p->next;  
    }  
    return NULL;  
}  
DuList Insert(DuList head,char n)  
{  
    int i;  
    DuNode *s= (DuNode *)malloc(sizeof(DuNode));  
    if(head==NULL)  
    {  
        head=(DuList)malloc(sizeof(DuNode));  
        assert(head!=NULL);  
        head->data=0;  
        head->next=NULL;  
        head->prior=NULL;  
        head->freq=0;  
    }  
    DuNode *newnode=(DuList)malloc(sizeof(DuNode));  
    assert(newnode!=NULL);  
    newnode->data=n;  
    newnode->next=NULL;  
    newnode->prior=NULL;  
    newnode->freq=0;  
  
    DuNode *p=head;  
    while(p->next!=NULL)  
    {  
        p=p->next;  
    }  
    p->next=newnode;  
    newnode->prior=p;  
    return head;  
}  
int main()  
{  
    DuNode *q,*head=NULL;  
    char e,p;  
    int m,n,i;  
    scanf("%d %d",&m,&n);  
    getchar();  
    for(i=0;i<m;i++)  
    {  
        scanf("%c",&p);  
        getchar();  
        head=Insert(head,p);  
    }  
    for(i=n;i>0;i--)  
    {  
        scanf("%c",&e);  
        getchar();  
        q=Locate(head,e);  
        q->freq++;  
    }  
    Sort(head,m);  
    Print(head);  
    return 0;  
} 
