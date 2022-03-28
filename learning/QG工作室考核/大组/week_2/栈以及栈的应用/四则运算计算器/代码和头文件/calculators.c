#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"calculators.h"
//初始化参数 
Status init(LinkStack *s){
	StackNode *node = (StackNode*)malloc(sizeof(StackNode));
	node->next = NULL;
	node->data = 0;
	s->count = 0;
	s->top = node; 
	return Success;
}
//入栈 
Status push(LinkStack *s,ElemType data){
	if(s->top == NULL){
		return Error;
	}
	StackNode *node =  (StackNode *)malloc(sizeof(StackNode));
	node->data = data;
	node->next = s->top->next;
	s->top->next = node;
	//栈计数器加一 
	s->count++;
	return Success;
}
//出栈
Status pop(LinkStack *s){
	if(s->top == NULL||s->top->next == NULL){
		return Error;
	}
	StackNode *p;
	p = s->top->next;
	s->top->next = p->next;
	free(p);
	//栈计数器减一 
	s->count--;
	return Success;
}
//判断是否为空 
Status empty(LinkStack *s){
	if(s->count == 0){
		return Success;
	}else{
		return Error;
	}
}
//输出栈顶元素 
int top(LinkStack *s){
	int top_data = s->top->next->data;
	return top_data;
}
//判断符号优先级 
Status priority(char a, char b){
	//加法 
	if (a == '+'&& b == '+'){
		return Error;
	}
	if (a == '+'&& b == '*'){
		return Error;
	}
	if (a == '+'&& b == '/'){
		return Error;
	}
	if (a == '+'&& b == '('){
		return Success;
	}
	if (a == '+'&& b == '-'){
		return Error;
	}
	//减法
	if (a == '-'&& b == '+'){
		return Error;
	}	 
	if (a == '-'&& b == '*'){
		return Error;
	}
	if (a == '-'&& b == '/'){
		return Error;
	}	
	if (a == '-'&& b == '('){
		return Success;
	}	
	if (a == '-'&& b == '-'){
		return Error;
	}		
	//乘法
	if (a == '*'&& b == '+'){
		return Success;
	} 
	if (a == '*'&& b == '-'){
		return Success;
	} 
	if (a == '*'&& b == '*'){
		return Error;
	} 
	if (a == '*'&& b == '/'){
		return Error;
	} 
	if (a == '*'&& b == '('){
		return Success;
	}
	//除法
	if (a == '/'&& b == '+'){
		return Success;
	} 
	if (a == '/'&& b == '-'){
		return Success;
	} 
	if (a == '/'&& b == '/'){
		return Error;
	} 
	if (a == '/'&& b == '*'){
		return Error;
	} 
	if (a == '/'&& b == '('){
		return Success;
	} 
	return Error;
}
//输入合法判断 
Status detection(char *str){
	int len = strlen(str); //字符串长度 
	for(int i=0; i<len; i++){
		if(((str[0]>'9' || str[0]<'0')&&str[0]!='(') || ((str[len-1]>'9' || str[len-1]<'0') &&str[len-1]!=')')){ //首,尾字符不为数字 
			return Error;
		}
		if((str[i]>'9'||str[i]<'0') && (str[i-1]>'9'||str[i-1]<'0')){ //符号相连判断 
			if(!(str[i]=='(' || str[i-1]==')')){  //符号相连时 有括号的特殊情况 
				return Error;
			}
		}
		if(str[i]!='+' && str[i]!='-' && str[i]!='*' && str[i]!='/' && str[i]!='('&& str[i]!=')'
								 && !(str[i]<='9' && str[i]>='0')){//判断非法的其他符号 
			return Error;
		}
		
	}
	return Success; 
}

//将数字压入栈res  符号压入栈mid  当符号压入res时直接弹出res的头2个元素 进行计算后再压入栈res 
//计算 
int computer(char *mid){
	int size = strlen(mid);//中缀表达式的长度 
	LinkStack st; //存运算符
	init(&st);  //初始化
	
	LinkStack res; //存结果 
	init(&res);
	
	for(int i = 0; i<size; i++){
		int k=0;
		//判断是否为数字 
		if(mid[i] >= '0' && mid[i] <= '9' && i<size){ 
			//当数字大于9时 
			while(mid[i] >= '0' && mid[i] <= '9' && i<size){
				k = k*10 + mid[i]-'0';
				i++;
			}
			push(&res,k);
		}
		//左括号入栈 
		if(mid[i] == '('){
			push(&st, mid[i]);
		}
		//运算符处理 
		if(mid[i] == '+'||mid[i] == '*'||mid[i] == '-'||mid[i] == '/'){
			if(empty(&st)){
				push(&st,mid[i]);
			}else{	//按优先级出栈 
				while(1){
					int temp = top(&st);
					if(priority(mid[i],temp)){ //栈中运算符优先级低 直接将运算符入栈 
						push(&st,mid[i]);
						break; 
					}else{  //栈中运算符优先级高   
						compute(&res,temp);  //从符号栈中弹出 并在数字栈中进行计算 
						pop(&st);
						if(empty(&st)){
							push(&st, mid[i]);
							break;
						}
					}
				}
			}
		}
		if(mid[i] == ')'){
			while(top(&st) != '('){ //寻找匹配的左括号 
				compute(&res,top(&st));//从符号栈中弹出 并在数字栈中进行计算 
				pop(&st);
			}
			pop(&st); //弹出不需要的左括号 
		}
	}
	while(!empty(&st)){ //符号栈中不为空时  
		compute(&res,top(&st));//从符号栈中弹出 并在数字栈中进行计算 
		pop(&st);
	}
	return top(&res);
}             
//提取栈的两个数字进行计算 
int compute(LinkStack *res, char type){
		if(type == '+'){
			int a = top(res);
			pop(res);
			int b = top(res);
			pop(res);
			push(res,a+b);
		}
		if(type == '-'){
			int a = top(res);
			pop(res);
			int b = top(res);
			pop(res);
			push(res,b-a);
		}
		if(type == '*'){
			int a = top(res);
			pop(res);
			int b = top(res);
			pop(res);
			push(res,a*b);
		}
		if(type == '/'){
			int a = top(res);
			pop(res);
			int b = top(res);
			pop(res);
			push(res,b/a);
		}
	return top(res);
}


