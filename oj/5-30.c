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
    	head = L->ptr.hp;  // �����һ���ӱ�
    	if ((head->tag == Atom) && (head->atom == x)) 
       	{  ����������.  } // ɾ��ԭ���� x�����
    	else 
       	{����������. }// ��һ��û�б�ɾ������� 
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
	if(!strComp(S,��()��))  
		L = NULL;  // �����ձ�
	else 
	{
    // ���ɱ���
   		if(!(L=(Glist*)malloc(sizeof(GLNode)) )) 
		    return;
    	if (StrLen(S)==1)
		{//������ԭ�ӹ����
       		L->tag= ATOM;
			L->atom = S; 
		}
    	else 
		{
        	L->tag=List;   
			p=L��
       //��subΪ ��ȥ�� S ������������Ӵ�
      		StrSubStr(sub, S,2,StrLen(S)-1);  
      		//Ϊsub������n���Ӵ�����n���ӱ�
      		do 
			{ //�ظ���n���ӱ�
			 //������ӱ�hsub=?I
				Sever(sub, hsub); 
				//�����ɴ�hsub����Ĺ����p?ptr.hp
				CreateGList(p->ptr.hp, hsub); 
				q=p; 
				if (!IsStrEmpty(sub)
				{ 
				//���µı�Ϊ��
					if(!(p=(GLNode*)malloc(sizeof(GLNode)) )) exit(OVERFLOW);
				    //����һ���ӱ�ı���*(p->ptr.tp) 
				   	p->tag = LIST;    
					q->ptr.tp=p;
				}
			}while (!IsStrEmpty(sub));
			q->ptr.tp = NULL;    // ��βΪ�ձ�
    	}
  	}
	return;
}

