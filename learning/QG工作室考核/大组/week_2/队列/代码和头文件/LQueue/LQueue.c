#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<stdlib.h>
#include"../head/LQueue.h" 
char type;
char data_type[30];
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q){
	Q->front = Q->rear = (Node*)malloc(sizeof(Node));
	if(Q->front == NULL){
		printf("初始化失败\n");
		return ;
	}
	Q->front->next = NULL;
	Q->length = 0;
	printf("初始化成功\n"); 
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q){
	if(Q->front == NULL){
		printf("队列未初始化\n"); 
		return ;
	}
	Node *p = Q->front;
	Node *q = NULL;
	while(p!=NULL){
		q = p->next;
		free(p);
		p = q;
	}
	Q->front = NULL;
	Q->rear = NULL;
	printf("队列摧毁成功\n"); 
} 

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	if(Q->length==0){
		printf("队列为空\n"); 
		return True;
	}else{
		printf("队列不为空\n");
		return False;
	}
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	if(Q->front==NULL){
		printf("请先初始化\n"); 
		return False;
	}
	if(Q->front->next==NULL){
		printf("队头元素不存在\n");
		return False;
	}
	e = Q->front->next->data;
	type = data_type[1
	];
	LPrint(Q->front->next->data);
	return True;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q){
	printf("队列长度为:%d\n",Q->length);
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data){
	if(Q->front == NULL){
		return False;
	}
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = data;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	Q->length++;
	return True;
}
//包含交互 
void EnLQueue_IxD(LQueue *Q){
	if(Q->front==NULL){
		printf("请先初始化\n");
		return ; 
	}
	//输入的是第几个数 
	int l = Q->length+1;
	choose_type(l); //储存第len个节点的数据 
	printf("请输入数据:\n");
	//根据选择的类型插入数据 
	if(data_type[l] == 'a'||data_type[l] == 'A'){
		int *data = (int*)malloc(sizeof(int));
		while(scanf("%d",data)!=1){
			printf("请输入数字\n");
			while (getchar() != '\n');
		}
		EnLQueue(Q, data);
	}else if(data_type[l] == 'b'||data_type[l] == 'B'){
		char *data = (char*)malloc(sizeof(char));
		scanf("%s",data);
		EnLQueue(Q, data);
	}else if(data_type[l] == 'c'||data_type[l] == 'C'){
		float *data = (float*)malloc(sizeof(float));
		scanf("%f",data);
		EnLQueue(Q, data);
	}
	printf("储存成功\n"); 
}
/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	if(Q->front == Q->rear){
		printf("队列中没有元素\n"); 
		return False; 
	}
	Node *p = Q->front->next;
	Q->front->next = p->next;
	if(Q->rear == p){
		Q->rear = Q->front;
	}	
	Q->length--; //队列长度减一 
	free(p);
	printf("出队成功\n");
	//调整队列元素对应的类型 
	for(int j=1; j<=Q->length; j++){
		data_type[j] = data_type[j+1];
	}
	return True;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
	if(Q->front==NULL){
		printf("请先初始化队列\n"); 
		return;
	} 
	if(Q->front == Q->rear){
		printf("队列已清空\n");
		return;
	}
	Node *p = Q->front->next;
	Node *q = NULL;
	while(p!=NULL){
		q = p->next;
		free(p);
		p = q;
	}
	Q->front->next = NULL;
	Q->rear = Q->front; 
	Q->length = 0;
	printf("队列清空成功\n"); 
}

 /**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 
 *  @notice      : None
 */
 
void LPrint(void *q){
	//根据储存的类型打印 
	if(type == 'a'||type == 'A'){
		printf("%d\n",(*(int*)q));
	}else if(type == 'b'||type == 'B'){
		printf("%s\n",((char*)q));
	}else if(type == 'c'||type == 'C'){
		printf("%f\n",(*(float*)q));
	}
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*LPrint)(void *q)){
	if(Q->front==NULL||Q->front->next == NULL){
		printf("队列为空或尚未初始化\n"); 
		return False;
	}
	int j = 1;
	Node *p = Q->front->next;
	while(p!=NULL){
		type = data_type[j++]; 
		LPrint(p->data);
		p = p->next;
	}
	return True;
}
//选择储存的数据类型 
void choose_type(int len){
	printf("请选择你要存储的数据类型:  \nA:整型  \nB:字符或字符串型  \nC:浮点型\n");
	char a[50];
	//输入异常判断 
	while(1){
		printf("请输入A，B或C\n"); 
		scanf("%s",a);
		if((a[0]=='A'||a[0]=='B'||a[0]=='a'||a[0]=='b'||a[0]=='c'||a[0]=='C')&&strlen(a)<=1){
			break;
		}
	}
	data_type[len] = a[0];//储存第len个节点的数据 
}
//菜单 
char *menu[] = 
{
	"---初始化队列---",
	"--- 摧毁链表 ---",
	"判断队列是否为空",
	"- 查看队头元素 -",
	"--- 队列长度 ---",
	"--- 数据入队 ---",	
	"--- 数据出队 ---",
	"--- 清空队列 ---",	
	"--- 输出队列 ---",
	"---   退出   ---",
};


//显示菜单 
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

