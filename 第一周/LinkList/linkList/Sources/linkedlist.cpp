#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<stdlib.h>
#include"../Headers/linkedList.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
//初始化参数 
Status InitList(LinkedList *L){
	if((*L)!=NULL){ //特殊情况判断 
		DestroyList(&(*L));
	}
	*L= (LNode*)malloc(sizeof(LNode));
    if(L == NULL){
        printf("初始化失败\n");
        return Error;
    }
    
    (*L)-> data = 0; //头结点数据为链表长度 
    printf("初始化成功\n");
    (*L)->next = NULL;
    int num_node = 0;//节点数
	ElemType value=0; //节点数据 
    LinkedList p = *L;		   //用于连接新节点 
	printf("请输入要构建的节点数："); //输入要构建的节点 
	scanf("%d", &num_node);
	
	for(int i =1; i <= num_node; i++) {
		printf("请输入第%d个节点：", i);
		scanf("%d",&value);
		LNode *node= (LNode*)malloc(sizeof(LNode));
		if(node == NULL){
        	printf("新增节点失败\n");
        	return Error;
    	}
    	node->data = value;
    	node->next = NULL; 
    	p->next = node;  //连接新节点 
    	p = node;
    	(*L)->data += 1; //令链表长度增加 
	}
    return SUCCESS;
}
//插入节点 
Status InsertList(LNode *p, LNode *q){
	if(p == NULL||q == NULL) {
		return Error;
	}
	q->next = p->next;
	p->next = q;
	return SUCCESS;
}
//插入节点（包括交互部分） 
void InsertNode(LNode* HeadNode){
	if(HeadNode == NULL || HeadNode->next == NULL){//特殊情况判断 
		printf("链表为空\n"); 
		return ;
	}
	ElemType p,q;
	printf("请输入想要插入的数据："); 
	scanf("%d",&q);
	printf("请输入要插到哪个数据之后："); 
	scanf("%d",&p);
	LNode *new_node = (LNode*)malloc(sizeof(LNode));//给新节点分配空间 
	new_node->data = q;
	new_node->next = NULL;
	LNode *p1 = HeadNode; //用于遍历寻找节点p 
	while(p1!=NULL){
		if(p1->data == p){
			InsertList(p1, new_node);
			printf("插入成功\n",p);
			HeadNode->data += 1;//令节点数加1 
			break;
		}
		p1 = p1->next;
	}
	if(p1==NULL){
		printf("插入失败，未能找到%d\n",p);
	}
}
//寻找中点 
LNode* FindMidNode(LinkedList *L){
	if((*L) == NULL||(*L)->next==NULL){
		printf("链表为空\n"); 
		return NULL;
	}
	
	int Lenlist = (*L)->data / 2 ;
	LNode *midnode = (*L)->next; 
	while(Lenlist--){
		midnode = midnode->next;
	}
	printf("中间值的数据为:%d\n",midnode->data);
	return midnode;
} 
//遍历输出 
void TraverseList(LinkedList L, void (*visit)(ElemType e)){
	LNode *p = NULL;
 
	if(L==NULL||L->next == NULL){
		printf("链表为空\n");
		return;
	}else{
		p = L->next;
	}
	while(p){
		visit(p->data);
		p = p->next;
	}
	printf("NULL\n");
}
//删除节点 
Status DeleteList(LNode *p, ElemType *e) {
	if(p == NULL||p->next == NULL){
		printf("链表为空\n"); 
		return Error;
	}
	LNode*q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	return SUCCESS;
}
//删除节点（包括交互） 
void DeleteNode(LNode* HeadNode){
	if(HeadNode == NULL||HeadNode->next == NULL){
		printf("链表为空\n"); 
		return ;
	}

	int delete_data;
	printf("%请输入要删除的数据："); 
	scanf("%d", &delete_data);
	if(HeadNode==NULL){
		printf("链表为空\n");
		return ;
	}

	LNode *p1;		//p1,p2用来寻找并处理删除的节点 
	LNode *p2;
	p1 = HeadNode;
	p2 = HeadNode->next;
	while(p2!=NULL){
		if(p2->data == delete_data){
			p1->next = p2->next;
			free(p2);
			HeadNode->data--; //令链表长度缩小 
			printf("删除成功\n"); 
			return;
		}
		p1=p2;
		p2=p1->next;
	}
	if(p2 == NULL){
		printf("不存在要删除的数据\n");
	} 
}
//查找数据 
Status SearchList(LinkedList L, ElemType e) {
	if(L->next == NULL) {
		return Error;
	}
	LNode*p = L->next;
	while(p ->next != NULL){
		p = p->next;
		if(p->data == e){
			return SUCCESS;
		}
	}
	return Error;
}
//查找数据（包括交互） 
Status SearchNode(LNode* HeadNode){
	if(HeadNode == NULL||HeadNode->next == NULL){
		printf("链表为空\n"); 
		return Error;
	}
	printf("请输入想要查询的数据：");
	int data; //待查询的数据 
	scanf("%d",&data);
	if(SearchList(HeadNode, data)){
		printf("表中存在该数据\n");
	}else{
		printf("表中不存在该数据\n"); 
	}
}
//判断是否为空 
Status IsLoopList(LNode *HeadNode){
	if(HeadNode==NULL){
		printf("链表为空\n"); 
		return SUCCESS;
	}
	LNode* fast, *slow; //快慢指针
	if(HeadNode->next == NULL){
		printf("链表为单链表\n");
		return SUCCESS;
	} 
	fast = slow = HeadNode;
	while(1){
		if(fast == NULL || fast->next){ //由于链表长度可能是奇数或者偶数 
			printf("链表为单链表\n");
			return SUCCESS;
		}else if (fast ==slow || fast->next == slow){
			printf("链表为循环链表\n"); 
			return SUCCESS; 
		}else{
			slow = slow->next;
			fast = fast->next->next;
		}
	}	
}	 
//递归实现翻转 （递归） 
LNode reverse(LNode *L) {
    if (L->next == NULL) {
		return *L;
	}
    LNode last = reverse(L->next);//递归输出的结果为转换后的头结点 
    L->next->next = L;
    L->next = NULL;
    return last;  //last：逆转后的头结点 
				  //注意函数使用L = reverse(L) 更新头指针 
}
//翻转链表（包括交互） 
Status ReverseList(LinkedList *L){
	if((*L)==NULL|| (*L)->next == NULL){			//链表只有一个节点 
		printf("链表没有节点不需要翻转\n"); 
		return Error;
	}else if((*L)->next->next == NULL){
		printf("链表只有一个节点不需要翻转\n");
		return Error; 
	}
    LNode *p, *q, *r; //实现节点的逆转 
    p = NULL;
    q = (*L)->next;
    r = q->next;
    while(r!=NULL){
    	q->next = p; //实现节点调换 
    	p = q;
    	q = r;
    	r = r->next;
    } 
    q->next = p;
    (*L)->next = q;
    printf("逆转成功\n"); 
    return SUCCESS; 
}
//摧毁链表 
void DestroyList(LinkedList *L){
	LNode *p = (*L);
	while(p){
		p=p->next;
		free(*L);
		(*L)=p;
	}
}

void visit(int data){
	printf("%d->",data);
}
//奇偶（有点小问题..） 
LNode* ReverseEvenList(LinkedList *L){
	if((*L) == NULL||(*L) ->next == NULL){
		return *L;
	}
	LNode*r,*q,*p;
	r = (*L) ;
	q = r->next;
	p = q->next;
	while(p!=NULL){
		if(p->data%2!=0){
			q->next = p->next;
			p->next = q;
			r->next = p;
			r = p;
			p = q;
			q = r;
		}
		r = r->next;
		q = q->next;
		p = p->next;	
	}
	return*L;
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
	"--- 查询元素 ---",
	"--- 删除元素 ---",
	"--- 插入元素 ---",
	"--- 找到中点 ---",	
	"--- 判断成环 ---",
	"--- 翻转链表 ---",	
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
	LinkedList L = NULL;
	LNode *node;
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
				case 0: InitList(&L); system("pause"); break ; //创建新链表 
				case 1: TraverseList(L, visit);system("pause");  break ; //输出链表 
				case 2: SearchNode(L); system("pause");  break ; //查询数据 
				case 3: DeleteNode(L); system("pause");   break ; //删除数据 
				case 4: InsertNode(L); system("pause");   break ; //插入数据 
				case 5: node = FindMidNode(&L); system("pause");   break ; //找到中点 
				case 6: IsLoopList(L); system("pause");   break ; //判断是否循环 
				case 7: ReverseList(&L); system("pause");   break ; //翻转链表
				case 8: DestroyList(&L); printf("链表清除成功\n"); system("pause");  break ; //清空链表
				case 9: SetConsoleTextAttribute(hOut,  //设置颜色防止异常 
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

