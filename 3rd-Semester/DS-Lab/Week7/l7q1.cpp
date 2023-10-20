#include <iostream>
using namespace std;

struct QueueRepr
{
	int queue[10];
	int maxSize;
	int front;
	int rear;
};

int size(QueueRepr *inst)
{
	return inst->rear - inst->front;
}

bool isEmpty(QueueRepr *inst)
{
	return inst->front == inst->rear;
}

bool isFull(QueueRepr *inst)
{
	return inst->rear == inst->maxSize;
}

void enqueue(QueueRepr *inst, int element)
{
	if (isFull(inst))
	{
		cout << "Overflow!\n";
		return;
	}

	inst->queue[inst->rear++] = element;
}

void dequeue(QueueRepr *inst)
{
	if (isEmpty(inst))
	{
		cout << "Underflow!\n";
		return;
	}

	inst->front++;
}

void front(QueueRepr *inst)
{
	cout << inst->queue[inst->front] << endl;
}

void display(QueueRepr *inst)
{
	cout << "The queue is\n";
	for (int i = inst->front; i < inst->rear; i++)
	{
		cout << inst->queue[i] << " ";
	}
	cout << endl;
}

int main()
{
	QueueRepr inst;
	inst.maxSize = 10;
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
			int x;

			cout << "Enter element to insert\n";
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
