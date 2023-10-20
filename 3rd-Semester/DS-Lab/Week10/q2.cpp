#include<iostream>
using namespace std;
struct node
{
	int info;
	struct node *left;
	struct node *right;
};
struct node node;
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
	else
	if(root->right!=NULL)
	insert(root->right,ele,after,r_l);
	if(root->left!=NULL)
	insert(root->left,ele,after,r_l);
}
void parent_find(struct node*&root,int ele,int parent)
{
//	cout<<"hey";
	if(root==NULL)
	return;
	if(root->info==ele)
	{
		cout<<"parent:"<<parent<<endl;
		return;
	}
	
	else
	{
		parent_find(root->left,ele,root->info);
		parent_find(root->right,ele,root->info);
	}
}
int depth(struct node*&root)
{
	if(root==NULL)
	 return 0;
	else
	{
		int left_depth=depth(root->left);
		int right_depth=depth(root->right);
		if(left_depth>right_depth)
		 return (left_depth+1);
		else
		 return (right_depth+1);
	}
}
int ancestors(struct node*&root,int ele)
{
	if(root==NULL)
	 return 0;
	if(root->info==ele)
	return 1;
	if(ancestors(root->left,ele)||ancestors(root->right,ele))
	{
		cout<<root->info<<" ";
		return 1;
	}
	return 0;
}
int main()
{
	struct node*root=NULL;
	int choice;
	do
	{
		cout<<"1.enter 2.find parent 3.find depth 4.find ancestors:";
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
		if(choice==2)
		{
			cout<<"enter ele";
			int ele;
			cin>>ele;
			parent_find(root,ele,-1);
		}
		if(choice==3)
		{
			cout<<"depth:"<<depth(root)<<endl;
		}
		if(choice==4)
		{
			cout<<"Enter ele:";
			int ele;
			cin>>ele;
			ancestors(root,ele);
		}
	}while(choice!=5);
}
