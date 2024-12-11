#include <stdio.h>

#define MAXSIZE 3000
typedef struct SqList{
	int r[MAXSIZE + 1];
}SqList;

int Partition (SqList *L, int low, int high){
	int pivotkey = L->r[low]; //轴点
    while (low<high) 
	{
        while (low<high && L->r[high]>=pivotkey)
            --high;
        L->r[low]=L->r[high];
        while (low<high && L->r[low]<=pivotkey) 
            ++low;
        L->r[high]=L->r[low];
    }
    L->r[low] = pivotkey;  //轴点到位
    return low;            // 返回轴点所在位置
} 

void QSort (SqList *L,  int low,  int  high ) {
    //对L中的子序列L.r[low..high]进行快速排序
    if (low < high) 
	{ 
	//对L.r[low..high] 进行一次划分
    	int pivotloc = Partition(L, low, high); 
		QSort(L, low, pivotloc-1);  //对低子序列递归排序
    	QSort(L, pivotloc+1, high); //对高子序列递归排序
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
