#include<iostream>
using namespace std;
struct node
{
	int info;
	struct node *left;
	struct node *right;
};
void insert(struct node*&root,int ele,int after,char r_l)
{
	if(root==NULL)
	{
		struct node*newNode=new struct node;
		root=newNode;
		newNode->info=ele;
		newNode->right=NULL;
		newNode->left=NULL;
	}
	if(root->info==after)
	{
		struct node*newNode=new struct node;
		newNode->info=ele;
		newNode->right=NULL;
		newNode->left=NULL;
		if(r_l=='r')
		{
			root->right=newNode;
		}
		else if(r_l=='l')
		  root->left=newNode;
		  
		//return 0;
	}
	//else
	if(root->right!=NULL)
	insert(root->right,ele,after,r_l);
	if(root->left!=NULL)
	insert(root->left,ele,after,r_l);
}
void inorder(struct node *&root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout<<root->info<<" ";
		inorder(root->right);
	}
}
void postorder(struct node*&root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->info<<" ";
	}
}
void preorder(struct node*&root)
{
	if(root!=NULL)
	{
		cout<<root->info<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}
int leaf_nodes(struct node *&root)
{
	if(root==NULL)
	  return 0;
	if(root->left==NULL && root->right==NULL)
	  return 1;
	else
	  return leaf_nodes(root->left)+leaf_nodes(root->right);
}
int main()
{
	struct node *root=NULL;
	int choice;
	do
	{
		cout<<"1.enter 2.inorder 3.post 4.pre 5.leaf nodes:";
		cin>>choice;
		if(choice==1)
		{
			cout<<"enter ele:";
			int ele,after;
			char c;
			cin>>ele;
			cout<<"enter ele after which to insert and r or l, enter 0 for after if first node";
			cin>>after>>c;
			insert(root,ele,after,c);
		}
		else if(choice==2)
		{
			inorder(root);
		}
		else if(choice==3)
		{
			postorder(root);
		}
		else if(choice==4)
		{
			preorder(root);
		}
		else if(choice==5)
		{
			cout<<"leafs:"<<leaf_nodes(root)<<endl;
		}
	}while(choice!=6);
}
