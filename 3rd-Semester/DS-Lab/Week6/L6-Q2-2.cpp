#include<iostream>
#include<cstdlib>
#include<math.h>
using namespace std;
int stack[100];
int top = -1;
int n=100;
bool isdigt(char x){
   if(x>='0' && x<='9')
   return true;
   else
   return false;
}

void push(int x)
{
    if(top>=n-1)
		cout<<"stack overflow";
	else{
		stack[++top] = x;
	}
}

int pop()
{
    if(top == -1)
        return -1;
    else
        return stack[top--];
}
int isoperator(char a){
	if(a=='+'|| a=='-'|| a=='*'|| a=='/'||a=='^')
	return 1;
	else
	return 0;
}
int main(){
	char exp[100],op[50];
	int k=0;
	double result;
	cout<<"enter postfix expression: ";
	gets(exp);
	for(int i=0;exp[i]!='\0';i++){
		if(isdigit(exp[i])){
			k=0;
			while(isdigit(exp[i]))
			op[k++]=exp[i++];
			i-=1;
			op[k]='\0';
			
			int num = atoi(op);
			push(num);
		}
		else if (isoperator(exp[i])){
			int op1 = pop();
			int op2 = pop();
		 switch (exp[i]){
		 	case '+':
		 		result =op2 + op1 ;
		 		push(result);
		 		break;
		 	case '-':
		 		result =op2 - op1 ;
		 		push(result);
		 		break;	
		 	case '*':
		 		result =op2 * op1 ;
		 		push(result);
		 		break;
		 	case '/':
		 		result =op2 / op1 ;
		 		push(result);
		 		break;
		 	case '^':
		 		result = pow(op2,op1) ;
		 		push(result);
		 		break;
		 }
		}
	}
	cout<<pop();
	return 0;
}
