#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<stdlib.h>
#include"../Headers/dulinkedList.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0)) //�˵����� 

//��ʼ�� 
Status InitList_DuL(DuLinkedList *L) {
	*L = (DuLinkedList)malloc(sizeof(DuLinkedList));
	if((*L)==NULL){
		return Error;
	}
	printf("��ʼ���ɹ�\n");
	(*L)->prior = (*L)->next = NULL;
	return SUCCESS;	
}

//�������� 
void CreateLinkList(DuLinkedList L){
    ElemType n;
    DuLinkedList p = L;
    printf("������Ҫ�����Ľڵ�����");
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        DuLNode* q = (DuLNode*)malloc(sizeof(DuLNode));
        p->next = q;
        printf("�������%d��Ԫ�ص�ֵ��",i);
        scanf("%d",&(q->data));
        q->prior = p;
        q->next = NULL;
        p = q;
    }
}
//�ݻ����� 
void DestroyList_DuL(DuLinkedList *L) {
	DuLNode *p=(*L);
	while(p){
		p=p->next;
		free(*L);
		(*L)=p;
	}
}
//�����ڵ� 
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
//��ǰ���� 
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
 
//�Ӻ���� 
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
//�Ӻ���� ������������ 
void InsertDuNode_back(DuLNode *L){
	ElemType data; //����Ľڵ�ǰһ��ֵ 
	DuLNode *p; //��ֵ���ڽڵ� 
	
	ElemType i_data;
	DuLNode *q = (DuLNode*)malloc(sizeof(DuLNode));//������ڵ� 
	
	printf("������Ҫ�����ֵ��");
	scanf("%d",&i_data);
	printf("������Ҫ�嵽�ĸ�ֵ���棺");
	scanf("%d",&data);
	q->data = i_data;
	p = SearchDuList(L,data);
	if(p!=NULL){
		if(InsertAfterList_DuL(p,q)){
			printf("����ɹ�\n"); 
		}else{
			printf("����ʧ��\n"); 
		}
	} 
	
}
//��ǰ���루���������� 
void InsertDuNode_front(DuLNode *L){
	ElemType data; //����ڵ��ǰһ���ڵ��ֵ 
	DuLNode *p; //��ֵ���ڽڵ� 
	
	ElemType i_data;//������ڵ��ֵ 
	DuLNode *q = (DuLNode*)malloc(sizeof(DuLNode));//������ڵ� 
	
	printf("������Ҫ�����ֵ��");
	scanf("%d",&i_data);
	printf("������Ҫ�嵽�ĸ�ֵǰ�棺");
	scanf("%d",&data);
	q->data = i_data;
	p = SearchDuList(L,data);//����p�ڵ� 
	if(p!=NULL){
		if(InsertBeforeList_DuL(p,q)){
			printf("����ɹ�\n"); 
		}else{
			printf("����ʧ��\n"); 
		}
	} 
	
}
//ɾ���ڵ� ������������ 
Status DeleteDul_node(DuLinkedList L){
	printf("������Ҫɾ���Ľڵ㣺");
	ElemType e;//Ҫɾ�������� 
	scanf("%d",&e); 
	DuLNode* p; //�ҵ������ݵĽڵ� 
	p = SearchDuList(L, e);
	if(DeleteList_DuL(p->prior,&e)){
		printf("ɾ���ɹ�\n");
	}else{
		printf("ɾ��ʧ��"); 
	} 
}
//ɾ���ڵ� 
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
 
//������� 
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
	"---����������---",
	"--- ������� ---",
	"--- ɾ��Ԫ�� ---",
	"--��ǰ����Ԫ��--",
	"--�Ӻ����Ԫ��--",
	"--- ������� ---",
	"---   �˳�   ---",
};

CONSOLE_CURSOR_INFO cci; //��������Ϣ����СdwSize���ɼ���bVisible�� 
//����Ĭ�ϵ�����λ��  	
COORD pos = {0,0};
//��ʾ�˵� 
void showmenu(HANDLE hOut ,char **menu , int size , int index) ;
//��ȡ�û����� 
int  get_userinput(int *index , int size) ;

void showmenu(HANDLE hOut ,char **menu , int size , int index)
{
	int i ;
	//system("cls");//���� 
	for(i = 0 ; i < size ; i++)
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
    		//���ù������
    		SetConsoleCursorPosition(hOut,pos);    
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

int main(){
	DuLinkedList L = NULL;
	DuLNode *node;
	int ret ;
    int index = 0 ;
    HANDLE hOut;
    //��ȡ��ǰ�ľ��---����Ϊ��׼������ 
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //��ȡ�����Ϣ
    GetConsoleCursorInfo(hOut, &cci); 
	//���ù���С   
    cci.dwSize = 1; 
	//���ù�겻�ɼ� FALSE   
    cci.bVisible =  0; 
    //����(Ӧ��)�����Ϣ
    SetConsoleCursorInfo(hOut, &cci);   
    while(1)
    {
    	//�������� 
    	showmenu(hOut , menu , NR(menu) , index);
		ret = get_userinput(&index , NR(menu));
		if(ret == ESC)
			break ;
		if(ret == ENTER)
		{	
			switch(index)
			{
				case 0: InitList_DuL(&L); CreateLinkList(L);system("pause"); break ; //���������� 
				case 1: TraverseList_DuL(L, visit);printf("NULL\n");system("pause");  break ; //������� 
				case 2: DeleteDul_node(L); system("pause");  break ; //ɾ������ 
				case 3: InsertDuNode_front(L); system("pause");   break ; //��ǰ�������� 
				case 4: InsertDuNode_back(L); system("pause");   break ; //�Ӻ�������� 
				case 5: DestroyList_DuL(&L); system("pause");   break ; //��ת����				
				case 6: SetConsoleTextAttribute(hOut,  //������ɫ��ֹ�쳣 
                            FOREGROUND_RED | 
                            FOREGROUND_GREEN | 
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY);  system("cls");      return 0 ;//�˳�
			}
			system("cls");
		}
	}
	system("cls");//���� 
	return 0;
}
