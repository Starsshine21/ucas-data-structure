#include "elevator.h"


Status InitElevator(Elevator *elevator)
{
    // 初始化CallCar以及Up和Down
    int i;
	for (i=0;i<5;i++)
    {
        elevator->CallCar[i] = 0;
        Down[i] = 0;
        Up[i] = 0;
        elevator->Stack[i].top = -1;
    }
    elevator->curpos = 1;
    elevator->Isstandby = 0;
    elevator->movement = Waiting;
    elevator->movementTim = waitTIM;
    elevator->State = Free;
    elevator->Passnum = 0;
    elevator->doorstate = 3; 
	return 0;
}

Status Controller(Elevator *elevator)//状态机
{
    int highrequest = HigherRequests(elevator);
    int lowrequest = LowerRequests(elevator);  
    int nextpos = -1; // 下一目的

    if(elevator->State == Free)
    {    
        // 如果楼上楼下都有请求则选择更近的请求
        if (highrequest != -1 && lowrequest != -1)
        {
            if (highrequest - elevator->curpos >= elevator->curpos - lowrequest)
                nextpos = lowrequest;
            else
                nextpos = highrequest;
        }
        else if (highrequest == -1)
            nextpos = lowrequest;
        else if (lowrequest == -1)
            nextpos = highrequest;

    //根据请求方向调整
        if (nextpos == -1)//没请求
            return OK;
        else if(nextpos == elevator->curpos)
        {
            elevator->movement = Opening;
            elevator->movementTim = doorTIM;
        }
        else if(nextpos < elevator->curpos)
        {
            elevator->State = GoingDown;
            elevator->movement = Accelerating;
            elevator->movementTim = accelerateTIM;
        }
        else if(nextpos > elevator->curpos)
        {
            elevator->State = GoingUp;
            elevator->movement = Accelerating;
            elevator->movementTim = accelerateTIM;
        }
    }
    else if(elevator->State == GoingDown)
    {
        if(lowrequest == -1)
        {
        	//如果当前楼层有人
//			if(StackEmpty(elevator->Stack[elevator->curpos]) == True)
//			{
//				elevator->movement = Opening;
//				elevator->movementTim = doorTIM;
//			}
//			else
			{ 
            	elevator->State = Free;
            	elevator->movement = Waiting;
            	elevator->movementTim = 0;
        	}
		}
    }
    else
    {
        if(highrequest == -1)
        {
        	//如果当前楼层有人
//			if(StackEmpty(elevator->Stack[elevator->curpos]) == True)
//			{
//				elevator->movement = Opening;
//				elevator->movementTim = doorTIM;
//			}
//			else
			{
        	    elevator->State = Free;
            	elevator->movement = Waiting;
            	elevator->movementTim = 0;
        	}
		}
    }
}

Status ChangeMovement(Elevator *elevator)
{
    switch (elevator->movement)
    {
    case Opening:
        elevator->movement = Opened;
        elevator->doorstate = 0;
        printf("电梯门打开\n");
        elevator->movementTim = testTIM;
        break;

    case Opened:
        // 如果本层电梯栈不空
        elevator->doorstate = 1;
        if (StackEmpty(elevator->Stack[elevator->curpos]) == False)//有人要在本楼层下楼 
        {
            ClientOut(elevator);
            elevator->movementTim = PeopleInAndOutTIM;
            printf("乘客正在出电梯\n");
        }
        // 乘客都出栈后/没有要出去的 进行下一个判断
        else
        {
            elevator->CallCar[elevator->curpos] = 0;
            // 如果有人要在本楼层进入电梯并且电梯未满
            if (IfPeopleIn(elevator) && elevator->Passnum < MaxNum)
            {
                ClientIn(elevator);
                elevator->movementTim = PeopleInAndOutTIM;
            }
            // 如果没人等待那么进入下一个状态
            else
            {
                elevator->movement = Closing;
                printf("电梯门正在关闭\n");
                elevator->movementTim = doorTIM;
            }
        }
        break;

    case Closing:
    	elevator->doorstate = 2;
        elevator->movement = Closed;
        printf("电梯门已经关上\n");
        break;

    case Closed:
    	elevator->doorstate = 3;
        // 如果有请求,设置电梯状态为正在加速
        if (HigherRequests(elevator) != -1 || LowerRequests(elevator) != -1)
        {
            elevator->movement = Accelerating;
            elevator->movementTim = accelerateTIM;
            printf("电梯开始加速\n");
        }
        //当前方向没有请求，改变运动状态
        else if (elevator->Passnum)
            ChangeState(elevator);
        // 如果没有请求并且没有人那就等待
        else
        {
            elevator->movement = Waiting;
            elevator->movementTim = waitTIM;
            // 提示消息
            printf("电梯正在 %d 楼等待\n", elevator->curpos);
        }
        break;

    case Moving:
        if (elevator->Isstandby)//电梯正在返回本垒层
        {
            if (elevator->curpos + 1 < 1)
            {
                Upstairs(elevator);
                elevator->movement = Moving;
                elevator->movementTim = upstairsTIM;
            }
            else if (elevator->curpos - 1 > 1)
            {
                DownStairs(elevator);
                elevator->movement = Moving;
                elevator->movementTim = downstairsTIM;
            }
            //即将到达本垒层
            else
            {
                elevator->movement = SlowingDown;
                elevator->movementTim = slowdownTIM;
            }
        }
        else
        {
            // 记录nextpos的值
            int nextpos;
            // 如果电梯正在上楼就获取楼上的请求
            if (elevator->State == GoingUp)
                nextpos = HigherRequests(elevator);
            // 如果电梯正在下楼就获取楼下的请求
            else
                nextpos = LowerRequests(elevator);
            // 如果应该继续往下那么更新当前状态的时间并下楼
            if (nextpos < elevator->curpos)
            {
                if(nextpos + 1 == elevator->curpos)
                {
                    DownStairs(elevator);
                    elevator->movement = SlowingDown;
                    elevator->movementTim = slowdownTIM;
                }
                else
                {
                    DownStairs(elevator);
                    elevator->movement = Moving;
                    elevator->movementTim = downstairsTIM;
                }
            }
            // 如果应该继续往上那么更新当前状态的时间并上楼
            else if(nextpos > elevator->curpos)
            {
                if(nextpos - 1 == elevator->curpos)
                {
                    Upstairs(elevator);
                    elevator->movement = SlowingDown;
                    elevator->movementTim = slowdownTIM;
                }
                else
                {
                    Upstairs(elevator);
                    elevator->movement = Moving;
                    elevator->movementTim = upstairsTIM;
                }
            }
        }
        break;

    case Waiting:
        //BackToBase(elevator);
        if(elevator->doorstate == 0)
        	elevator->movement = Opened;
        else if(elevator->doorstate == 2)
        	elevator->movement = Closed;
        else if(elevator->doorstate == 3)
        {
			elevator->movement = Opening;
        	elevator->movementTim = doorTIM;
        }
        break;

    case Accelerating:
        elevator->movement = Moving;
        if (elevator->State == GoingDown)// 计时为下楼计时
            elevator->movementTim = downstairsTIM;
        else if (elevator->State == GoingUp)// 计时为上楼计时
            elevator->movementTim = upstairsTIM;
        break;

    case SlowingDown:
        if (!elevator->Isstandby)// 如果是正常减速则开门
        {
            elevator->movement = Opening;
            elevator->movementTim = doorTIM;
        }
        else       // 如果是回到本垒层则等待
        {
            elevator->movement = Waiting;
            elevator->movementTim = waitTIM;
        }
        break;
    }
	return 0;
}

int HigherRequests(Elevator *elevator)
{
    // 电梯状态得为GoingUp或者Wating才能考虑上楼
    if (elevator->State == GoingUp || elevator->movement == Waiting || elevator->movement == Closed)
    {
        // 找到最接近的请求
        int i;
		for (i = elevator->curpos+1 ; i < 5; i++)
            if (elevator->CallCar[i] || Up[i] || Down[i])
                // 返回最接近的请求楼层
                return i;
    }
    return -1;
}

int LowerRequests(Elevator *elevator)
{
    // 电梯状态得为GoingDown或者Waiting才行
    if (elevator->State == GoingDown || elevator->movement == Waiting)
    {
        // 寻找最近请求
        int i;
		for (i = elevator->curpos-1; i >= 0; i--)
            if (elevator->CallCar[i] || Up[i] || Down[i])
                // 返回最近请楼层
                return i;
    }
    // 没找到则返回-1
    return -1;
}

void ChangeState(Elevator *elevator)
{
	int i;
	int temp = 0;
    if (elevator->Passnum >= MaxNum)
        return;
    
    // 看楼上是否有请求
	
    for (i = elevator->curpos + 1; i < 5; i++)
        if (elevator->CallCar[i] || Up[i])
            temp = 1;
    // 如果楼上没有请求并且当前电梯内有乘客,那么电梯State需要改变
    if (elevator->Passnum && !temp)
        elevator->State = GoingDown;
    temp = 0;
    // 看楼下是否有请求
	for (i = elevator->curpos - 1; i >= 0; i--)
        if (elevator->CallCar[i] || Down[i])
            temp = 1;
    // 如果楼下没有请求并且当前电梯内有乘客,那么电梯State需要改变
    if (elevator->Passnum && !temp)
        elevator->State = GoingUp;
}

Status Upstairs(Elevator *elevator)
{
    elevator->curpos++;
	return 0;
}


Status DownStairs(Elevator *elevator)
{
    elevator->curpos--;
	return 0;
}


Status BackToBase(Elevator *elevator)
{
    // 表示等待时间已经超过300s
    //elevator->Isstandby = 1;

    // 如果当前在本垒层则继续保持
    if (elevator->curpos == 1)
    {
        elevator->movement = Waiting;
        printf("电梯在本垒层等待\n");
        elevator->State = Free;
        elevator->movementTim = 0;
    }
    // 如果在本垒层下方则准备回到一楼
    else if (elevator->curpos < 1)
    {
        // 设置电梯加速启动
        elevator->movement = Accelerating;
        // 计时
        elevator->movementTim = accelerateTIM;
        // 上楼
        elevator->State = GoingUp;
    }
    // 如果在本垒层上方则准备回到一楼
    else
    {
        // 设置电梯加速启动
        elevator->movement = Accelerating;
        // 计时
        elevator->movementTim = accelerateTIM;
        // 下楼
        elevator->State = GoingDown;
    }
    
    return OK;
}

Status CancelIsstandby(Elevator *elevator)
{
    elevator->Isstandby = 0;
    return OK;
}

Status InitQueue(WaitQueue *Q)
{
    // 分配内存空间
    Q->front = Q->rear = (ClientQueueNode *)malloc(sizeof(ClientQueueNode));
    Q->front->next = NULL;
    // 初始化等待数量为0
    Q->WaitNum = 0;
    return OK;
}

Status Enqueue(WaitQueue *Q, Client temp)
{
    // 分配新的内存空间
    ClientQueueNode *ptr = (ClientQueueNode *)malloc(sizeof(ClientQueueNode));

    ptr->passenger = temp;
    ptr->next = NULL;
    Q->rear->next = ptr;
    Q->rear = ptr;
    Q->WaitNum++;
    return OK;
}

Status Dequeue(WaitQueue *Q, Client *temp)
{
	
	ClientQueueNode *ptr = Q->front;
    // 如果队列为空直接返回
    if (Q->WaitNum == 0)
        return Error;
   	
	Q->front = Q->front->next;
	*temp = Q->front->passenger;

	free(ptr);
	Q->WaitNum --;
	return OK;
	
//    //取出乘客 
//    ptr = Q->front->next;
//    //看一下这里的乘客  
//    Q->front->next = ptr->next;
//    *temp = ptr->passenger;
//    free(ptr);
//    Q->WaitNum--;
//    return OK;
}

Status InitWaitQueue()
{
	int i,j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 5; j++)
            InitQueue(&Queue[i][j]);
	return 0;
}

void Update(void)
{
	int i,j;
    // 遍历等待队列
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (!i) // i等于0代表上楼等待队列
            {
                if (Queue[i][j].WaitNum == 0)   // 如果没人等待Up就设置为0
                    Up[j] = 0;
        	}
            else// i等于1代表下楼等待队列
            {
                if (Queue[i][j].WaitNum == 0)// 如果没人等待Down就设置为0
                    Down[j] = 0;
        	}
		}
    }
    return;
}

//乘客进电梯
Status Pop(ClientStack *S, Client *temp)
{
    *temp = S->base[S->top--];
    return OK;
}

//乘客出电梯
Status Push(ClientStack *S, Client temp)
{
    //if (S->top < MaxNum)
        S->base[++S->top] = temp;
    return OK;
}

//判断乘客栈是否为空 每层一个栈（也可以用数组之类的 无所谓）
Status StackEmpty(ClientStack S)
{
    // 如果栈顶为-1返回True
    if (S.top == -1)
        return True;
    // 否则返回False
    return False;
}

Status Newclient()
{
    Client NewClient;
    NewClient.occurTime = Time;                     // 新乘客到达时间
    NewClient.ClientID = ++ID;                      // 新乘客的ID
    NewClient.Infloor = rand() % 5;                 // 新乘客起始楼层
    NewClient.OutFloor = rand() % 5;                // 新乘客目标楼层
    NewClient.GiveupTime = 20 + rand() % 30;      // 最长等待时间
    InterTime = rand() % 30;                        // 下一个乘客到达时间间隔
    while (NewClient.Infloor == NewClient.OutFloor) // 如果新乘客出发地和目标地相同，重新分配
        NewClient.OutFloor = rand() % 5;
    // 如果是上楼则进入对应的上楼等待队列
    if (NewClient.Infloor < NewClient.OutFloor)
    {
        Enqueue(&Queue[0][NewClient.Infloor], NewClient);
        printf("%d 号乘客在 %d 楼等待上楼\n", NewClient.ClientID, NewClient.Infloor);
        Up[NewClient.Infloor] = 1;
    }
    else
    {
        Enqueue(&Queue[1][NewClient.Infloor], NewClient);
        printf("%d 号乘客在 %d 楼等待下楼\n", NewClient.ClientID, NewClient.Infloor);
        Down[NewClient.Infloor] = 1;
    }
	return 0;
}

//超过等待时间的乘客
Status ClientGiveUp()
{
	int i,j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 5; j++)
        {
            WaitQueue temp = Queue[i][j];
            ClientQueueNode *ptr = temp.front->next;
            ClientQueueNode *pre = temp.front;
            while (ptr != NULL)
            {
                // 如果超过等待时间
                if (ptr->passenger.occurTime + ptr->passenger.GiveupTime <= Time)
                {
                    // 乘客出列
                    pre->next = ptr->next;
                    printf("等待时间过长，%d 号乘客离开了 %d 楼\n", ptr->passenger.ClientID, ptr->passenger.Infloor);
                    free(ptr);
                    ptr = pre->next;
                    Queue[i][j].WaitNum--;// 排队人数减少
                }
                else
                {
                    pre = ptr;
                    ptr = ptr->next;
                }
            }
        }
    }
    // 更新Up和Down数组
    Update();
	return 0;
}

Status ClientOut(Elevator *elevator)
{
    // 当前楼层的乘客栈不空,则清空乘客栈
    if (elevator->Stack[elevator->curpos].top != -1)
    {
        Client temp;
        Pop(&elevator->Stack[elevator->curpos], &temp);
        printf("%d 号乘客在 %d 楼下电梯\n", temp.ClientID, temp.OutFloor);
        elevator->Passnum--;
        Time += PeopleInAndOutTIM * t;
    }
    Update();
	return 0;
}

Status IfPeopleIn(Elevator *elevator)
{
    // 如果电梯向上
    if (elevator->State == GoingUp)
    {
        if (Up[elevator->curpos]) // 如果有人等待
            return True;
        // 如果电梯已经等待300s则有人等待就返回True
        if (!elevator->Passnum && Down[elevator->curpos])
            return True;
    }
    // 如果电梯向下
    else if (elevator->State == GoingDown)
    {
        // 如果有人等待返回True
        if (Down[elevator->curpos])
            return True;
        // 如果上一个状态为Free则有人等待就返回True
        if (!elevator->Passnum && Up[elevator->curpos])
            return True;
    }
    else if (Down[elevator->curpos] || Up[elevator->curpos])
            return True;
    // 没人等待返回False
    return False;
}

Status ClientIn(Elevator *elevator)
{
    if (elevator->State == Free)
    {
        if (Up[elevator->curpos])
        {
            Client temp;
            Dequeue(&Queue[0][elevator->curpos], &temp);// 从等待队列中取出乘客
            Push(&elevator->Stack[temp.OutFloor], temp);// 乘客入栈
            elevator->CallCar[temp.OutFloor] = 1;// 设置目的地
            printf("%d 号乘客在 %d 楼进入电梯\n", temp.ClientID, elevator->curpos);
        }
        else if(Down[elevator->curpos])
        {
            Client temp;
            Dequeue(&Queue[1][elevator->curpos], &temp);
            Push(&elevator->Stack[temp.OutFloor], temp);
            elevator->CallCar[temp.OutFloor] = 1;
            printf("%d 号乘客在 %d 楼进入电梯\n", temp.ClientID, elevator->curpos);
        }
    }
    else if (elevator->State == GoingUp)
    {
        // 如果上一状态不是空闲的,那么只能接与行进状态相同的乘客
        Client temp;
        Dequeue(&Queue[0][elevator->curpos], &temp);
        Push(&elevator->Stack[temp.OutFloor], temp);
        elevator->CallCar[temp.OutFloor] = 1;
        printf("%d 号乘客在 %d 楼进入电梯\n", temp.ClientID, elevator->curpos);
    }
    else
    {
        Client temp;
        Dequeue(&Queue[1][elevator->curpos], &temp);
        Push(&elevator->Stack[temp.OutFloor], temp);
        elevator->CallCar[temp.OutFloor] = 1;
        printf("%d 号乘客在 %d 楼进入电梯\n", temp.ClientID, elevator->curpos);
    }
    // 电梯乘客增加
    elevator->Passnum++;
    Update();
    return OK;
}

void makegraph(Elevator *elevator)
{
	int i,j;
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	rectangle(150, 50, 350, 125);
	rectangle(150, 125, 350, 200);
	rectangle(150, 200, 350, 275);
	rectangle(150, 275, 350, 350);
	rectangle(150, 350, 350, 425);

	rectangle(350, 50, 450, 125);
	rectangle(350, 125, 450, 200);
	rectangle(350, 200, 450, 275);
	rectangle(350, 275, 450, 350);
	rectangle(350, 350, 450, 425);
	
	rectangle(550, 50, 750, 125);
	rectangle(550, 125, 750, 200);
	rectangle(550, 200, 750, 275);
	rectangle(550, 275, 750, 350);
	rectangle(550, 350, 750, 425);

	settextstyle(25, 0, "楷体");//设置字体高度，宽度，字型
    setbkmode(TRANSPARENT);//设置字体背景透明，默认不透明
    settextcolor(BLACK);
	char c;
	for(i=0;i<4;i++)
	{
	    c = '4'- i;
		int y_pos = i * 75 + 70;
		outtextxy(70,y_pos,c);
	}
	char arr_0[] = "-1";
	outtextxy(70,370,arr_0);
 

    char arr_1[] = "电梯门与乘客";
    outtextxy(210,10, arr_1);
	char arr_2[] = "等待中的乘客";
    outtextxy(580,10, arr_2);

	//电梯的位置
	IMAGE door_img;
	int y_ele = 350 - elevator->curpos * 75;
	if(elevator->movement == Closing || elevator->movement == Opened)
		loadimage(&door_img,_T("opened.png"), 100, 75);
	else
		loadimage(&door_img,_T("closed.png"), 100, 75);
	putimage(350, y_ele, &door_img, SRCINVERT);
	

	//电梯中的乘客
	IMAGE people;
	loadimage(&people,_T("people.png"),50,50);
	for(i=0;i<5;i++)
	{
		int num = elevator->Stack[i].top;
		while(num > -1)
		{
			int x_people = 300 - 50 * num;
			putimage(x_people, y_ele+25 , &people, SRCINVERT);
			//char c = elevator->Stack[i].base[num].ClientID - '0';
			//outtextxy(400,400,c);
			num --;
		}
	}
	
	
	//等待的乘客
	for(i=0;i<2;i++)
	{
		for(j=0;j<5;j++)
		{
			int d = Queue[i][j].WaitNum;
			int people_pos = 375 -  Queue[i][j].rear->passenger.Infloor * 75;
			if(d)
			{
				putimage(570,people_pos,&people,SRCINVERT);
				d--;
			}
		}
	}

	Sleep(300);
}


int main(int argc, char const *argv[])
{
	Elevator elevator;
    srand(time(NULL));
 
    InitElevator(&elevator);
    InitWaitQueue();
	initgraph(800, 480, SHOWCONSOLE);
    while (Time++ < MaxTime)
    {
        ClientGiveUp();
        if (!InterTime)
            Newclient();
        else
            InterTime--;
        // 正在关门或者等待时本层出现乘客则进入电梯
        if (elevator.movement == Closing)
        {
            // 如果当前电梯不为空,如果有相同行进方向的乘客则入栈
            if (elevator.Passnum && elevator.Passnum < MaxNum)
            {
                // 如果当前电梯向上,有向上的乘客则切换到开门
                if (elevator.State == GoingUp)
                {
                    if (Up[elevator.curpos])
                    {
                        elevator.movement = Opening;
                        elevator.movementTim = doorTIM;
                    }
                }
                // 如果当前电梯向下,有向下的乘客则切换到开门
                else if (elevator.State == GoingDown)
                {
                    if (Down[elevator.curpos])
                    {
                        elevator.movement = Opening;
                        elevator.movementTim = doorTIM;
                    }
                }
            }
            // 如果当前电梯为空
            else if (!elevator.Passnum)
            {
                // 只要有请求则都切换到开门状态
                if (Up[elevator.curpos] || Down[elevator.curpos])
                {
                    elevator.movement = Opening;
                    elevator.movementTim = doorTIM;
                }
            }
        }
        else if (elevator.movement == Waiting)
        {
            int i = LowerRequests(&elevator);
            int j = HigherRequests(&elevator);
            // 如果请求在本层则切换到开门
            if (j == elevator.curpos)
            {
                elevator.movement = Opening;
                elevator.movementTim = doorTIM;
            }
            // 如果请求在高层则切换到加速并把State设置为GoingUp
            else if (j != -1)
            {
                elevator.movement = Accelerating;
                elevator.movementTim = accelerateTIM;
                elevator.State = GoingUp;
            }
            // 如果请求在低层则切换到加速并把State设置为GoingDown
            else if (i != -1)
            {
                elevator.movement = Accelerating;
                elevator.movementTim = accelerateTIM;
                elevator.State = GoingDown;
            }
        }
        if (!elevator.movementTim)
        {
        	printf("电梯现在在%d 楼\n",elevator.curpos);
        	Controller(&elevator);
            ChangeMovement(&elevator); 
    	}
		// 如果不为0,则计时减小
        else
            elevator.movementTim --;
        makegraph(&elevator);
    }
    
    
    return 0;
}