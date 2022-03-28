#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"../head/LQueue.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
	//	COORD pos = {0,0};	//定义默认的坐标位置  	
int main(int argc, char** argv) {
	//设置初始化参数 
	LQueue q;
	q.front = NULL;
	q.rear = NULL; 
	q.length=0;
	void *head_data;

	system("cls");//清屏 
	CONSOLE_CURSOR_INFO cci; //定义光标信息（大小dwSize，可见度bVisible） 
	int ret; //储存键盘输入 
    int index = 0;
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
    int Menu_size = 10;
    while(1)
    {	
    	
    	//键盘输入 
    	showmenu(hOut , menu ,Menu_size , index);
		ret = get_userinput(&index , Menu_size);
		if(ret == ESC)
			break ;
		if(ret == ENTER)
		{	
			cci.bVisible =  1;
			SetConsoleCursorInfo(hOut, &cci); 
			switch(index)
			{	case 0: InitLQueue(&q); system("pause"); break ; //初始化队列
				case 1: DestoryLQueue(&q);system("pause");  break ; //摧毁链表
				case 2: IsEmptyLQueue(&q); system("pause");  break ; //判断队列是否为空
				case 3: GetHeadLQueue(&q, head_data); system("pause");   break ; //查看队头元素
				case 4: LengthLQueue(&q); system("pause");   break ; //队列长度
				case 5: EnLQueue_IxD(&q);system("pause");  break ;//数据入队 
				case 6: DeLQueue(&q); system("pause");   break ; //数据出队
				case 7: ClearLQueue(&q); system("pause");   break ; //清空队列
				case 8: TraverseLQueue(&q,LPrint); system("pause");  break ; //输出队列
				case 9: SetConsoleTextAttribute(hOut,  //设置颜色防止异常 
                            FOREGROUND_RED | 
                            FOREGROUND_GREEN | 
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY);  system("cls");      return 0 ;//退出
			}
			cci.bVisible =  0;
			SetConsoleCursorInfo(hOut, &cci); 
			system("cls");
		}
	}
	system("cls");//清屏 
    return 0;
}

