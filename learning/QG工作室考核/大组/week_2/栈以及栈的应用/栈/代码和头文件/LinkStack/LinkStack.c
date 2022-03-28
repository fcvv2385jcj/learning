#include "../head/LinkStack.h" 
#include <Windows.h>
#include <conio.h>
#include<stdio.h>
#include <malloc.h>
//链栈

//初始化栈
Status initLStack(LinkStack *s){
	StackNode *node = (StackNode*)malloc(sizeof(StackNode));
	node->next = NULL;
	node->data = 0;
	s->count = 0;
	s->top = node; 
	printf("初始化成功\n"); 
	return SUCCESS;
}

//判断栈是否为空
Status isEmptyLStack(LinkStack *s){
	if(s->top == NULL){
		printf("请先初始化\n");
		return Error; 
	}
	if(s->count == 0){
		printf("链栈为空\n");
		return Success;
	}else{
		printf("链栈不为空\n");
		return Error;
	}
}

//得到栈顶元素
Status getTopLStack(LinkStack *s,ElemType *e){
	if(s->top == NULL){
		printf("请先初始化\n");
		return Error; 
	}
	if(s->top->next == NULL){
		printf("链栈没有栈顶元素\n"); 
		return Error;
	}
	*e = s->top->next->data;
	printf("栈顶元素为%d\n",*e);
	return Success;
}

//清空栈
Status clearLStack(LinkStack *s) {
	if(s->top == NULL){
		printf("请先初始化\n"); 
		return Error;
	}
	if(s->top->next == NULL) {
		printf("栈已经清空\n"); 
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

//销毁栈
Status destroyLStack(LinkStack *s){
	if(s->top == NULL){
		printf("请先初始化\n"); 
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
	printf("栈已摧毁\n"); 
}

//检测栈长度
Status LStackLength(LinkStack *s,int *length){
	if(s->top == NULL){
		printf("请先初始化\n"); 
		return Error;
	}
	*length = s->count;
	printf("栈长度为%d\n",*length);
	return Success;
}

//入栈
Status pushLStack(LinkStack *s,ElemType data){
	if(s->top == NULL){
		printf("请先初始化\n"); 
		return Error;
	}
	StackNode *node =  (StackNode *)malloc(sizeof(StackNode));
	node->data = data;
	node->next = s->top->next;
	s->top->next = node;
	s->count++;
	return Success;
}

//入栈（包含交互） 
Status pushLStack_IxD(LinkStack *s){
	if(s->top == NULL){
		printf("请先初始化\n"); 
		return Error;
	}
	printf("请输入数据:\n"); 
	int data;
	while(scanf("%d",&data)!=1){
		printf("请输入数字:\n");
		while (getchar() != '\n');
	}
	pushLStack(s,data);
	printf("入栈成功\n");
}

//出栈
Status popLStack(LinkStack *s,ElemType *data){
	if(s->top == NULL){
		printf("请先初始化\n"); 
		return Error;
	}
	if(s->top->next == NULL) {
		printf("栈为空栈\n"); 
		return Error;
	}
	StackNode *p;
	*data = s->top->next->data;
	p = s->top->next;
	s->top->next = p->next;
	printf("出栈成功，出栈元素为%d\n",*data);
	free(p);
	s->count--;
	return Success;
}

//打印
Status printStack(LinkStack * s)
{
	if(s->top == NULL){
		printf("请先初始化\n"); 
		return Error;
	}
	if(s->top->next == NULL) {
		printf("栈为空栈\n");
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
	"---初始化链栈---",
	"--获得栈顶元素--",
	"判断链栈是否为空",
	"--- 链栈长度 ---",
	"----- 入栈 -----",	
	"----- 出栈 -----",	
	"--- 清空链栈 ---",	
	"--- 摧毁链栈 ---",
	"--- 输出链栈 ---",	
	"---   退出   ---",
};

void showmenu(HANDLE hOut ,char **menu , int size , int index)
{
	COORD pos = {0,0};	//定义默认的坐标位置

	int i ;
	//system("cls");//清屏 
	for(i = 0 ; i <size ; i++)
	{
		//如果i==index表示在当前选项的位置，默认初始化显示是第一项，高亮 
		//当按下上下按键选择的时候，光标会移动，也就看到了列表选择的现象 
		if(i == index)
		{
			//白色 
			SetConsoleTextAttribute(hOut,BACKGROUND_RED |
                            BACKGROUND_GREEN |
                            BACKGROUND_BLUE); 
			pos.X = 0;
    		pos.Y = i;
    		SetConsoleCursorPosition(hOut,pos); 
    		//设置光标坐标	   
    		printf("%s",menu[i]);
		}
		//否则显示为灰色
		else
		{
			//灰色 
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | 
                            FOREGROUND_GREEN | 
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY); 
			pos.X = 0;
    		pos.Y = i;
    		//设置光标坐标
    		SetConsoleCursorPosition(hOut,pos);    //设置光标坐标	   
    		printf("%s",menu[i]);
		}
		printf("%\n");
	}

}

//获取用户输入的接口 
int  get_userinput(int *index , int size)//&index , NR(menu)
{
	int ch ;
	ch = getch();
	switch(ch)
	{
		//上 
		//如果选择上，那么光标向上移动 
		case UP : if(*index > 0)  *index -= 1 ;  break; 
		//下 
		//如果选择下，那么光标向下移动 
		case DOWN :if(*index < size -1)  *index += 1 ;  break;
		//左 
		//回车 
		case ENTER: return ENTER ;
		//ESC
		case ESC: return ESC ;
	}
	return 0 ;
}

