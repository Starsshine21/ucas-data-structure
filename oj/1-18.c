#include <stdio.h>

//#define A 0
//#define B 1
//#define C 2
//#define D 3
//#define E 4

typedef struct school
{
//	struct student;
	int score_M;
	int score_F;
	int total_score;
}sch;

//typedef struct student 
//{
//	char program[2];
//	char gender[2];
//};


int main ()
{
	struct school p[5];
    int d;
    char a,b,c;
    int i;
    int num = 0;//第几个学校 
	for(i=0;i<5;i++)
		p[i].score_F = p[i].score_M = p[i].total_score = 0;
	
	while(scanf("%c %c %c %d",&a,&b,&c,&d) != EOF){

    	num = c - 'A'; 
        if(b == 'M')
        	p[num].score_M += d;
        else
        	p[num].score_F += d;
        getchar();
//        if((e=getchar()) == '\n')
//        	;
//        else if((e=getchar()) == EOF)
//    		break;
    }
    
	for(i=0;i<5;i++)
	{
		p[i].total_score = p[i].score_F + p[i].score_M;
		if(p[i].score_M > 0)
		printf("%c M %d\n",i+'A',p[i].score_M);
		if(p[i].score_F > 0)
		printf("%c F %d\n",i+'A',p[i].score_F);
		if(p[i].total_score > 0)
		printf("%c %d\n",i+'A',p[i].total_score);
	}

//	int i;
//	int sum[5][2];//5表示学校，2表示性别 
//	for(i=0,i<5;i++)
//		for(j=0;j<2;j++)
//			sum[i][j] = 0;
//	for(i=0;i<5;i++)
//	{
//		x = p[i].school;
//		if(p[i].gender == 'M')
//			sum[x][0] += p[i].score;
//		else
//			sum[x][1] += p[i].score; 
//	}

	//求和并把和放入结构中 
	
	
	
}
