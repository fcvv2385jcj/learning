#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "calculators.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("�˳�������:00\n");
	while(1){
		char mid[30]; //��������ı��ʽ 
		int ans=0; //������ 
		printf("��������ʽ:\n"); 
		scanf("%s",mid);
		//�˳������ж� 
		if(mid[0]=='0'&&mid[1]=='0'){
			return 0;
		} 
		//�����ʽ�ж� 
		while(!detection(mid)){
			printf("��������ȷ�ĸ�ʽ!\n"); 
			scanf("%s",mid);
		}
		ans = computer(mid);
		printf("%d\n",ans);
	}
	return 0;
}
