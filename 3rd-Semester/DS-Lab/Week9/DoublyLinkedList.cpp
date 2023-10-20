#include<iostream>
using namespace std;
struct node{
	int data;
	node* prev;
	node* next;
};
void insertRear(node *head,int data){
	node* newNode = new node;
	node* last = head;
	newNode->data = data;
	newNode->next = NULL;
	
	if(head->next == NULL){
		newNode->prev = NULL;
		head->next = newNode;
		return;
	}
	while(last->next != NULL){
		last = last->next;
	}
	last->next=newNode;
	newNode->prev = last;
	
}
void insertAfter(node *head,int element, int data){
	node *temp = head->next;
	
	while(temp->data != element){
		if(temp->next == NULL){
			cout<<"The given element is not present in the list\n";
			return;
		}
		temp = temp->next;
	}
	if(temp->next == NULL){
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;
		newNode->prev = temp;
		temp->next = newNode;
	}
	else{
		node* newNode = new node;
		newNode->data = data;
		newNode->next = temp->next;
		temp->next = newNode;
		newNode->prev = temp;
		newNode->next->prev = newNode;
	}
	
	
}
void insertBefore(node *head,int element, int data){
	node *temp = head->next;
	while(temp->data != element){
		temp = temp->next;
	}
	if(temp->prev == NULL){
		node *newNode = new node;
		head->next = newNode;
		newNode->data = data;
		newNode->prev = NULL;
		temp->prev = newNode;
		newNode->next = temp;
		
	}
	else{
		node *newNode = new node;
		newNode->data = data;
		newNode->prev = temp->prev;
		temp->prev = newNode;
		newNode->next = temp;
		newNode->prev->next = newNode;
	}
	
}
void printList(node *head){
	node *temp = head->next;
	cout<<"Traversing forward :\n";
	while(temp->next!= NULL){
		cout<<" "<<temp->data<<" ";
		temp = temp->next;
	}
	cout<<temp->data<<endl;
	cout<<"Traversing Backward:\n";
	while(temp->prev!=NULL){
		cout<<" "<<temp->data<<" ";
		temp = temp->prev;
	}
	cout<<temp->data<<endl;
}
void deleteRear(node *head){
	node* temp = head->next;
	if(head->next == NULL ){
		cout<<"The list is empty \n";
		return;
	}
	if(temp->next == NULL){
		head->next = NULL;
		delete temp;
		return;
	}
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->prev->next = NULL;
	delete temp;
}
void deleteAfter(node* head,int element){
	node* temp = head->next;
	if(head->next == NULL){
		cout<<"The list is empty \n";
		return;
	}
	while(temp->data != element){
		temp=temp->next;
		if(temp ==NULL){
			cout<<"Element is not present in the list\n";
			return;
		}
		else{
			continue;
		}
	}
	temp= temp->next;
	if(temp->next == NULL){
		temp->prev->next = NULL;
		delete temp;
	}
	else if(temp ==NULL){
		cout<<"Nothing to delete after the element\n";
		return;
	}
	else{
		temp->prev->next = temp->next;
		temp->next->prev =temp->prev;
		delete temp;
		
	}
}
void deleteBefore(node *head,int element){
	node *temp = head->next;
	if(temp == NULL){
		cout<<"List is empty \n";
		return;
	}
	while(temp->next->data != element){
		temp = temp->next;
		if(temp->next == NULL){
			cout<<"The element is not in the list \n";
			return;
		}
		else{
			continue;
		}
	}
	if(temp->prev == NULL){
		head->next = temp->next;
		temp->next->prev =NULL;
		delete temp;
	}
	else{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;	
	}
		
}
int main(){
	int choice,data,element;
	node* head = new node;
	head->next = NULL;	
	cout<<"1.Insert Rear \n";
	cout<<"2.Delete Rear \n";
	cout<<"3.Insert After \n";
	cout<<"4.Delete After \n";
	cout<<"5.Insert Before \n";
	cout<<"6.Delete Before \n";
	cout<<"7.Display list\n";
	cout<<"8.Exit\n";
	do{
		cout<<"Enter your choice\n";
		cin>>choice;
		switch(choice){
			case 1:
				cout<<"Enter data :\n";
				cin>> data;
				insertRear(head,data);
				break;
			case 2:
				deleteRear(head);
				cout<<"deleted rear\n";
				break;				
			case 3:
				cout<<"Enter data:\n";
				cin>>data;
				cout<<"Enter the element after which the data is to be inserted\n";
				cin>>element;
				insertAfter(head,element,data);
				break;
			case 4:
				cout<<"Enter the element after which the data is to be deleted\n";
				cin>>element;
				deleteAfter(head,element);
				cout<<"Element deleted\n";
				break;
			case 5:
				cout<<"Enter data:\n";
				cin>>data;
				cout<<"Enter the element before which the data is to be inserted.\n";
				cin>>element;
				insertBefore(head,element,data);
				break;
			case 6:
				cout<<"Enter the element before which the data is to be deleted\n";
				cin>>element;
				deleteBefore(head,element);
				cout<<"Element deleted\n";
				break;
			case 7:
				printList(head);
				break;
			case 8:
				break;
			default:
				cout<<"Wrong choice!\n";
				break;
				
		}
	}while(choice!=8);
	
}
