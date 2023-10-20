#include <iostream>
using namespace std;
struct Node
{
	int data;
	Node *next;
};
void display(Node *node)
{
	cout << "The list is :\n";
	while (node != NULL)
	{
		cout << node->data << "-->";
		node = node->next;
	}

	if (node == NULL)
		cout << "null\n";
}
void InsertBegin(struct Node **head, int node_data)
{
	Node *newNode = new Node;
	newNode->data = node_data;
	newNode->next = (*head);
	(*head) = newNode;
}
void InsertEnd(struct Node **head, int node_data)
{
	Node *newNode = new Node;

	Node *last = *head;
	newNode->data = node_data;
	newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	return;
}
void InsertAfter(Node *head, int data, int element)
{
	Node *temp = head;
	while (temp->data != data)
	{
		if (temp->next == NULL)
			cout << "given data not in the list\n";
		else
			temp = temp->next;
	}
	Node *newNode = new Node;
	newNode->data = element;
	newNode->next = temp->next;
	temp->next = newNode;
}
void InsertBefore(Node *head, int data, int element)
{
	Node *temp = head;
	while (temp->next->data != data)
	{
		if (temp->next == NULL)
			cout << "given data not in the list\n";
		else
			temp = temp->next;
	}
	Node *newNode = new Node;
	newNode->data = element;
	newNode->next = temp->next;
	temp->next = newNode;
}
void Delete(Node *head, int data)
{
	Node *temp;
	if (head->data == data)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	else
	{
		Node *current = head;
		while (current->next != NULL)
		{
			if (current->next->data == data)
			{
				temp = current->next;
				current->next = current->next->next;
				delete temp;
				return;
			}
			else
				current = current->next;
		}
	}
	cout << "Element not found !\n";
}
int main()
{
	Node *head = NULL;
	int choice, element;
	cout << "1) Insert at the beggining .\n";
	cout << "2) Insert at the end.\n";
	cout << "3) Insert after a given element\n";
	cout << "4) Insert before a given element\n";
	cout << "5) Delete a given element\n";
	cout << "6) Display the list\n";
	cout << "Exit\n";
	do
	{
		cout << "Enter choice \n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			element;
			cout << "Enter the element to insert\n";
			cin >> element;
			InsertBegin(&head, element);
			break;
		case 2:
			element;
			cout << "Enter the element to insert \n";
			cin >> element;
			InsertEnd(&head, element);
			break;
		case 3:
			cout << "Enter the element to insert \n";
			cin >> element;
			int data;
			cout << "Enter the data after which insertion is to be done\n";
			cin >> data;
			InsertAfter(head, data, element);
			break;
		case 4:
			cout << "Enter the element to insert \n";
			cin >> element;
			cout << "Enter the data before which insertion is to be done\n";
			cin >> data;
			InsertBefore(head, data, element);
			break;
		case 5:
			cout << "Enter the element to be deleted\n";
			cin >> element;
			Delete(head, element);
			break;

		case 6:
			display(head);
			break;
		case 7:
			break;
		default:
			cout << "Enter a valid option :\n";
			break;
		}

	} while (choice != 7);
	return 0;
}
