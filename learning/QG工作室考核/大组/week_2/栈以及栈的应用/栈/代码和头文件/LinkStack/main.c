#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../head/LinkStack.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	LinkStack s;
	s.top = NULL;
	s.count = 0;
	ElemType top_data,pop_data,length; //����ջ��Ԫ�� ��ջ��Ԫ�� ջ��С 
	
	system("mode con cols=100 lines=30");
	CONSOLE_CURSOR_INFO cci; //��������Ϣ����СdwSize���ɼ���bVisible�� 
	int ret;
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
			{	
				case 0: initLStack(&s); system("pause"); break ; //��ʼ����ջ
				case 1: getTopLStack(&s,&top_data);system("pause");  break ; //���ջ��Ԫ��
				case 2: isEmptyLStack(&s); system("pause");  break ; //�ж���ջ�Ƿ�Ϊ��
				case 3: LStackLength(&s, &length); system("pause"); break ; //��ջ����
				case 4: pushLStack_IxD(&s); system("pause");   break ; //��ջ
				case 5: popLStack(&s, &pop_data);system("pause");  break ;//��ջ
				case 6: clearLStack(&s); system("pause");   break ; //�����ջ
				case 7: destroyLStack(&s); system("pause");   break ; //�ݻ���ջ
				case 8: printStack(&s); system("pause");  break ; //�����ջ
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
