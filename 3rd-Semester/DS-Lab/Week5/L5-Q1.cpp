#include <iostream>
using namespace std;

struct StackRepr
{
	int stack[10];
	int top;
	int size;
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

void push(StackRepr *inst, int element)
{
	if (isFull(inst))
	{
		cout << "Overflow, Stack is full!" << endl;
		return;
	}
	inst->stack[inst->top] = element;
	inst->top++;
}

void display(StackRepr *inst)
{
	if (isEmpty(inst))
	{
		cout << "Stack is empty!" << endl;
		return;
	}
	for (int i = inst->top - 1; i >= 0; i--)
	{
		cout << inst->stack[i] << " ";
	}
	cout << endl;
}

void pop(StackRepr *inst)
{
	if (isEmpty(inst))
	{
		cout << "Underflow, can't pop item" << endl;
		return;
	}
	cout << inst->stack[--inst->top] << " popped from the stack" << endl;
}

void peek(StackRepr *inst)
{
	if (isEmpty(inst))
	{
		cout << "Underflow, Stack is empty" << endl;
		return;
	}
	cout << inst->stack[inst->top - 1] << endl;
}

int main()
{
	int choice = 0;

	StackRepr inst;
	inst.top = 0;
	inst.size = 10;

	cout << "1) Push element to stack" << endl;
	cout << "2) Pop element from stack" << endl;
	cout << "3) Peek element in stack" << endl;
	cout << "4) Display stack elements" << endl;
	cout << "5) Exit" << endl;

	while (choice != 5)
	{
		cout << "Enter your choice" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int element;
			cout << "Enter element to push to stack" << endl;
			cin >> element;

			push(&inst, element);
			break;
		}
		case 2:
		{
			pop(&inst);
			break;
		}
		case 3:
		{
			peek(&inst);
			break;
		}
		case 4:
		{
			display(&inst);
			break;
		}
		default:
			exit(0);
		}
	}
};
