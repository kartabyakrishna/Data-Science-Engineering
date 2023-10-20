#include <iostream>
using namespace std;

struct StackRepr
{
	char stack[100];
	int top;
	int size;
	bool isValid;
};

bool isFull(StackRepr *inst)
{
	if (inst->top == inst->size)
	{
		return true;
	}
	return false;
}

bool isEmpty(StackRepr *inst)
{
	if (inst->top == 0)
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

void pop(StackRepr *inst, char element)
{
	if (isEmpty(inst))
	{
		inst->isValid = false;
		return;
	}

	--inst->top;
	char top = inst->stack[inst->top];
	switch (element)
	{
	case ')':
	{
		if (top != '(')
		{
			inst->isValid = false;
		}
		break;
	}
	case '}':
	{
		if (top != '{')
		{
			inst->isValid = false;
		}
		break;
	}
	case ']':
	{
		if (top != '[')
		{
			inst->isValid = false;
		}
		break;
	}
	}
}

int main()
{
	StackRepr inst;
	inst.top = 0;
	inst.size = 100;
	inst.isValid = true;

	char str[100];

	cout << "Enter the expression" << endl;
	gets(str);

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			push(&inst, str[i]);
		}
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			pop(&inst, str[i]);
		}
	}

	if (inst.isValid == false)
	{
		cout << "Not valid";
	}
	else if (inst.isValid == true && inst.top == 0)
	{
		cout << "Valid";
	}
	else
	{
		cout << "Not valid";
	}
};
