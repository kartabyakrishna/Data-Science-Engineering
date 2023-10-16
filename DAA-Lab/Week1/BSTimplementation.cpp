
#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node* left, *right;
		Node(int data){
			this->data = data;
			this->left =NULL;
			this->right = NULL;
		}
};
Node* root = NULL;
void insert(int data){
	Node *nN = new Node(data);
	Node *node = root;
	while(true){
		if(node == NULL){
			root = nN;
			break;
		}
		else if (data> node->data){
			if (node->right==NULL){
				node->right =nN;
				break;
			}
			else{
				node = node->right;
			}
		}
		else{
			if(node->left== NULL){
				node->left =nN;
				break;
			}else{
				node = node->left;
			}
		}
	}
}
int searchAndInsert_BST(int data){
	Node * node = root;
	while(node!= NULL){
		if(node->data == data){
			return 1;
		}
		else if (data > node->data){
			node = node->right ;
		}
		else{
			node = node->left;
		}
	}
		if(node==NULL){
			insert(data);
			return 0 ;
		}
	}
void Inorder(Node* node){
	if(node == NULL){
		return;
	}
	Inorder(node->left);
	cout<<node->data<<" ";
	Inorder(node->right);
}
void Preorder(Node* node){
	if(node ==NULL){
		return;
	}
	cout<<node->data<<" ";
	Preorder(node->left);
	Preorder(node->right);	
}
void Postorder(Node* node){
	if (node==NULL){
		return;
	}
	Postorder(node->left);
	Postorder(node->right);
	cout<< node->data<< " ";
}
int main(){
	int ch = 0, data,n,r;
	do{
		cout<<"1-Enter elements\n2-Search elements\n3-Inorder\n4-Preorder\n5-Postorder\n";
		cin>>ch;
		switch(ch){
			case 1:
				cout << "How many elements : ";
				cin>> n ;
				for(int i = 0; i<n ; i++){
					cin >> data;
					r = searchAndInsert_BST(data);
					if(r == 1){
						cout << "duplicate element!"<<endl;
						i--;	
					}
				}
				break;
			case 2:
				cout << "enter element to search: "<<endl;
				cin >> data;
				r = searchAndInsert_BST(data);
				if(r==1){
					cout<<"key found";
				}
				else{
					cout<<"key not found and inserted"<<endl;
				}
				break;
			case 3:
				cout << "inorder : "<<endl;
				Inorder(root);
				cout<<endl;
				break;
			case 4:
				cout<< "preorder : "<<endl;
				Preorder(root);
				cout<<endl;
				break;
			case 5:
				cout << "postorder : "<<endl;
				Postorder(root);
				cout<<endl;
				break;
			default :
				cout<< " invalid choice ";
		}
	}while(ch!=6);
	return 0;
} 
