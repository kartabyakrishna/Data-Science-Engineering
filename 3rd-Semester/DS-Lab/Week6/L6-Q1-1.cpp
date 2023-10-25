#include<iostream>           // Include the C++ input/output library.
#include<string.h>           // Include the C library for string manipulation.
using namespace std;         // Use the standard namespace.

char stack[100];              // Declare a character array for the stack with a capacity of 100 elements.
int top = -1;                 // Initialize the top of the stack to -1 (empty).
int n = 100;                  // Define the maximum capacity of the stack as 100.

// Function to check if a character is a digit.
bool isdigit(char x) {
    if (x >= '0' && x <= '9')  // Check if the character is between '0' and '9'.
        return true;
    else
        return false;
}

// Function to check if a character is a lowercase alphabet.
bool isalpha(char x) {
    if (x >= 'a' && x <= 'z')  // Check if the character is between 'a' and 'z'.
        return true;
    else
        return false;
}

// Function to push a character onto the stack.
void push(char x) {
    if (top >= n - 1)         // Check if the stack is full (overflow).
        cout << "stack overflow";
    else {
        stack[++top] = x;     // Increment the top index and add the character to the stack.
    }
}

// Function to pop a character from the stack.
char pop() {
    if (top == -1)            // Check if the stack is empty.
        return -1;
    else
        return stack[top--];  // Return the character at the top of the stack and decrement the top index.
}

// Function to determine the priority of an operator.
int priority(char x) {
    if (x == ')')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    return 0;
}

int main() {
    char exp[100];            // Declare an array to store the input expression.
    char revexp[100];         // Declare an array to store the reverse of the input expression.
    char result[100];         // Declare an array to store the final result.
    char x;
    cout << "Enter the expression : \n";  // Prompt the user to enter an expression.
    gets(exp);                            // Read the input expression from the user.

    cout << "\n";

    int k = 0;
    for (int i = strlen(exp) - 1; i >= 0; i--) {
        revexp[k++] = exp[i];   // Reverse the input expression character by character.
    }
    revexp[k] = '\0';

    int i;
    k = 0;
    for (i = 0; revexp[i] != '\0'; i++) {
        if (isalpha(revexp[i]))
            result[k++] = revexp[i];  // If it's a letter, add it to the result.
        else if (isdigit(revexp[i])) {
            result[k++] = ' ';       // Add a space.
            while (isdigit(revexp[i]))
                result[k++] = revexp[i++];  // Add digits to the result.
            result[k++] = ' ';             // Add a space.
            i -= 1;
        } else if (revexp[i] == ')') {
            push(revexp[i]);  // Push ')' onto the stack.
        } else if (revexp[i] == '(') {
            while ((x = pop()) != ')') {
                result[k++] = x;  // Pop and add characters from the stack until ')' is encountered.
            }
        } else {
            while (priority(stack[top]) >= priority(revexp[i]))
                result[k++] = pop();  // Pop and add characters with higher or equal precedence.
            push(revexp[i]);          // Push the current character onto the stack.
        }
    }
    while (top != -1) {
        result[k++] = pop();  // Pop and add any remaining characters from the stack.
    }
    result[k] = '\0';

    for (int j = strlen(result) - 1; j >= 0; j--) {
        cout << result[j];  // Print the final result in reverse order.
    }
    return 0;
}
