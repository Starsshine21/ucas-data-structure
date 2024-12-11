#include <stdio.h>

void main()
{
	int highbound,lowbound,step;
	scanf("%d %d %d",&lowbound,&highbound,&step);
	getchar();
	int count = (highbound-lowbound)/step;
	int space[count];
	int i;
	for(i=0;i<count;i++)
		scanf("%d",&space[i]);
	i = 0;
	int num = 0;
	int state = 0;
	while(i < count)
	{
		if(space[i])
		{
			if(num > 0)
			{
				if(state == 0)
					printf("0 %d %d",lowbound,num);
				else
					printf("\n0 %d %d",lowbound,num);
				state = 1;
				lowbound += num;
				num = 0;
			}
			lowbound += step;	
		}
		else
			num += step;
		i++;
	}
	if(space[count-1] == 0)
	{
		if(state)
			printf("\n");
		printf("0 %d %d",lowbound,num);
		state = 1;
	}
	if(!state)
		printf("0 0 0");
} 
