#include<iostream>
using namespace std;
struct node
{
	int info;
	struct node *left;
	struct node *right;
};
struct node node;

int create(struct node *&root,int ele)
{
	
	//struct node *temp=root;

	if(root==NULL)
	{
		struct node*newNode=new struct node;
		newNode->info=ele;
		newNode->left=NULL;
		newNode->right=NULL;
		root=newNode;
		return newNode->info;
	}
	if(ele<root->info)
	  return create(root->left,ele);
	else
	  return create(root->right,ele);
}
int search(struct node *&root,int ele)
{
	struct node *temp=root;
	if(root==NULL)
	{
		cout<<"not found";
		return 0;
	}
	if(ele<root->info)
	  return search(root->left,ele);
	else if(ele>root->info)
	  return search(root->right,ele);
	else
	{
		cout<<"found:";
		return root->info;
	}	 
}
int main()
{
	struct node *root=NULL;
	int choice;
	do
	{
		cout<<"1.enter 2.search:";
		cin>>choice;
		if(choice==1)
		{
			cout<<"enter ele:";
			int ele;
			cin>>ele;
			cout<<create(root,ele);
		}
		else if(choice==2)
		{
			cout<<"enter search ele:";
			int ele;
			cin>>ele;
			cout<<search(root,ele);
		}
	}while(choice!=3);
}
