#include<iostream>
using namespace std;
struct Element{
	int coefficient;
	int exponent;
};
struct node{
	Element data;
	node* prev;
	node* next;
};
void insertPoly(node *head , Element data){
	node* newNode = new node;
	newNode->data = data;
	newNode->next = NULL;
	if(head->next ==NULL){
		head->next = newNode;
		newNode->prev = NULL;
		return;
	}
	
	node *temp = head->next;
	while(temp->next!= NULL){
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}
void printPoly(node *head){
	node* temp = head->next;
	while(temp->next != NULL){
		if(temp->data.exponent == 0){
			cout<<temp->data.coefficient<<" +";
		}
		else if(temp->data.coefficient == 0){
			continue;
		}
		else{
			cout<<temp->data.coefficient<<"x^"<<temp->data.exponent<<" +";
		}
		temp = temp->next;
	}
		if(temp->data.exponent == 0){
			cout<<temp->data.coefficient<<endl;
		}
		else if(temp->data.coefficient == 0){
			cout<<" \n";
		}
		else{
			cout<<temp->data.coefficient<<"x^"<<temp->data.exponent<<endl;
		}
}
void readPoly(node *head){
	int n ;
	Element data;
	cout<<"Enter the number of terms in the polynomial\n";
	cin>>n;
	cout<<"Enter the polynomial in descending order of exponent\n ";
	for(int i=0;i<n;i++){
	cout<<"Enter coeffiecient \n";
	cin>>data.coefficient;
	cout<<"Enter exponent\n";
	cin>>data.exponent;
	insertPoly(head,data);
	}
	
}
void polyAdd(node* head1, node* head2 , node* head3){
	node* temp1 = head1->next;
	node* temp2 = head2->next;
	Element flag;
	while(temp1 != NULL && temp2 != NULL){
		if(temp1->data.exponent > temp2->data.exponent){
			flag = temp1->data;
			insertPoly(head3,flag);
			temp1 =temp1->next;
		}
		else if(temp2->data.exponent > temp1->data.exponent){
			flag = temp2->data;
			insertPoly(head3,flag);
			temp2=temp2->next;
		}
		else{
			flag.coefficient = temp1->data.coefficient + temp2->data.coefficient;
			flag.exponent = temp1->data.exponent;
			insertPoly(head3,flag);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	if(temp1 != NULL){
		while(temp1 != NULL){
			flag = temp1->data;
			insertPoly(head3,flag);
			temp1= temp1->next;
		}
	}
	else{
		while(temp2 != NULL){
			flag = temp2->data;
			insertPoly(head3,flag);
			temp2= temp2->next;
		}
	}
}




int main(){
	node *head1 = new node;
	node *head2 = new node;
	node *head3 = new node;
	head1->next = NULL;
	head2->next =NULL;
	head3->next =NULL;
	cout<<"Enter poly 1"<<endl;
	readPoly(head1);
	printPoly(head1);
	cout<<"Enter poly 2"<<endl;
	readPoly(head2);
	printPoly(head2);
	cout<<"The sum is:\n";
	polyAdd(head1,head2,head3);
	printPoly(head3);
	
	return 0;
}
