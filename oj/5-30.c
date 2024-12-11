#include <stdio.h>
#include <string.h>

typedef enum {ATOM,LIST} ElemTag;
typedef struct GLNode{
    ElemTag tag;
    union{
        char atom;
        struct { 
        struct GLNode *hp, *tp;
       }ptr;
    };
}*GList;


void delete(GList T, char x)
{
  	if (L) 
	{
    	head = L->ptr.hp;  // 考察第一个子表
    	if ((head->tag == Atom) && (head->atom == x)) 
       	{  …………….  } // 删除原子项 x的情况
    	else 
       	{……………. }// 第一项没有被删除的情况 
  	}

}

int main()
{
	GList L;
	SString S;
	CreateGList(L, S);
	getchar();
	char x = getchar();
	delete(L,x);
}

void CreateGList(Glist *L, SString S) 
{
	if(!strComp(S,”()”))  
		L = NULL;  // 创建空表
	else 
	{
    // 生成表结点
   		if(!(L=(Glist*)malloc(sizeof(GLNode)) )) 
		    return;
    	if (StrLen(S)==1)
		{//建立单原子广义表
       		L->tag= ATOM;
			L->atom = S; 
		}
    	else 
		{
        	L->tag=List;   
			p=L；
       //设sub为 脱去串 S 最外层括弧的子串
      		StrSubStr(sub, S,2,StrLen(S)-1);  
      		//为sub中所含n个子串建立n个子表
      		do 
			{ //重复建n个子表
			 //分离出子表串hsub=?I
				Sever(sub, hsub); 
				//创建由串hsub定义的广义表p?ptr.hp
				CreateGList(p->ptr.hp, hsub); 
				q=p; 
				if (!IsStrEmpty(sub)
				{ 
				//余下的表不为空
					if(!(p=(GLNode*)malloc(sizeof(GLNode)) )) exit(OVERFLOW);
				    //建下一个子表的表结点*(p->ptr.tp) 
				   	p->tag = LIST;    
					q->ptr.tp=p;
				}
			}while (!IsStrEmpty(sub));
			q->ptr.tp = NULL;    // 表尾为空表
    	}
  	}
	return;
}

