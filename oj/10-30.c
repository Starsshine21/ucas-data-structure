#include <stdio.h>

#define MAXSIZE 3000
typedef struct SqList{
	int r[MAXSIZE + 1];
}SqList;

int Partition (SqList *L, int low, int high){
	int pivotkey = L->r[low]; //���
    while (low<high) 
	{
        while (low<high && L->r[high]>=pivotkey)
            --high;
        L->r[low]=L->r[high];
        while (low<high && L->r[low]<=pivotkey) 
            ++low;
        L->r[high]=L->r[low];
    }
    L->r[low] = pivotkey;  //��㵽λ
    return low;            // �����������λ��
} 

void QSort (SqList *L,  int low,  int  high ) {
    //��L�е�������L.r[low..high]���п�������
    if (low < high) 
	{ 
	//��L.r[low..high] ����һ�λ���
    	int pivotloc = Partition(L, low, high); 
		QSort(L, low, pivotloc-1);  //�Ե������еݹ�����
    	QSort(L, pivotloc+1, high); //�Ը������еݹ�����
    }
}

int main()
{
	SqList L;
	int count = 0;
	char c = ' ';
//	int num;
//	scanf("%d",&num);
	while(c != '\n')
	{
		scanf("%d",&L.r[count++]);
		c = getchar();
	}
	c = ' ';
	while(c != '\n')
	{
		scanf("%d",&L.r[count++]);
		c = getchar();
	}
	QSort(&L,0,count-1);
	int i = 0;
	for(i=0;i<count-1;i++)
		printf("%d ",L.r[i]);
	printf("%d",L.r[i]);
	return 0;
}
