#include <Windows.h>
#include <conio.h>
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef enum Status
{
    Error = 0, 
	Success = 1
} Status;

//��Ӧ�������� 
typedef enum 
{
	UP = 72,
	DOWN = 80 ,
	LEFT = 75 ,
	RIGHT = 77 ,
	ENTER = 13 ,
	ESC = 27 ,
}key_board;

typedef int ElemType;

typedef  struct StackNode
{
	ElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;
	int	count;
}LinkStack;



//��ջ
Status initLStack(LinkStack *s);//��ʼ��ջ
Status isEmptyLStack(LinkStack *s);//�ж�ջ�Ƿ�Ϊ��
Status getTopLStack(LinkStack *s,ElemType *e);//�õ�ջ��Ԫ��
Status clearLStack(LinkStack *s);//���ջ
Status destroyLStack(LinkStack *s);//����ջ
Status LStackLength(LinkStack *s,int *length);//���ջ����
Status pushLStack(LinkStack *s,ElemType data);//��ջ
Status pushLStack_IxD(LinkStack *s);//��ջ���������� 
Status popLStack(LinkStack *s,ElemType *data);//��ջ
Status printStack(LinkStack * s);//��� 
extern char *menu[];
void showmenu(HANDLE hOut ,char **menu , int size , int index);
int  get_userinput(int *index , int size);
#endif 
