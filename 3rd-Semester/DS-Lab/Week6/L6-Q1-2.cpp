#include<iostream>
using namespace std;

char stack[100]; // Declare a character array for the stack with a capacity of 100 elements.
int top = -1;    // Initialize the top of the stack to -1 (empty).
int n = 100;     // Define the maximum capacity of the stack as 100.

// Function to check if a character is a digit.
bool isdigt(char x) {
   if (x >= '0' && x <= '9')
      return true;
   else
      return false;
}

// Function to check if a character is a lowercase alphabet.
bool isaplha(char x) {
   if (x >= 'a' && x <= 'z')
      return true;
   else
      return false;
}

// Function to push a character onto the stack.
void push(char x) {
   if (top >= n - 1)
      cout << "stack overflow"; // If the stack is full, print "stack overflow."
   else {
      stack[++top] = x; // Increment the top index and add the character to the stack.
   }
}

// Function to pop a character from the stack.
char pop() {
   if (top == -1)
      return -1; // If the stack is empty, return -1.
   else
      return stack[top--]; // Return the character at the top of the stack and decrement the top index.
}

// Function to determine the priority of an operator.
int priority(char x) {
   if (x == '(')
      return 0;     // The priority of an open parenthesis is 0.
   if (x == '+' || x == '-')
      return 1;     // The priority of addition and subtraction is 1.
   if (x == '*' || x == '/')
      return 2;     // The priority of multiplication and division is 2.
   if (x == '^')
      return 3;     // The priority of exponentiation is 3.
   return 0;        // Default priority is 0.
}

int main() {
   char exp[100];
   char x;
   cout << "Enter the expression : \n"; // Prompt the user to enter an expression.
   gets(exp);                            // Read the input expression from the user.

   cout << "\n";

   int i = 0;
   while (exp[i] != '\0') {
      if (isalpha(exp[i]))
         cout << exp[i]; // If it's a letter, print it.
      else if (isdigit(exp[i])) {
         while (isdigit(exp[i]))
            cout << exp[i++]; // If it's a digit, print all contiguous digits.
         cout << " ";          // Add a space after the digit sequence.
         i -= 1;                // Adjust the index to account for the digits.
      } else if (exp[i] == '(') {
         push(exp[i]); // If it's an open parenthesis, push it onto the stack.
      } else if (exp[i] == ')') {
         while ((x = pop()) != '(')
            cout << x; // If it's a close parenthesis, pop and print all characters until an open parenthesis is encountered.
      } else {
         while (priority(stack[top]) >= priority(exp[i]))
            cout << pop(); // Pop and print characters with higher or equal precedence.
         push(exp[i]);     // Push the current character onto the stack.
      }
      i++;
   }

   while (top != -1) {
      cout << pop(); // Pop and print any remaining characters from the stack.
   }
   return 0;
}
