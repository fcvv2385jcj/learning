#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<stdlib.h>
#include"../Headers/dulinkedList.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0)) //菜单长度 

//初始化 
Status InitList_DuL(DuLinkedList *L) {
	*L = (DuLinkedList)malloc(sizeof(DuLinkedList));
	if((*L)==NULL){
		return Error;
	}
	printf("初始化成功\n");
	(*L)->prior = (*L)->next = NULL;
	return SUCCESS;	
}

//输入数据 
void CreateLinkList(DuLinkedList L){
    ElemType n;
    DuLinkedList p = L;
    printf("请输入要构建的节点数：");
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        DuLNode* q = (DuLNode*)malloc(sizeof(DuLNode));
        p->next = q;
        printf("请输入第%d个元素的值：",i);
        scanf("%d",&(q->data));
        q->prior = p;
        q->next = NULL;
        p = q;
    }
}
//摧毁链表 
void DestroyList_DuL(DuLinkedList *L) {
	DuLNode *p=(*L);
	while(p){
		p=p->next;
		free(*L);
		(*L)=p;
	}
}
//搜索节点 
DuLNode* SearchDuList(DuLinkedList L, ElemType e) {
	if(L->next == NULL) {
		return L;
	}
	DuLNode*p = L->next;
	while(p ->next != NULL){
		p = p->next;
		if(p->data == e){
			return p;
		}
	}
	return NULL;
}
//从前插入 
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
		if(p == NULL||q == NULL||p->prior == NULL){
			return Error;
		}
		q->next = p;
		q->prior = p->prior;
		p->prior->next = q;
		p->prior = q;
		return SUCCESS;
}
 
//从后插入 
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if(p == NULL||q == NULL) {
		return Error;
	}
	q->next = p->next;
	q->prior=p;
	p->next->prior = q;
	p->next=q; 	
	return SUCCESS;
}
//从后插入 （包括交互） 
void InsertDuNode_back(DuLNode *L){
	ElemType data; //插入的节点前一个值 
	DuLNode *p; //该值所在节点 
	
	ElemType i_data;
	DuLNode *q = (DuLNode*)malloc(sizeof(DuLNode));//待插入节点 
	
	printf("请输入要插入的值：");
	scanf("%d",&i_data);
	printf("请输入要插到哪个值后面：");
	scanf("%d",&data);
	q->data = i_data;
	p = SearchDuList(L,data);
	if(p!=NULL){
		if(InsertAfterList_DuL(p,q)){
			printf("插入成功\n"); 
		}else{
			printf("插入失败\n"); 
		}
	} 
	
}
//从前插入（包括交互） 
void InsertDuNode_front(DuLNode *L){
	ElemType data; //插入节点的前一个节点的值 
	DuLNode *p; //该值所在节点 
	
	ElemType i_data;//待插入节点的值 
	DuLNode *q = (DuLNode*)malloc(sizeof(DuLNode));//待插入节点 
	
	printf("请输入要插入的值：");
	scanf("%d",&i_data);
	printf("请输入要插到哪个值前面：");
	scanf("%d",&data);
	q->data = i_data;
	p = SearchDuList(L,data);//搜索p节点 
	if(p!=NULL){
		if(InsertBeforeList_DuL(p,q)){
			printf("插入成功\n"); 
		}else{
			printf("插入失败\n"); 
		}
	} 
	
}
//删除节点 （包括交互） 
Status DeleteDul_node(DuLinkedList L){
	printf("请输入要删除的节点：");
	ElemType e;//要删除的数据 
	scanf("%d",&e); 
	DuLNode* p; //找到该数据的节点 
	p = SearchDuList(L, e);
	if(DeleteList_DuL(p->prior,&e)){
		printf("删除成功\n");
	}else{
		printf("删除失败"); 
	} 
}
//删除节点 
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
	if(p == NULL) {
		return Error;
	}
	DuLNode *q = p->next;
	*e = p->next->data;
	p->next = p->next->next;
	if(q->next!=NULL){
		q->next->prior = p;
	}
	free(q);
	return SUCCESS;
}
 
//输出链表 
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	DuLNode *p = L->next;
	while(p){
		visit(p->data);
		p = p->next;
	}
}

void visit(ElemType e){
	printf("%d->",e);
} 

enum 
{
	UP = 72,
	DOWN = 80 ,
	LEFT = 75 ,
	RIGHT = 77 ,
	ENTER = 13 ,
	ESC = 27 ,
};

char *menu[] = 
{
	"---创建新链表---",
	"--- 输出链表 ---",
	"--- 删除元素 ---",
	"--从前插入元素--",
	"--从后插入元素--",
	"--- 清空链表 ---",
	"---   退出   ---",
};

CONSOLE_CURSOR_INFO cci; //定义光标信息（大小dwSize，可见度bVisible） 
//定义默认的坐标位置  	
COORD pos = {0,0};
//显示菜单 
void showmenu(HANDLE hOut ,char **menu , int size , int index) ;
//获取用户输入 
int  get_userinput(int *index , int size) ;

void showmenu(HANDLE hOut ,char **menu , int size , int index)
{
	int i ;
	//system("cls");//清屏 
	for(i = 0 ; i < size ; i++)
	{
		//如果i==index表示在当前选项的位置，默认初始化显示是第一项，高亮 
		//当按下上下按键选择的时候，光标会移动，也就看到了列表选择的现象 
		if(i == index)
		{
			//灰色 
			SetConsoleTextAttribute(hOut,BACKGROUND_RED |
                            BACKGROUND_GREEN |
                            BACKGROUND_BLUE); 
			pos.X = 0;
    		pos.Y = i;
    		//设置光标坐标
    		SetConsoleCursorPosition(hOut,pos);    
    		printf("%s",menu[i]);
		}
		//否则显示为白色 
		else
		{
			//白色 
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

int main(){
	DuLinkedList L = NULL;
	DuLNode *node;
	int ret ;
    int index = 0 ;
    HANDLE hOut;
    //获取当前的句柄---设置为标准输出句柄 
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //获取光标信息
    GetConsoleCursorInfo(hOut, &cci); 
	//设置光标大小   
    cci.dwSize = 1; 
	//设置光标不可见 FALSE   
    cci.bVisible =  0; 
    //设置(应用)光标信息
    SetConsoleCursorInfo(hOut, &cci);   
    while(1)
    {
    	//键盘输入 
    	showmenu(hOut , menu , NR(menu) , index);
		ret = get_userinput(&index , NR(menu));
		if(ret == ESC)
			break ;
		if(ret == ENTER)
		{	
			switch(index)
			{
				case 0: InitList_DuL(&L); CreateLinkList(L);system("pause"); break ; //创建新链表 
				case 1: TraverseList_DuL(L, visit);printf("NULL\n");system("pause");  break ; //输出链表 
				case 2: DeleteDul_node(L); system("pause");  break ; //删除数据 
				case 3: InsertDuNode_front(L); system("pause");   break ; //从前插入数据 
				case 4: InsertDuNode_back(L); system("pause");   break ; //从后插入数据 
				case 5: DestroyList_DuL(&L); system("pause");   break ; //翻转链表				
				case 6: SetConsoleTextAttribute(hOut,  //设置颜色防止异常 
                            FOREGROUND_RED | 
                            FOREGROUND_GREEN | 
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY);  system("cls");      return 0 ;//退出
			}
			system("cls");
		}
	}
	system("cls");//清屏 
	return 0;
}
