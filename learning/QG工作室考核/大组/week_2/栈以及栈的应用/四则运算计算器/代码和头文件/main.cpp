#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "calculators.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("退出请输入:00\n");
	while(1){
		char mid[30]; //储存输入的表达式 
		int ans=0; //储存结果 
		printf("请输入表达式:\n"); 
		scanf("%s",mid);
		//退出程序判断 
		if(mid[0]=='0'&&mid[1]=='0'){
			return 0;
		} 
		//输入格式判断 
		while(!detection(mid)){
			printf("请输入正确的格式!\n"); 
			scanf("%s",mid);
		}
		ans = computer(mid);
		printf("%d\n",ans);
	}
	return 0;
}
