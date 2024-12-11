#ifndef Elevator_H

#define Elevator_H

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <graphics.h>
#include <windows.h>



#define t 1
#define True -1
#define False 0
#define OK 1
#define Error 0
#define Infeasible -1
#define Overflow -2
#define MaxNum 10
typedef int Status;
#define MaxTime 4000


#define testTIM 4           // ���Լ��
#define doorTIM 2           // ����������ʱ��
#define PeopleInAndOutTIM 2 // �˿ͽ���
#define upstairsTIM 2       // ������¥
#define waitTIM 0          // ��ȴ�ʱ��
#define downstairsTIM 2     // ������¥
#define accelerateTIM 3     // ����ʱ��
#define slowdownTIM 3       // ����ʱ��



// ���ݵ��˶�
typedef enum ElevatorMove
{
    Opening,      // ���ڿ���
    Opened,       // �Ѿ�����
    Closing,      // ���ڹ���
    Closed,       // �Ѿ�����
    Moving,       // �����ƶ�
    Waiting,      // �ȴ��˿�
    Accelerating, // ���ڼ���
    SlowingDown,  // ���ڼ���
} ElevatorMove;

/* ���ݵ��˶�״̬ */
typedef enum ElevatorState
{
    GoingUp,   // ����
    GoingDown, // �½�
    Free,      // ����
} ElevatorState;

/* �˿͵Ľڵ���Ϣ */
typedef struct ClientNode
{
    int occurTime;  // �³˿͵���ʱ��
    int ClientID;   // �˿�ID
    int Infloor;    // ��ʼ¥��
    int OutFloor;   // Ŀ��¥��
    int GiveupTime; // ��ȴ�ʱ��
} Client;

/* �˿�ջ */
typedef struct ClientStackNode
{
    Client base[MaxNum]; // �˿�ջ�Ļ���
    int top;             // ջ��ָ��
}ClientStack;

/* �ȴ����� */
typedef struct ClientQueueNode
{
    Client passenger;             // �˿�
    struct ClientQueueNode *next; // ��һ���˿�
}ClientQueueNode;

typedef struct WaitQueue
{
    ClientQueueNode *front;
    ClientQueueNode *rear;
    int WaitNum;
} WaitQueue;

/* ���ݽṹ�� */
typedef struct ElevatorNode
{
    int Passnum;         // ��ǰ�˿�����
    ElevatorState State;   // ���ݵ�ǰ״̬
    int curpos;          // ��ǰ��������¥��
    ElevatorMove movement; // ��ǰ���ݵ��˶�״̬
    int movementTim;       // ��ǰ״̬ʣ��ʱ��
    int CallCar[5];        // Ŀ�ĵ�
    ClientStack Stack[5];  // �˿�ջ
    int Isstandby;                // ֵΪ0,��������Ѿ���ĳ��ͣ��300t
	int doorstate;  //�ŵ�״̬��0Ϊopening��1Ϊopened��2Ϊclosing��3Ϊclosed 
} Elevator;

/*******************************************************************************************/

/**
 * @brief һЩȫ�ֱ��� 
 */
/*******************************************************************************************/
// ��ʱ�������
int Time = 0;
// ��¼�˿͵�ID
int ID;
// �����˿͵ļ��
int InterTime = 0;
// ���е�������
int Up[5];
// ���е�������
int Down[5];
// 2*5�ȴ�����
WaitQueue Queue[2][5];
/*******************************************************************************************/

/**
 * @brief һЩ��������
 */
/*******************************************************************************************/

/**
 * @brief ��ջ������
 */
/*********************************************/
// �ж϶�ջ�Ƿ�Ϊ��
Status StackEmpty(ClientStack S);
// ��ջ
Status Pop(ClientStack *S, Client *temp);
// ��ջ
Status Push(ClientStack *S, Client temp);
/*********************************************/

/**
 * @brief ���е�����
 */
/*********************************************/
// ��ʼ������
Status InitQueue(WaitQueue *Q);
// ���
Status Enqueue(WaitQueue *Q, Client temp);
// ����
Status Dequeue(WaitQueue *Q, Client *temp);
// ����CallUp��CallDown����
void Update(void);
// ��ʼ���ȴ�����
Status InitWaitQueue();
/*********************************************/

/**
 * @brief �˿͵�����
 */
/*********************************************/
// �����³˿�
Status Newclient();
// ɾ��������ȴ�ʱ��ĳ˿�
Status ClientGiveUp();
// �˿ͳ�����ջ
Status ClientOut(Elevator *elevator);
// �˿ͽ�����ջ
Status ClientIn(Elevator *elevator);
// �жϵ�ǰ¥����û�˿͵ȴ�
Status IfPeopleIn(Elevator *elevator);
/*********************************************/

/**
 * @brief ���ݵ�����
 */
/*********************************************/
// ��ʼ������
Status InitElevator(Elevator *elevator);
// ���ݿ���ʱ�ĵ�����
Status Controller(Elevator *elevator);
// �ı��ж�
Status ChangeMovement(Elevator *elevator);
// �߲�����
int HigherRequests(Elevator *elevator);
// �Ͳ�����
int LowerRequests(Elevator *elevator);
// ��¥
Status DownStairs(Elevator *elevator);
// ��¥
Status Upstairs(Elevator *elevator);
// ���ر��ݲ�
Status BackToBase(Elevator *elevator);
// ȡ��D2
Status CancelD2(Elevator *elevator);
// �ı�״̬
void ChangeState(Elevator *elevator);
/*********************************************/

/*******************************************************************************************/

#endif // !Elevator_H
