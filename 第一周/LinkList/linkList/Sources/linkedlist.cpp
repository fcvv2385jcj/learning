#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<stdlib.h>
#include"../Headers/linkedList.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
//��ʼ������ 
Status InitList(LinkedList *L){
	if((*L)!=NULL){ //��������ж� 
		DestroyList(&(*L));
	}
	*L= (LNode*)malloc(sizeof(LNode));
    if(L == NULL){
        printf("��ʼ��ʧ��\n");
        return Error;
    }
    
    (*L)-> data = 0; //ͷ�������Ϊ������ 
    printf("��ʼ���ɹ�\n");
    (*L)->next = NULL;
    int num_node = 0;//�ڵ���
	ElemType value=0; //�ڵ����� 
    LinkedList p = *L;		   //���������½ڵ� 
	printf("������Ҫ�����Ľڵ�����"); //����Ҫ�����Ľڵ� 
	scanf("%d", &num_node);
	
	for(int i =1; i <= num_node; i++) {
		printf("�������%d���ڵ㣺", i);
		scanf("%d",&value);
		LNode *node= (LNode*)malloc(sizeof(LNode));
		if(node == NULL){
        	printf("�����ڵ�ʧ��\n");
        	return Error;
    	}
    	node->data = value;
    	node->next = NULL; 
    	p->next = node;  //�����½ڵ� 
    	p = node;
    	(*L)->data += 1; //������������ 
	}
    return SUCCESS;
}
//����ڵ� 
Status InsertList(LNode *p, LNode *q){
	if(p == NULL||q == NULL) {
		return Error;
	}
	q->next = p->next;
	p->next = q;
	return SUCCESS;
}
//����ڵ㣨�����������֣� 
void InsertNode(LNode* HeadNode){
	if(HeadNode == NULL || HeadNode->next == NULL){//��������ж� 
		printf("����Ϊ��\n"); 
		return ;
	}
	ElemType p,q;
	printf("��������Ҫ��������ݣ�"); 
	scanf("%d",&q);
	printf("������Ҫ�嵽�ĸ�����֮��"); 
	scanf("%d",&p);
	LNode *new_node = (LNode*)malloc(sizeof(LNode));//���½ڵ����ռ� 
	new_node->data = q;
	new_node->next = NULL;
	LNode *p1 = HeadNode; //���ڱ���Ѱ�ҽڵ�p 
	while(p1!=NULL){
		if(p1->data == p){
			InsertList(p1, new_node);
			printf("����ɹ�\n",p);
			HeadNode->data += 1;//��ڵ�����1 
			break;
		}
		p1 = p1->next;
	}
	if(p1==NULL){
		printf("����ʧ�ܣ�δ���ҵ�%d\n",p);
	}
}
//Ѱ���е� 
LNode* FindMidNode(LinkedList *L){
	if((*L) == NULL||(*L)->next==NULL){
		printf("����Ϊ��\n"); 
		return NULL;
	}
	
	int Lenlist = (*L)->data / 2 ;
	LNode *midnode = (*L)->next; 
	while(Lenlist--){
		midnode = midnode->next;
	}
	printf("�м�ֵ������Ϊ:%d\n",midnode->data);
	return midnode;
} 
//������� 
void TraverseList(LinkedList L, void (*visit)(ElemType e)){
	LNode *p = NULL;
 
	if(L==NULL||L->next == NULL){
		printf("����Ϊ��\n");
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
//ɾ���ڵ� 
Status DeleteList(LNode *p, ElemType *e) {
	if(p == NULL||p->next == NULL){
		printf("����Ϊ��\n"); 
		return Error;
	}
	LNode*q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	return SUCCESS;
}
//ɾ���ڵ㣨���������� 
void DeleteNode(LNode* HeadNode){
	if(HeadNode == NULL||HeadNode->next == NULL){
		printf("����Ϊ��\n"); 
		return ;
	}

	int delete_data;
	printf("%������Ҫɾ�������ݣ�"); 
	scanf("%d", &delete_data);
	if(HeadNode==NULL){
		printf("����Ϊ��\n");
		return ;
	}

	LNode *p1;		//p1,p2����Ѱ�Ҳ�����ɾ���Ľڵ� 
	LNode *p2;
	p1 = HeadNode;
	p2 = HeadNode->next;
	while(p2!=NULL){
		if(p2->data == delete_data){
			p1->next = p2->next;
			free(p2);
			HeadNode->data--; //����������С 
			printf("ɾ���ɹ�\n"); 
			return;
		}
		p1=p2;
		p2=p1->next;
	}
	if(p2 == NULL){
		printf("������Ҫɾ��������\n");
	} 
}
//�������� 
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
//�������ݣ����������� 
Status SearchNode(LNode* HeadNode){
	if(HeadNode == NULL||HeadNode->next == NULL){
		printf("����Ϊ��\n"); 
		return Error;
	}
	printf("��������Ҫ��ѯ�����ݣ�");
	int data; //����ѯ������ 
	scanf("%d",&data);
	if(SearchList(HeadNode, data)){
		printf("���д��ڸ�����\n");
	}else{
		printf("���в����ڸ�����\n"); 
	}
}
//�ж��Ƿ�Ϊ�� 
Status IsLoopList(LNode *HeadNode){
	if(HeadNode==NULL){
		printf("����Ϊ��\n"); 
		return SUCCESS;
	}
	LNode* fast, *slow; //����ָ��
	if(HeadNode->next == NULL){
		printf("����Ϊ������\n");
		return SUCCESS;
	} 
	fast = slow = HeadNode;
	while(1){
		if(fast == NULL || fast->next){ //���������ȿ�������������ż�� 
			printf("����Ϊ������\n");
			return SUCCESS;
		}else if (fast ==slow || fast->next == slow){
			printf("����Ϊѭ������\n"); 
			return SUCCESS; 
		}else{
			slow = slow->next;
			fast = fast->next->next;
		}
	}	
}	 
//�ݹ�ʵ�ַ�ת ���ݹ飩 
LNode reverse(LNode *L) {
    if (L->next == NULL) {
		return *L;
	}
    LNode last = reverse(L->next);//�ݹ�����Ľ��Ϊת�����ͷ��� 
    L->next->next = L;
    L->next = NULL;
    return last;  //last����ת���ͷ��� 
				  //ע�⺯��ʹ��L = reverse(L) ����ͷָ�� 
}
//��ת�������������� 
Status ReverseList(LinkedList *L){
	if((*L)==NULL|| (*L)->next == NULL){			//����ֻ��һ���ڵ� 
		printf("����û�нڵ㲻��Ҫ��ת\n"); 
		return Error;
	}else if((*L)->next->next == NULL){
		printf("����ֻ��һ���ڵ㲻��Ҫ��ת\n");
		return Error; 
	}
    LNode *p, *q, *r; //ʵ�ֽڵ����ת 
    p = NULL;
    q = (*L)->next;
    r = q->next;
    while(r!=NULL){
    	q->next = p; //ʵ�ֽڵ���� 
    	p = q;
    	q = r;
    	r = r->next;
    } 
    q->next = p;
    (*L)->next = q;
    printf("��ת�ɹ�\n"); 
    return SUCCESS; 
}
//�ݻ����� 
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
//��ż���е�С����..�� 
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
	"---����������---",
	"--- ������� ---",
	"--- ��ѯԪ�� ---",
	"--- ɾ��Ԫ�� ---",
	"--- ����Ԫ�� ---",
	"--- �ҵ��е� ---",	
	"--- �жϳɻ� ---",
	"--- ��ת���� ---",	
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
	LinkedList L = NULL;
	LNode *node;
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
				case 0: InitList(&L); system("pause"); break ; //���������� 
				case 1: TraverseList(L, visit);system("pause");  break ; //������� 
				case 2: SearchNode(L); system("pause");  break ; //��ѯ���� 
				case 3: DeleteNode(L); system("pause");   break ; //ɾ������ 
				case 4: InsertNode(L); system("pause");   break ; //�������� 
				case 5: node = FindMidNode(&L); system("pause");   break ; //�ҵ��е� 
				case 6: IsLoopList(L); system("pause");   break ; //�ж��Ƿ�ѭ�� 
				case 7: ReverseList(&L); system("pause");   break ; //��ת����
				case 8: DestroyList(&L); printf("��������ɹ�\n"); system("pause");  break ; //�������
				case 9: SetConsoleTextAttribute(hOut,  //������ɫ��ֹ�쳣 
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

