typedef enum Status 
{
    Error = 0, 
	Success = 1
} Status;

//typedef void *ElemType;
typedef int ElemType;
typedef  struct StackNode
{
	ElemType data;
	struct StackNode *next;
}StackNode;

typedef  struct  LinkStack
{
	StackNode* top;
	int	count;
}LinkStack;

int compute(LinkStack *res, char type);//提取栈的两个数字进行计算 
Status priority(char a, char b);  //符号优先级判断 
Status init(LinkStack *s);  //初始化栈 
Status push(LinkStack *s,ElemType data);//入栈
Status pop(LinkStack *s);//出栈
Status empty(LinkStack *s); //判断栈是否为空 
Status detection(char *str);//检测输入字符串是否合法 
int top(LinkStack *s); //输出栈顶的元素 

//将数字压入栈res  符号压入栈mid  当符号压入res时直接弹出res的头2个元素 进行计算后再压入栈res 
int computer(char *s);  //计算 
