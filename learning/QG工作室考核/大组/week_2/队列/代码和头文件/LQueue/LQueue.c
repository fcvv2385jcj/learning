#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<stdlib.h>
#include"../head/LQueue.h" 
char type;
char data_type[30];
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q){
	Q->front = Q->rear = (Node*)malloc(sizeof(Node));
	if(Q->front == NULL){
		printf("��ʼ��ʧ��\n");
		return ;
	}
	Q->front->next = NULL;
	Q->length = 0;
	printf("��ʼ���ɹ�\n"); 
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q){
	if(Q->front == NULL){
		printf("����δ��ʼ��\n"); 
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
	printf("���дݻٳɹ�\n"); 
} 

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	if(Q->length==0){
		printf("����Ϊ��\n"); 
		return True;
	}else{
		printf("���в�Ϊ��\n");
		return False;
	}
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	if(Q->front==NULL){
		printf("���ȳ�ʼ��\n"); 
		return False;
	}
	if(Q->front->next==NULL){
		printf("��ͷԪ�ز�����\n");
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
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q){
	printf("���г���Ϊ:%d\n",Q->length);
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
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
//�������� 
void EnLQueue_IxD(LQueue *Q){
	if(Q->front==NULL){
		printf("���ȳ�ʼ��\n");
		return ; 
	}
	//������ǵڼ����� 
	int l = Q->length+1;
	choose_type(l); //�����len���ڵ������ 
	printf("����������:\n");
	//����ѡ������Ͳ������� 
	if(data_type[l] == 'a'||data_type[l] == 'A'){
		int *data = (int*)malloc(sizeof(int));
		while(scanf("%d",data)!=1){
			printf("����������\n");
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
	printf("����ɹ�\n"); 
}
/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	if(Q->front == Q->rear){
		printf("������û��Ԫ��\n"); 
		return False; 
	}
	Node *p = Q->front->next;
	Q->front->next = p->next;
	if(Q->rear == p){
		Q->rear = Q->front;
	}	
	Q->length--; //���г��ȼ�һ 
	free(p);
	printf("���ӳɹ�\n");
	//��������Ԫ�ض�Ӧ������ 
	for(int j=1; j<=Q->length; j++){
		data_type[j] = data_type[j+1];
	}
	return True;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
	if(Q->front==NULL){
		printf("���ȳ�ʼ������\n"); 
		return;
	} 
	if(Q->front == Q->rear){
		printf("���������\n");
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
	printf("������ճɹ�\n"); 
}

 /**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q
 
 *  @notice      : None
 */
 
void LPrint(void *q){
	//���ݴ�������ʹ�ӡ 
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
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*LPrint)(void *q)){
	if(Q->front==NULL||Q->front->next == NULL){
		printf("����Ϊ�ջ���δ��ʼ��\n"); 
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
//ѡ�񴢴���������� 
void choose_type(int len){
	printf("��ѡ����Ҫ�洢����������:  \nA:����  \nB:�ַ����ַ�����  \nC:������\n");
	char a[50];
	//�����쳣�ж� 
	while(1){
		printf("������A��B��C\n"); 
		scanf("%s",a);
		if((a[0]=='A'||a[0]=='B'||a[0]=='a'||a[0]=='b'||a[0]=='c'||a[0]=='C')&&strlen(a)<=1){
			break;
		}
	}
	data_type[len] = a[0];//�����len���ڵ������ 
}
//�˵� 
char *menu[] = 
{
	"---��ʼ������---",
	"--- �ݻ����� ---",
	"�ж϶����Ƿ�Ϊ��",
	"- �鿴��ͷԪ�� -",
	"--- ���г��� ---",
	"--- ������� ---",	
	"--- ���ݳ��� ---",
	"--- ��ն��� ---",	
	"--- ������� ---",
	"---   �˳�   ---",
};


//��ʾ�˵� 
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

