#include <stdio.h>

#define MAXSIZE 30

typedef struct HeapType{
	int r[MAXSIZE + 1];
	int length;
};

void HeapAdjust (int *R, int s, int m)
{
    int rc = R[s];    //暂存 R[s] 
    int j;
    for(j=2*s; j<=m; j*=2)
	{ //j 初值指向左孩子
            //沿着key较大的孩子结点自上而下筛选
        if ( j<m && R[j]<R[j+1])  
			++j;  //j为key较大的记录下标
        if (rc >= R[j])  
			break; //rc应插入在位置s上
        R[s] = R[j];   s = j;  
    } 
    R[s] = rc;  //将调整前的堆顶记录插入到 s 位置
}

void HeapSort (HeapType *H)
{//对顺序表 H 进行堆排序
	int i;
	for(i=H->length/2;i>0;--i)
		HeapAdjust (H->r,i,H->length);    // 把H.r建大顶堆
	for(i=H->length; i>1; --i ) 
	{
	// 将堆顶记录和当前未经排序子序列
	//H.r[1..i]中最后一个记录相互交换
		int temp = H->r[1];
		H->r[1] = H->r[i];
		H->r[i] = temp;
	// 将H.r[1..i-1]调整为大顶堆
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
