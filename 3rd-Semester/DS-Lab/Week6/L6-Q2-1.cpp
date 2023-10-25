#include<iostream>      // Include the C++ input/output library.
#include<locale>
#include<string.h>      // Include the C library for string manipulation.
#include<math.h>        // Include the C math library.
#include<cstdlib>       // Include the C standard library.
using namespace std;     // Use the standard namespace.

int stack[100];           // Declare an integer array for the stack with a capacity of 100 elements.
int top = -1;              // Initialize the top of the stack to -1 (empty).
int n = 100;               // Define the maximum capacity of the stack as 100.

// Function to check if a character is a digit.
bool isdigt(char x) {
   if(x>='0' && x<='9')
      return true;
   else
      return false;
}

// Function to push an integer onto the stack.
void push(int x) {
    if(top>=n-1)
		cout<<"stack overflow";  // If the stack is full, print "stack overflow."
	else{
		stack[++top] = x;  // Increment the top index and add the integer to the stack.
	}
}

// Function to pop an integer from the stack.
int pop() {
    if(top == -1)
        return -1;   // If the stack is empty, return -1.
    else
        return stack[top--];  // Return the integer at the top of the stack and decrement the top index.
}

// Function to check if a character is an operator.
int isoperator(char a){
	if(a=='+'|| a=='-'|| a=='*'|| a=='/'||a=='^')
	    return 1;
	else
	    return 0;
}

int main(){
	char exp[100], str[100];
	double result;
	int k = 0;
	char op[50];
	cout << "enter prefix expression: ";  // Prompt the user to enter a prefix expression.
	gets(exp);                              // Read the input expression from the user.
	int i = strlen(exp);
	for(;i>=0;i--){
		if(isdigit(exp[i])){
			k = 0;
			while(isdigit(exp[i]))
				op[k++] = exp[i--]; // Collect all contiguous digits.
			i += 1;
			op[k] = '\0';
			int j = 0;
			for(int z = strlen(op) - 1; z >= 0; z--){
            	str[j++] = op[z];  // Reverse the digit sequence.
            }
            string newstr = str;  // Convert the reversed string to a C++ string.
			int num = atoi(str);  // Convert the string to an integer.
			push(num);           // Push the integer onto the stack.
		}
		else if (isoperator(exp[i])){
			int op1 = pop();
			int op2 = pop();
			switch (exp[i]){
				case '+':
					result = op1 + op2 ;
					push(result);
					break;
				case '-':
					result = op1 - op2 ;
					push(result);
					break;	
				case '*':
					result = op1 * op2 ;
					push(result);
					break;
				case '/':
					result = op1 / op2;
					push(result);
					break;
				case '^':
					result = pow(op1, op2) ;
					push(result);
					break;
			}
		}
	}
	cout << pop();  // Print the final result.
	return 0;
}
