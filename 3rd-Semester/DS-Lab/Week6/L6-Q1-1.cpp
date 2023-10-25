#include<iostream>
#include<string.h>
using namespace std;
char stack[100];
int top = -1;
int n=100;
bool isdigt(char x){
   if(x>='0' && x<='9')
   return true;
   else
   return false;
}
bool isaplha(char x){
	if(x>='a'&&x<='z')
	return true;
	else
	return false;
}
void push(char x)
{
    if(top>=n-1)
		cout<<"stack overflow";
	else{
		stack[++top] = x;
	}
}

char pop()
{
    if(top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if(x == ')')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    if(x=='^')
        return 3;
    return 0;
}

int main()
{
    char exp[100];
    char revexp[100];
    char result[100];
    char x; 
    cout<<"Enter the expression : \n";
    gets(exp);
    cout<<"\n";
    
    int k =0;
    for(int i= strlen(exp)-1;i>=0;i--){
    	
    	revexp[k++] = exp[i];
	}
	revexp[k]='\0';
	int i;
	k=0;
    for(i=0;revexp[i]!='\0';i++){
    	
    	if (isalpha(revexp[i]))
    	result[k++]= revexp[i];
    	else if(isdigit(revexp[i])){
    		 result[k++]=' ';
    	while(isdigit(revexp[i]))
		result[k++] =revexp[i++];	
		result[k++]=' ';
		i-=1;
			
		}
		else if(revexp[i]==')'){
			push(revexp[i]);
		}
		else if(revexp[i]=='('){
			while((x=pop())!= ')'){
				result[k++]=x;
			}
		}
		else{
			while(priority(stack[top]) >= priority(revexp[i]))
				result[k++]=pop();
				push(revexp[i]);
		
		}
	}
	while(top!=-1){
		result[k++]=pop();
	}
	result[k]='\0';
	for(int j = strlen(result)-1;j>=0;j--){
		cout<<result[j];
	}
	return 0;
}
}