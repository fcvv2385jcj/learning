#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"calculators.h"
//��ʼ������ 
Status init(LinkStack *s){
	StackNode *node = (StackNode*)malloc(sizeof(StackNode));
	node->next = NULL;
	node->data = 0;
	s->count = 0;
	s->top = node; 
	return Success;
}
//��ջ 
Status push(LinkStack *s,ElemType data){
	if(s->top == NULL){
		return Error;
	}
	StackNode *node =  (StackNode *)malloc(sizeof(StackNode));
	node->data = data;
	node->next = s->top->next;
	s->top->next = node;
	//ջ��������һ 
	s->count++;
	return Success;
}
//��ջ
Status pop(LinkStack *s){
	if(s->top == NULL||s->top->next == NULL){
		return Error;
	}
	StackNode *p;
	p = s->top->next;
	s->top->next = p->next;
	free(p);
	//ջ��������һ 
	s->count--;
	return Success;
}
//�ж��Ƿ�Ϊ�� 
Status empty(LinkStack *s){
	if(s->count == 0){
		return Success;
	}else{
		return Error;
	}
}
//���ջ��Ԫ�� 
int top(LinkStack *s){
	int top_data = s->top->next->data;
	return top_data;
}
//�жϷ������ȼ� 
Status priority(char a, char b){
	//�ӷ� 
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
	//����
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
	//�˷�
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
	//����
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
//����Ϸ��ж� 
Status detection(char *str){
	int len = strlen(str); //�ַ������� 
	for(int i=0; i<len; i++){
		if(((str[0]>'9' || str[0]<'0')&&str[0]!='(') || ((str[len-1]>'9' || str[len-1]<'0') &&str[len-1]!=')')){ //��,β�ַ���Ϊ���� 
			return Error;
		}
		if((str[i]>'9'||str[i]<'0') && (str[i-1]>'9'||str[i-1]<'0')){ //���������ж� 
			if(!(str[i]=='(' || str[i-1]==')')){  //��������ʱ �����ŵ�������� 
				return Error;
			}
		}
		if(str[i]!='+' && str[i]!='-' && str[i]!='*' && str[i]!='/' && str[i]!='('&& str[i]!=')'
								 && !(str[i]<='9' && str[i]>='0')){//�жϷǷ����������� 
			return Error;
		}
		
	}
	return Success; 
}

//������ѹ��ջres  ����ѹ��ջmid  ������ѹ��resʱֱ�ӵ���res��ͷ2��Ԫ�� ���м������ѹ��ջres 
//���� 
int computer(char *mid){
	int size = strlen(mid);//��׺���ʽ�ĳ��� 
	LinkStack st; //�������
	init(&st);  //��ʼ��
	
	LinkStack res; //���� 
	init(&res);
	
	for(int i = 0; i<size; i++){
		int k=0;
		//�ж��Ƿ�Ϊ���� 
		if(mid[i] >= '0' && mid[i] <= '9' && i<size){ 
			//�����ִ���9ʱ 
			while(mid[i] >= '0' && mid[i] <= '9' && i<size){
				k = k*10 + mid[i]-'0';
				i++;
			}
			push(&res,k);
		}
		//��������ջ 
		if(mid[i] == '('){
			push(&st, mid[i]);
		}
		//��������� 
		if(mid[i] == '+'||mid[i] == '*'||mid[i] == '-'||mid[i] == '/'){
			if(empty(&st)){
				push(&st,mid[i]);
			}else{	//�����ȼ���ջ 
				while(1){
					int temp = top(&st);
					if(priority(mid[i],temp)){ //ջ����������ȼ��� ֱ�ӽ��������ջ 
						push(&st,mid[i]);
						break; 
					}else{  //ջ����������ȼ���   
						compute(&res,temp);  //�ӷ���ջ�е��� ��������ջ�н��м��� 
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
			while(top(&st) != '('){ //Ѱ��ƥ��������� 
				compute(&res,top(&st));//�ӷ���ջ�е��� ��������ջ�н��м��� 
				pop(&st);
			}
			pop(&st); //��������Ҫ�������� 
		}
	}
	while(!empty(&st)){ //����ջ�в�Ϊ��ʱ  
		compute(&res,top(&st));//�ӷ���ջ�е��� ��������ջ�н��м��� 
		pop(&st);
	}
	return top(&res);
}             
//��ȡջ���������ֽ��м��� 
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


