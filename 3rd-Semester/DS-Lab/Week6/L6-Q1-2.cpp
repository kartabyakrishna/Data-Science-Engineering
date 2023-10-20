#include<iostream>
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
    if(x == '(')
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
    char x;
    cout<<"Enter the expression : \n";
    gets(exp);
    cout<<"\n";
    
    int i=0;
    while(exp[i] != '\0')
    {
        if(isalpha(exp[i]))
            cout<<exp[i];
        else if (isdigit(exp[i]))
        {
        	while(isdigit(exp[i]))
        	cout<<exp[i++];
        	cout<<" ";
        	i-=1;
        	
		}
        else if(exp[i] == '(')
            push(exp[i]);
        else if(exp[i] == ')')
        {
            while((x = pop()) != '(')
                cout<<x;
        }
        else
        {
            while(priority(stack[top]) >= priority(exp[i]))
                cout<<pop();
            push(exp[i]);
        }
        i++;
    }
    
    while(top != -1)
    {
        cout<<pop();
    }
	return 0;
}
