#include <stdio.h>
#include <stdlib.h>

typedef int PolyTerm;

typedef struct PolyNode{
  PolyTerm coef,exp;
  struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;


LinkedPoly CreateList()
{
	PolyNode *L, *q;
	L = (PolyNode *)malloc(sizeof(PolyNode));
	L->next = NULL;
	q = L;
	PolyNode *p;
	char sign;
	char num;
	int i;
	sign = getchar();
	if(sign == '-')
	{
		p = (PolyNode *)malloc(sizeof(PolyNode));
		getchar();
		p->coef = 0;
		while((num=getchar()) >= '0' && num <= '9' )
			p->coef = p->coef * 10 + num - '0';
		p->coef = -1 * p->coef;
		if(num == 'x')
		{
			if((sign=getchar()) == '^')
			{
				scanf("%d",&p->exp);
				sign = getchar();
			}
			else
				p->exp = 1;
		}
		else
		{
			p->exp = 0;
			sign = num; 
		}
		q->next = p;
		q = p;
	}
	else if(sign == 'x')
	{
		p = (PolyNode *)malloc(sizeof(PolyNode));
		p->coef = 1;
		if((sign=getchar()) == '^')
		{
			scanf("%d",&p->exp);
			sign = getchar();
		}
		else
			p->exp = 1;
		q->next = p;
		q = p;
	}
		
	else if(sign >= '0' && sign <= '9')
	{
		p = (PolyNode *)malloc(sizeof(PolyNode));
		p->coef = sign - '0';
		while((num=getchar()) >= '0' && num <= '9')
			p->coef = p->coef * 10 + num - '0';
		if(num == 'x')
		{
			if((sign=getchar()) == '^')
			{
				scanf("%d",&p->exp);
				sign = getchar();
			}
			else
				p->exp = 1;
		}
		else
		{
			p->exp = 0;
			sign = num;
		}
		q->next = p;
		q = p;
	}
		
	while(sign != '\n')
	{
		sign = getchar();
		getchar();
		num = getchar();
		p = (PolyNode *)malloc(sizeof(PolyNode));
		if(num == 'x')
		{
			if(sign == '+')
				p->coef = 1;
			else
				p->coef = -1;
			if((num=getchar()) == '^')
			{
				scanf("%d",&p->exp);
				sign = getchar();
			}
			else
			{
				p->exp = 1;
				sign = num;
			}
			q->next = p;
			q = p;
		}
			
		else if(num >= '0' && num <= '9')
		{
			p = (PolyNode *)malloc(sizeof(PolyNode));
			p->coef = num - '0';
			while((num=getchar()) >= '0' && num <= '9')
				p->coef = p->coef * 10 + num - '0';
			if(sign == '-')
				p->coef = -1 * p->coef;
				
			if(num == 'x')
			{
				if((sign=getchar()) == '^')
				{
					scanf("%d",&p->exp);
					sign = getchar();
				}
				else
					p->exp = 1;
			}
			else
			{
				p->exp = 0;
				sign = num;
			}
			q->next = p;
			q = p;
		}
	}
	
	while(sign != '\n')
	{
		scanf("%c ",&sign);
		p = (PolyNode *)malloc(sizeof(PolyNode));
		if((num=getchar()) == 'x')
			p->coef = 1;
		else
		{
			p->coef = sign - '0';
			while((num=getchar()) != ' ' && num != 'x')
				p->coef = p->coef * 10 + num - '0';
		}
		
		
		if(sign == '-')
		{
			scanf("%d",i);
			p->coef = -1 * i;
		}
		else
		{
			scanf("%d",i);
			p->coef = i;
		}
		
		
		if(num== 'x')
		{
			if((sign=getchar()) == '^')
			{
				scanf("%d",&p->exp);
				sign = getchar();
			}
			else
				p->exp = 1;	
		}
		else
			p->exp = 0;
			
		q->next = p;
		q = p;
	}
	q->next = NULL;
	return L;
}


LinkedPoly differential(LinkedPoly L)
{
    LinkedPoly p,s;
    p = L;
    s = p->next;
    while(p->next != L && s)
	{
        if(s->exp == 0)
		{
            p->next = s->next;
            free(s);         
            s = p->next;
        }
        else
		{
		    s->coef = s->exp * s->coef;
            s->exp--;
            s = s->next;   
            p = p->next;     
        }
    }
	return L;
}

LinkedPoly fold(LinkedPoly L)
{
	LinkedPoly head,p,q;
	head = L;
	if(head->next)
	{
	for(head=L->next;head;head=head->next)
	{
		for(p=head->next;p;p=p->next)
		{
			if(p->exp == head->exp)
			{
				head->coef += p->coef;
				p->coef = 0;
				p->exp = 0;
			}
		}
//		for(p=head;p->next;p=p->next)
//		{
//			if(p->next->exp == head->exp)
//			{
//				head->coef += p->next->coef;
//				LinkedPoly t = p->next;
//				p->next = t->next;
//				free(t);
//			}
//		}
	}
}

	
//	for(p=L;p;p=p->next)
//	{
//		while(p->next->coef == 0)
//		{
//			LinkedPoly t = p->next;
//			p->next = t->next;
//			free(t);
//			if(p->next == NULL)
//				break;
//		}
//	}
	head = L;
	if(head->next)
	{
	for(head=L->next;head->next;)
	{
		p = head;	
		q = L;
		while(p->next->exp < q->next->exp)
			q = q->next;
		//p->next接到q后面去	
		LinkedPoly t = p->next;
		p->next = p->next->next;//取出 
		t->next = q->next;
		q->next = t;
		if(p == q) head = head->next;
	}
}
	return L;
}

int main()
{
	LinkedPoly L,head;
	L = CreateList();
	L = differential(L);
	L = fold(L);
	int t = 1;

	
	for(head=L->next;head;head=head->next)
	{
		if(head->coef != 0)
			t = 0;
	}
	head = L->next;
	if(t == 1)
		printf("0");
	else
	{
		if(head->coef != 0)
		{
			if(head->coef > 0)
				printf("%d",head->coef);
			else
				printf("- %d",-head->coef);
			if(head->exp == 0)
				printf(" ");
		 	else if(head->exp == 1)
				printf("x ");
			else if(head->exp > 1)
				printf("x^%d ",head->exp);
		}
		
		for(head=L->next->next;head;head=head->next)
		{
			if(head->coef != 0)
			{
				if(head->coef > 0)
					printf("+ %d",head->coef);
				else
					printf("- %d",-head->coef);
				if(head->exp == 0)
					printf(" ");
				else if(head->exp == 1)
					printf("x ");
				else if(head->exp > 1)
					printf("x^%d ",head->exp);
			}
		}
	}
	return 0;
}

