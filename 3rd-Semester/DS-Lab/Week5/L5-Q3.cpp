#include <iostream>
using namespace std;

struct StackRepr
{
	char stack[100];
	int top;
	int size;
	bool isPalindrome;
};

bool isFull(StackRepr *inst)
{
	if (inst->top == inst->size)
	{
		return true;
	}
	return false;
}

void push(StackRepr *inst, char element)
{
	if (isFull(inst))
	{
		cout << "Stack is full!" << endl;
		return;
	}
	inst->stack[inst->top] = element;
	inst->top++;
}

int pop(StackRepr *inst)
{
	return inst->stack[--inst->top];
}

int main()
{
	StackRepr inst;
	inst.top = 0;
	inst.size = 100;
	inst.isPalindrome = true;

	char str[100];

	cout << "Enter the string" << endl;
	gets(str);

	for (int i = 0; str[i] != '\0'; i++)
	{
		push(&inst, str[i]);
	}

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (pop(&inst) != str[i])
		{
			inst.isPalindrome = false;
		}
	}

	if (inst.isPalindrome == false)
	{
		cout << "Not a palindrome";
	}
	else
	{

		cout << "Is a palindrome";
	}
};
