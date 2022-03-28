#include "../head/LinkStack.h" 
#include <Windows.h>
#include <conio.h>
#include<stdio.h>
#include <malloc.h>
//��ջ

//��ʼ��ջ
Status initLStack(LinkStack *s){
	StackNode *node = (StackNode*)malloc(sizeof(StackNode));
	node->next = NULL;
	node->data = 0;
	s->count = 0;
	s->top = node; 
	printf("��ʼ���ɹ�\n"); 
	return SUCCESS;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack *s){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n");
		return Error; 
	}
	if(s->count == 0){
		printf("��ջΪ��\n");
		return Success;
	}else{
		printf("��ջ��Ϊ��\n");
		return Error;
	}
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack *s,ElemType *e){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n");
		return Error; 
	}
	if(s->top->next == NULL){
		printf("��ջû��ջ��Ԫ��\n"); 
		return Error;
	}
	*e = s->top->next->data;
	printf("ջ��Ԫ��Ϊ%d\n",*e);
	return Success;
}

//���ջ
Status clearLStack(LinkStack *s) {
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}
	if(s->top->next == NULL) {
		printf("ջ�Ѿ����\n"); 
	}
	StackNode *p = s->top->next;
	StackNode *q = p;
	while(p!=NULL){
		p = p->next;
		free(q);
		q = p;
	}
	s->count = 0;
	s->top->next=NULL;
	return Success;
}	

//����ջ
Status destroyLStack(LinkStack *s){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}

	StackNode *p = s->top;
	while(s->top!=NULL){
		s->top = s->top->next;
		free(p);
		p=s->top;
	}
	free(s->top);
	s->top = NULL;
	printf("ջ�Ѵݻ�\n"); 
}

//���ջ����
Status LStackLength(LinkStack *s,int *length){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}
	*length = s->count;
	printf("ջ����Ϊ%d\n",*length);
	return Success;
}

//��ջ
Status pushLStack(LinkStack *s,ElemType data){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}
	StackNode *node =  (StackNode *)malloc(sizeof(StackNode));
	node->data = data;
	node->next = s->top->next;
	s->top->next = node;
	s->count++;
	return Success;
}

//��ջ������������ 
Status pushLStack_IxD(LinkStack *s){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}
	printf("����������:\n"); 
	int data;
	while(scanf("%d",&data)!=1){
		printf("����������:\n");
		while (getchar() != '\n');
	}
	pushLStack(s,data);
	printf("��ջ�ɹ�\n");
}

//��ջ
Status popLStack(LinkStack *s,ElemType *data){
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}
	if(s->top->next == NULL) {
		printf("ջΪ��ջ\n"); 
		return Error;
	}
	StackNode *p;
	*data = s->top->next->data;
	p = s->top->next;
	s->top->next = p->next;
	printf("��ջ�ɹ�����ջԪ��Ϊ%d\n",*data);
	free(p);
	s->count--;
	return Success;
}

//��ӡ
Status printStack(LinkStack * s)
{
	if(s->top == NULL){
		printf("���ȳ�ʼ��\n"); 
		return Error;
	}
	if(s->top->next == NULL) {
		printf("ջΪ��ջ\n");
		return Error; 
	}
	StackNode *p = s->top->next;

	while(p!=NULL){
		printf("%d\n",p->data);
		p=p->next;
	}
	return Success;
}
 
char *menu[] = 
{
	"---��ʼ����ջ---",
	"--���ջ��Ԫ��--",
	"�ж���ջ�Ƿ�Ϊ��",
	"--- ��ջ���� ---",
	"----- ��ջ -----",	
	"----- ��ջ -----",	
	"--- �����ջ ---",	
	"--- �ݻ���ջ ---",
	"--- �����ջ ---",	
	"---   �˳�   ---",
};

void showmenu(HANDLE hOut ,char **menu , int size , int index)
{
	COORD pos = {0,0};	//����Ĭ�ϵ�����λ��

	int i ;
	//system("cls");//���� 
	for(i = 0 ; i <size ; i++)
	{
		//���i==index��ʾ�ڵ�ǰѡ���λ�ã�Ĭ�ϳ�ʼ����ʾ�ǵ�һ����� 
		//���������°���ѡ���ʱ�򣬹����ƶ���Ҳ�Ϳ������б�ѡ������� 
		if(i == index)
		{
			//��ɫ 
			SetConsoleTextAttribute(hOut,BACKGROUND_RED |
                            BACKGROUND_GREEN |
                            BACKGROUND_BLUE); 
			pos.X = 0;
    		pos.Y = i;
    		SetConsoleCursorPosition(hOut,pos); 
    		//���ù������	   
    		printf("%s",menu[i]);
		}
		//������ʾΪ��ɫ
		else
		{
			//��ɫ 
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | 
                            FOREGROUND_GREEN | 
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY); 
			pos.X = 0;
    		pos.Y = i;
    		//���ù������
    		SetConsoleCursorPosition(hOut,pos);    //���ù������	   
    		printf("%s",menu[i]);
		}
		printf("%\n");
	}

}

//��ȡ�û�����Ľӿ� 
int  get_userinput(int *index , int size)//&index , NR(menu)
{
	int ch ;
	ch = getch();
	switch(ch)
	{
		//�� 
		//���ѡ���ϣ���ô��������ƶ� 
		case UP : if(*index > 0)  *index -= 1 ;  break; 
		//�� 
		//���ѡ���£���ô��������ƶ� 
		case DOWN :if(*index < size -1)  *index += 1 ;  break;
		//�� 
		//�س� 
		case ENTER: return ENTER ;
		//ESC
		case ESC: return ESC ;
	}
	return 0 ;
}

