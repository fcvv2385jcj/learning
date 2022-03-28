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

int compute(LinkStack *res, char type);//��ȡջ���������ֽ��м��� 
Status priority(char a, char b);  //�������ȼ��ж� 
Status init(LinkStack *s);  //��ʼ��ջ 
Status push(LinkStack *s,ElemType data);//��ջ
Status pop(LinkStack *s);//��ջ
Status empty(LinkStack *s); //�ж�ջ�Ƿ�Ϊ�� 
Status detection(char *str);//��������ַ����Ƿ�Ϸ� 
int top(LinkStack *s); //���ջ����Ԫ�� 

//������ѹ��ջres  ����ѹ��ջmid  ������ѹ��resʱֱ�ӵ���res��ͷ2��Ԫ�� ���м������ѹ��ջres 
int computer(char *s);  //���� 
