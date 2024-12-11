#include "elevator.h"


Status InitElevator(Elevator *elevator)
{
    // ��ʼ��CallCar�Լ�Up��Down
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

Status Controller(Elevator *elevator)//״̬��
{
    int highrequest = HigherRequests(elevator);
    int lowrequest = LowerRequests(elevator);  
    int nextpos = -1; // ��һĿ��

    if(elevator->State == Free)
    {    
        // ���¥��¥�¶���������ѡ�����������
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

    //�������������
        if (nextpos == -1)//û����
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
        	//�����ǰ¥������
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
        	//�����ǰ¥������
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
        printf("�����Ŵ�\n");
        elevator->movementTim = testTIM;
        break;

    case Opened:
        // ����������ջ����
        elevator->doorstate = 1;
        if (StackEmpty(elevator->Stack[elevator->curpos]) == False)//����Ҫ�ڱ�¥����¥ 
        {
            ClientOut(elevator);
            elevator->movementTim = PeopleInAndOutTIM;
            printf("�˿����ڳ�����\n");
        }
        // �˿Ͷ���ջ��/û��Ҫ��ȥ�� ������һ���ж�
        else
        {
            elevator->CallCar[elevator->curpos] = 0;
            // �������Ҫ�ڱ�¥�������ݲ��ҵ���δ��
            if (IfPeopleIn(elevator) && elevator->Passnum < MaxNum)
            {
                ClientIn(elevator);
                elevator->movementTim = PeopleInAndOutTIM;
            }
            // ���û�˵ȴ���ô������һ��״̬
            else
            {
                elevator->movement = Closing;
                printf("���������ڹر�\n");
                elevator->movementTim = doorTIM;
            }
        }
        break;

    case Closing:
    	elevator->doorstate = 2;
        elevator->movement = Closed;
        printf("�������Ѿ�����\n");
        break;

    case Closed:
    	elevator->doorstate = 3;
        // ���������,���õ���״̬Ϊ���ڼ���
        if (HigherRequests(elevator) != -1 || LowerRequests(elevator) != -1)
        {
            elevator->movement = Accelerating;
            elevator->movementTim = accelerateTIM;
            printf("���ݿ�ʼ����\n");
        }
        //��ǰ����û�����󣬸ı��˶�״̬
        else if (elevator->Passnum)
            ChangeState(elevator);
        // ���û��������û�����Ǿ͵ȴ�
        else
        {
            elevator->movement = Waiting;
            elevator->movementTim = waitTIM;
            // ��ʾ��Ϣ
            printf("�������� %d ¥�ȴ�\n", elevator->curpos);
        }
        break;

    case Moving:
        if (elevator->Isstandby)//�������ڷ��ر��ݲ�
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
            //�������ﱾ�ݲ�
            else
            {
                elevator->movement = SlowingDown;
                elevator->movementTim = slowdownTIM;
            }
        }
        else
        {
            // ��¼nextpos��ֵ
            int nextpos;
            // �������������¥�ͻ�ȡ¥�ϵ�����
            if (elevator->State == GoingUp)
                nextpos = HigherRequests(elevator);
            // �������������¥�ͻ�ȡ¥�µ�����
            else
                nextpos = LowerRequests(elevator);
            // ���Ӧ�ü���������ô���µ�ǰ״̬��ʱ�䲢��¥
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
            // ���Ӧ�ü���������ô���µ�ǰ״̬��ʱ�䲢��¥
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
        if (elevator->State == GoingDown)// ��ʱΪ��¥��ʱ
            elevator->movementTim = downstairsTIM;
        else if (elevator->State == GoingUp)// ��ʱΪ��¥��ʱ
            elevator->movementTim = upstairsTIM;
        break;

    case SlowingDown:
        if (!elevator->Isstandby)// �����������������
        {
            elevator->movement = Opening;
            elevator->movementTim = doorTIM;
        }
        else       // ����ǻص����ݲ���ȴ�
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
    // ����״̬��ΪGoingUp����Wating���ܿ�����¥
    if (elevator->State == GoingUp || elevator->movement == Waiting || elevator->movement == Closed)
    {
        // �ҵ���ӽ�������
        int i;
		for (i = elevator->curpos+1 ; i < 5; i++)
            if (elevator->CallCar[i] || Up[i] || Down[i])
                // ������ӽ�������¥��
                return i;
    }
    return -1;
}

int LowerRequests(Elevator *elevator)
{
    // ����״̬��ΪGoingDown����Waiting����
    if (elevator->State == GoingDown || elevator->movement == Waiting)
    {
        // Ѱ���������
        int i;
		for (i = elevator->curpos-1; i >= 0; i--)
            if (elevator->CallCar[i] || Up[i] || Down[i])
                // ���������¥��
                return i;
    }
    // û�ҵ��򷵻�-1
    return -1;
}

void ChangeState(Elevator *elevator)
{
	int i;
	int temp = 0;
    if (elevator->Passnum >= MaxNum)
        return;
    
    // ��¥���Ƿ�������
	
    for (i = elevator->curpos + 1; i < 5; i++)
        if (elevator->CallCar[i] || Up[i])
            temp = 1;
    // ���¥��û�������ҵ�ǰ�������г˿�,��ô����State��Ҫ�ı�
    if (elevator->Passnum && !temp)
        elevator->State = GoingDown;
    temp = 0;
    // ��¥���Ƿ�������
	for (i = elevator->curpos - 1; i >= 0; i--)
        if (elevator->CallCar[i] || Down[i])
            temp = 1;
    // ���¥��û�������ҵ�ǰ�������г˿�,��ô����State��Ҫ�ı�
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
    // ��ʾ�ȴ�ʱ���Ѿ�����300s
    //elevator->Isstandby = 1;

    // �����ǰ�ڱ��ݲ����������
    if (elevator->curpos == 1)
    {
        elevator->movement = Waiting;
        printf("�����ڱ��ݲ�ȴ�\n");
        elevator->State = Free;
        elevator->movementTim = 0;
    }
    // ����ڱ��ݲ��·���׼���ص�һ¥
    else if (elevator->curpos < 1)
    {
        // ���õ��ݼ�������
        elevator->movement = Accelerating;
        // ��ʱ
        elevator->movementTim = accelerateTIM;
        // ��¥
        elevator->State = GoingUp;
    }
    // ����ڱ��ݲ��Ϸ���׼���ص�һ¥
    else
    {
        // ���õ��ݼ�������
        elevator->movement = Accelerating;
        // ��ʱ
        elevator->movementTim = accelerateTIM;
        // ��¥
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
    // �����ڴ�ռ�
    Q->front = Q->rear = (ClientQueueNode *)malloc(sizeof(ClientQueueNode));
    Q->front->next = NULL;
    // ��ʼ���ȴ�����Ϊ0
    Q->WaitNum = 0;
    return OK;
}

Status Enqueue(WaitQueue *Q, Client temp)
{
    // �����µ��ڴ�ռ�
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
    // �������Ϊ��ֱ�ӷ���
    if (Q->WaitNum == 0)
        return Error;
   	
	Q->front = Q->front->next;
	*temp = Q->front->passenger;

	free(ptr);
	Q->WaitNum --;
	return OK;
	
//    //ȡ���˿� 
//    ptr = Q->front->next;
//    //��һ������ĳ˿�  
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
    // �����ȴ�����
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (!i) // i����0������¥�ȴ�����
            {
                if (Queue[i][j].WaitNum == 0)   // ���û�˵ȴ�Up������Ϊ0
                    Up[j] = 0;
        	}
            else// i����1������¥�ȴ�����
            {
                if (Queue[i][j].WaitNum == 0)// ���û�˵ȴ�Down������Ϊ0
                    Down[j] = 0;
        	}
		}
    }
    return;
}

//�˿ͽ�����
Status Pop(ClientStack *S, Client *temp)
{
    *temp = S->base[S->top--];
    return OK;
}

//�˿ͳ�����
Status Push(ClientStack *S, Client temp)
{
    //if (S->top < MaxNum)
        S->base[++S->top] = temp;
    return OK;
}

//�жϳ˿�ջ�Ƿ�Ϊ�� ÿ��һ��ջ��Ҳ����������֮��� ����ν��
Status StackEmpty(ClientStack S)
{
    // ���ջ��Ϊ-1����True
    if (S.top == -1)
        return True;
    // ���򷵻�False
    return False;
}

Status Newclient()
{
    Client NewClient;
    NewClient.occurTime = Time;                     // �³˿͵���ʱ��
    NewClient.ClientID = ++ID;                      // �³˿͵�ID
    NewClient.Infloor = rand() % 5;                 // �³˿���ʼ¥��
    NewClient.OutFloor = rand() % 5;                // �³˿�Ŀ��¥��
    NewClient.GiveupTime = 20 + rand() % 30;      // ��ȴ�ʱ��
    InterTime = rand() % 30;                        // ��һ���˿͵���ʱ����
    while (NewClient.Infloor == NewClient.OutFloor) // ����³˿ͳ����غ�Ŀ�����ͬ�����·���
        NewClient.OutFloor = rand() % 5;
    // �������¥������Ӧ����¥�ȴ�����
    if (NewClient.Infloor < NewClient.OutFloor)
    {
        Enqueue(&Queue[0][NewClient.Infloor], NewClient);
        printf("%d �ų˿��� %d ¥�ȴ���¥\n", NewClient.ClientID, NewClient.Infloor);
        Up[NewClient.Infloor] = 1;
    }
    else
    {
        Enqueue(&Queue[1][NewClient.Infloor], NewClient);
        printf("%d �ų˿��� %d ¥�ȴ���¥\n", NewClient.ClientID, NewClient.Infloor);
        Down[NewClient.Infloor] = 1;
    }
	return 0;
}

//�����ȴ�ʱ��ĳ˿�
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
                // ��������ȴ�ʱ��
                if (ptr->passenger.occurTime + ptr->passenger.GiveupTime <= Time)
                {
                    // �˿ͳ���
                    pre->next = ptr->next;
                    printf("�ȴ�ʱ�������%d �ų˿��뿪�� %d ¥\n", ptr->passenger.ClientID, ptr->passenger.Infloor);
                    free(ptr);
                    ptr = pre->next;
                    Queue[i][j].WaitNum--;// �Ŷ���������
                }
                else
                {
                    pre = ptr;
                    ptr = ptr->next;
                }
            }
        }
    }
    // ����Up��Down����
    Update();
	return 0;
}

Status ClientOut(Elevator *elevator)
{
    // ��ǰ¥��ĳ˿�ջ����,����ճ˿�ջ
    if (elevator->Stack[elevator->curpos].top != -1)
    {
        Client temp;
        Pop(&elevator->Stack[elevator->curpos], &temp);
        printf("%d �ų˿��� %d ¥�µ���\n", temp.ClientID, temp.OutFloor);
        elevator->Passnum--;
        Time += PeopleInAndOutTIM * t;
    }
    Update();
	return 0;
}

Status IfPeopleIn(Elevator *elevator)
{
    // �����������
    if (elevator->State == GoingUp)
    {
        if (Up[elevator->curpos]) // ������˵ȴ�
            return True;
        // ��������Ѿ��ȴ�300s�����˵ȴ��ͷ���True
        if (!elevator->Passnum && Down[elevator->curpos])
            return True;
    }
    // �����������
    else if (elevator->State == GoingDown)
    {
        // ������˵ȴ�����True
        if (Down[elevator->curpos])
            return True;
        // �����һ��״̬ΪFree�����˵ȴ��ͷ���True
        if (!elevator->Passnum && Up[elevator->curpos])
            return True;
    }
    else if (Down[elevator->curpos] || Up[elevator->curpos])
            return True;
    // û�˵ȴ�����False
    return False;
}

Status ClientIn(Elevator *elevator)
{
    if (elevator->State == Free)
    {
        if (Up[elevator->curpos])
        {
            Client temp;
            Dequeue(&Queue[0][elevator->curpos], &temp);// �ӵȴ�������ȡ���˿�
            Push(&elevator->Stack[temp.OutFloor], temp);// �˿���ջ
            elevator->CallCar[temp.OutFloor] = 1;// ����Ŀ�ĵ�
            printf("%d �ų˿��� %d ¥�������\n", temp.ClientID, elevator->curpos);
        }
        else if(Down[elevator->curpos])
        {
            Client temp;
            Dequeue(&Queue[1][elevator->curpos], &temp);
            Push(&elevator->Stack[temp.OutFloor], temp);
            elevator->CallCar[temp.OutFloor] = 1;
            printf("%d �ų˿��� %d ¥�������\n", temp.ClientID, elevator->curpos);
        }
    }
    else if (elevator->State == GoingUp)
    {
        // �����һ״̬���ǿ��е�,��ôֻ�ܽ����н�״̬��ͬ�ĳ˿�
        Client temp;
        Dequeue(&Queue[0][elevator->curpos], &temp);
        Push(&elevator->Stack[temp.OutFloor], temp);
        elevator->CallCar[temp.OutFloor] = 1;
        printf("%d �ų˿��� %d ¥�������\n", temp.ClientID, elevator->curpos);
    }
    else
    {
        Client temp;
        Dequeue(&Queue[1][elevator->curpos], &temp);
        Push(&elevator->Stack[temp.OutFloor], temp);
        elevator->CallCar[temp.OutFloor] = 1;
        printf("%d �ų˿��� %d ¥�������\n", temp.ClientID, elevator->curpos);
    }
    // ���ݳ˿�����
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

	settextstyle(25, 0, "����");//��������߶ȣ���ȣ�����
    setbkmode(TRANSPARENT);//�������屳��͸����Ĭ�ϲ�͸��
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
 

    char arr_1[] = "��������˿�";
    outtextxy(210,10, arr_1);
	char arr_2[] = "�ȴ��еĳ˿�";
    outtextxy(580,10, arr_2);

	//���ݵ�λ��
	IMAGE door_img;
	int y_ele = 350 - elevator->curpos * 75;
	if(elevator->movement == Closing || elevator->movement == Opened)
		loadimage(&door_img,_T("opened.png"), 100, 75);
	else
		loadimage(&door_img,_T("closed.png"), 100, 75);
	putimage(350, y_ele, &door_img, SRCINVERT);
	

	//�����еĳ˿�
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
	
	
	//�ȴ��ĳ˿�
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
        // ���ڹ��Ż��ߵȴ�ʱ������ֳ˿���������
        if (elevator.movement == Closing)
        {
            // �����ǰ���ݲ�Ϊ��,�������ͬ�н�����ĳ˿�����ջ
            if (elevator.Passnum && elevator.Passnum < MaxNum)
            {
                // �����ǰ��������,�����ϵĳ˿����л�������
                if (elevator.State == GoingUp)
                {
                    if (Up[elevator.curpos])
                    {
                        elevator.movement = Opening;
                        elevator.movementTim = doorTIM;
                    }
                }
                // �����ǰ��������,�����µĳ˿����л�������
                else if (elevator.State == GoingDown)
                {
                    if (Down[elevator.curpos])
                    {
                        elevator.movement = Opening;
                        elevator.movementTim = doorTIM;
                    }
                }
            }
            // �����ǰ����Ϊ��
            else if (!elevator.Passnum)
            {
                // ֻҪ���������л�������״̬
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
            // ��������ڱ������л�������
            if (j == elevator.curpos)
            {
                elevator.movement = Opening;
                elevator.movementTim = doorTIM;
            }
            // ��������ڸ߲����л������ٲ���State����ΪGoingUp
            else if (j != -1)
            {
                elevator.movement = Accelerating;
                elevator.movementTim = accelerateTIM;
                elevator.State = GoingUp;
            }
            // ��������ڵͲ����л������ٲ���State����ΪGoingDown
            else if (i != -1)
            {
                elevator.movement = Accelerating;
                elevator.movementTim = accelerateTIM;
                elevator.State = GoingDown;
            }
        }
        if (!elevator.movementTim)
        {
        	printf("����������%d ¥\n",elevator.curpos);
        	Controller(&elevator);
            ChangeMovement(&elevator); 
    	}
		// �����Ϊ0,���ʱ��С
        else
            elevator.movementTim --;
        makegraph(&elevator);
    }
    
    
    return 0;
}