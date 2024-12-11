#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSIZE 12500

typedef struct OLNode{
	int i,j;
	int e;
	struct OLNode *right, *down;
}OLNode, *Olink;

typedef struct{
	Olink *rhead, *chead;
	int mu, nu, tu;
	OLNode data[MAXSIZE + 1];
}Matrix, *CrossList;


void CreatSMatrix_OL(int m, int n, CrossList M) 
{
    if (!(M->rhead=(Olink *)malloc(n*sizeof(Olink))))   
		return;
    if (!(M->chead=(Olink *)malloc(m*sizeof(Olink))))   
   		return;
   	int i;
    for(i=0;i<m;i++) 
   		M->rhead[i] = NULL;
    for(i=0;i<n;i++) 
   		M->chead[i] = NULL;
   	
   	int data[m*n];
   	
	int j, num, sign;
    num = 0;
    int count = 0;
    char c = '0';
    while (c != '\n') 
	{
        num = 0;
        if ((c = getchar()) == '-')
		    sign = -1;
		else
		{
            sign = 1;
            num = c - '0';
    	}
    	if(c == '\n' && count == 0)
			break;
    	while (isdigit((c = getchar())))
            num = num * 10 + c - '0';
		data[count++] = sign * num;
    }
    
    M->tu = count;
   	
	int t = M->tu;
	j = -1;
	i = 0;
	int e;
	Olink p,q;
    while(t>0) 
    {
    	scanf("%d",num);
    	if(j<n-1)
    		j++;
    	else
    	{
			j = 0;
    		i++;
		}
		if(num != 0) 
		{
			e = data[M->tu - t];
	        if (!(p=(OLNode *)malloc(sizeof(OLNode))))  
				return;
	        p->i=i; p->j=j; 
			p->e=e;
	        if (M->rhead[i] == NULL || M->rhead[i]->j > j)
			{
	   	        p->right = M->rhead[i]; 
				M->rhead[i] = p;
			}
	        else
			{   
		    	for (q= M->rhead[i]; (q->right) && q->right->j < j; q=q->right)
					; //找到插入点
				p->right = q->right;
				q->right = p;
			}
	        if (M->chead[j]==NULL || M->chead[j]->i>i)
			{
	            p->down = M->chead[j]; 
				M->chead[j]=p;
			}
	        else
			{    
				for (q=M->chead[j]; (q->down) && q->down->i < i; q=q->down)
					;
	            p->down = q->down; 
				q->down = p;
	        }  
	        t--; 
		}
	}
}

void main()
{
	int m,n;
	scanf("%d %d", &m, &n);
	CrossList A = (CrossList)malloc(sizeof(Matrix));
	CrossList B = (CrossList)malloc(sizeof(Matrix));
	CreatSMatrix_OL(m,n,A);
	CreatSMatrix_OL(m,n,B);
	Olink ta, tb;
	Olink pa = ta = A->rhead[0];
	Olink pb = tb = B->rhead[0]; 
	int i;
	for(i=0;i<A->mu;i++)
	{
		ta = pa = A->rhead[i];
		tb = pb = B->rhead[i];
		while(pa || pb)
		{
			if(pb == NULL)
				break;
			else if(pa->j == pb->j)
			{//各自后移 
				pa->e += pb->e;
				ta = pa;
				tb = pb; 
				pa = pa->right;
				pb = pb->right;
			}
			else if(pa->j < pb->j)
			{
				ta = pa;
				pa ++;
			}
			else if(pa->j > pb->j || pa == NULL)
			{
				Olink p = (Olink)malloc(sizeof(OLNode));
				if(pa ==A->rhead[i])
					A->rhead[i] = p;
				else
					ta->right = p;
				p->e = pb->e;
				p->right = pa;
				tb = pb;
				pb ++;
			}
		}
	}
	
	
}

