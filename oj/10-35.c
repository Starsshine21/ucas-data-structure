#include <stdio.h>

#define MAXSIZE 30

typedef struct HeapType{
	int r[MAXSIZE + 1];
	int length;
};

void HeapAdjust (int *R, int s, int m)
{
    int rc = R[s];    //�ݴ� R[s] 
    int j;
    for(j=2*s; j<=m; j*=2)
	{ //j ��ֵָ������
            //����key�ϴ�ĺ��ӽ�����϶���ɸѡ
        if ( j<m && R[j]<R[j+1])  
			++j;  //jΪkey�ϴ�ļ�¼�±�
        if (rc >= R[j])  
			break; //rcӦ������λ��s��
        R[s] = R[j];   s = j;  
    } 
    R[s] = rc;  //������ǰ�ĶѶ���¼���뵽 s λ��
}

void HeapSort (HeapType *H)
{//��˳��� H ���ж�����
	int i;
	for(i=H->length/2;i>0;--i)
		HeapAdjust (H->r,i,H->length);    // ��H.r���󶥶�
	for(i=H->length; i>1; --i ) 
	{
	// ���Ѷ���¼�͵�ǰδ������������
	//H.r[1..i]�����һ����¼�໥����
		int temp = H->r[1];
		H->r[1] = H->r[i];
		H->r[i] = temp;
	// ��H.r[1..i-1]����Ϊ�󶥶�
		HeapAdjust(H->r, 1, i-1);  
	}
} 

int main()
{
	HeapType H;
	char c = ' ';
	int count = 0;
	while(c != '\n')
	{
		scanf("%d",&H.r[count++]);
		H.length ++;
		c = getchar();
	}
	HeapSort(&H);
}
	
}
