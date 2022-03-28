#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../head/LinkStack.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	LinkStack s;
	s.top = NULL;
	s.count = 0;
	ElemType top_data,pop_data,length; //储存栈顶元素 出栈的元素 栈大小 
	
	system("mode con cols=100 lines=30");
	CONSOLE_CURSOR_INFO cci; //定义光标信息（大小dwSize，可见度bVisible） 
	int ret;
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
			{	
				case 0: initLStack(&s); system("pause"); break ; //初始化链栈
				case 1: getTopLStack(&s,&top_data);system("pause");  break ; //获得栈顶元素
				case 2: isEmptyLStack(&s); system("pause");  break ; //判断链栈是否为空
				case 3: LStackLength(&s, &length); system("pause"); break ; //链栈长度
				case 4: pushLStack_IxD(&s); system("pause");   break ; //入栈
				case 5: popLStack(&s, &pop_data);system("pause");  break ;//出栈
				case 6: clearLStack(&s); system("pause");   break ; //清空链栈
				case 7: destroyLStack(&s); system("pause");   break ; //摧毁链栈
				case 8: printStack(&s); system("pause");  break ; //输出链栈
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
