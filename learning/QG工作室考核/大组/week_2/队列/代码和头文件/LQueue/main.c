#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"../head/LQueue.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
	//	COORD pos = {0,0};	//����Ĭ�ϵ�����λ��  	
int main(int argc, char** argv) {
	//���ó�ʼ������ 
	LQueue q;
	q.front = NULL;
	q.rear = NULL; 
	q.length=0;
	void *head_data;

	system("cls");//���� 
	CONSOLE_CURSOR_INFO cci; //��������Ϣ����СdwSize���ɼ���bVisible�� 
	int ret; //����������� 
    int index = 0;
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
    int Menu_size = 10;
    while(1)
    {	
    	
    	//�������� 
    	showmenu(hOut , menu ,Menu_size , index);
		ret = get_userinput(&index , Menu_size);
		if(ret == ESC)
			break ;
		if(ret == ENTER)
		{	
			cci.bVisible =  1;
			SetConsoleCursorInfo(hOut, &cci); 
			switch(index)
			{	case 0: InitLQueue(&q); system("pause"); break ; //��ʼ������
				case 1: DestoryLQueue(&q);system("pause");  break ; //�ݻ�����
				case 2: IsEmptyLQueue(&q); system("pause");  break ; //�ж϶����Ƿ�Ϊ��
				case 3: GetHeadLQueue(&q, head_data); system("pause");   break ; //�鿴��ͷԪ��
				case 4: LengthLQueue(&q); system("pause");   break ; //���г���
				case 5: EnLQueue_IxD(&q);system("pause");  break ;//������� 
				case 6: DeLQueue(&q); system("pause");   break ; //���ݳ���
				case 7: ClearLQueue(&q); system("pause");   break ; //��ն���
				case 8: TraverseLQueue(&q,LPrint); system("pause");  break ; //�������
				case 9: SetConsoleTextAttribute(hOut,  //������ɫ��ֹ�쳣 
                            FOREGROUND_RED | 
                            FOREGROUND_GREEN | 
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY);  system("cls");      return 0 ;//�˳�
			}
			cci.bVisible =  0;
			SetConsoleCursorInfo(hOut, &cci); 
			system("cls");
		}
	}
	system("cls");//���� 
    return 0;
}

