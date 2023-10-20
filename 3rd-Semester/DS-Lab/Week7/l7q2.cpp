#include <iostream>
using namespace std;

struct CircularQueueRepr
{
	char *queue[5];
	int max_size;
	int front;
	int rear;
	int count;
};

int size(CircularQueueRepr *inst)
{
	return inst->rear - inst->front;
}

bool isEmpty(CircularQueueRepr *inst)
{
	return inst->count == 0;
}

bool isFull(CircularQueueRepr *inst)
{
	return inst->count == inst->max_size;
}

void enqueue(CircularQueueRepr *inst, char *element)
{
	if (isFull(inst))
	{
		cout << "Overflow!\n";
		return;
	}

	inst->queue[inst->rear] = element;
	inst->rear = (inst->rear + 1) % inst->max_size;
	inst->count++;
}

void dequeue(CircularQueueRepr *inst)
{
	if (isEmpty(inst))
	{
		cout << "Underflow!\n";
		return;
	}

	inst->front = (inst->front + 1) % inst->max_size;
	inst->count--;
}

void front(CircularQueueRepr *inst)
{
	cout << inst->queue[inst->front] << endl;
}

void display(CircularQueueRepr *inst)
{
	cout << "The queue is\n";
	if (inst->rear > inst->front)
	{
		for (int i = inst->front; i < inst->rear; i++)
		{
			cout << inst->queue[i] << " ";
		}
	}
	else
	{
		for (int i = inst->front; i < inst->max_size; i++)
		{
			cout << inst->queue[i] << " ";
		}
		for (int i = 0; i < inst->rear; i++)
		{
			cout << inst->queue[i] << " ";
		}
	}
	cout << endl;
}

int main()
{
	CircularQueueRepr inst;
	inst.max_size = 5;
	inst.front = 0;
	inst.rear = 0;

	int count = 0;

	cout << "1) Enqueue\n";
	cout << "2) Dequeue\n";
	cout << "3) Display\n";
	cout << "4) Front\n";

	while (true)
	{
		cout << "Enter choice\n";
		cin >> count;

		switch (count)
		{
		case 1:
		{
			char *x;
			x = new char[50];

			cout << "Enter element to insert: ";
			cin >> x;

			enqueue(&inst, x);
			break;
		}
		case 2:
		{
			dequeue(&inst);
			break;
		}
		case 3:
		{
			display(&inst);
			break;
		}
		case 4:
		{
			front(&inst);
			break;
		}
		case 5:
			exit(0);
		default:
			break;
		}
	}
}
