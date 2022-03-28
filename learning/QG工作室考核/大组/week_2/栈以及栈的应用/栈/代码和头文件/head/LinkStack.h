#include <Windows.h>
#include <conio.h>
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef enum Status
{
    Error = 0, 
	Success = 1
} Status;

//对应键盘输入 
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



//链栈
Status initLStack(LinkStack *s);//初始化栈
Status isEmptyLStack(LinkStack *s);//判断栈是否为空
Status getTopLStack(LinkStack *s,ElemType *e);//得到栈顶元素
Status clearLStack(LinkStack *s);//清空栈
Status destroyLStack(LinkStack *s);//销毁栈
Status LStackLength(LinkStack *s,int *length);//检测栈长度
Status pushLStack(LinkStack *s,ElemType data);//入栈
Status pushLStack_IxD(LinkStack *s);//入栈（含交互） 
Status popLStack(LinkStack *s,ElemType *data);//出栈
Status printStack(LinkStack * s);//输出 
extern char *menu[];
void showmenu(HANDLE hOut ,char **menu , int size , int index);
int  get_userinput(int *index , int size);
#endif 
