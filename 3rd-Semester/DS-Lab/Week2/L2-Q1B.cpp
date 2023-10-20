#include<iostream>
using namespace std;
int main()
{
	int m,i,j,lt[30][30],l1d[30],k=0;
	cout<<"Enter the number of rows and columns:";
	cin>>m;
	cout<<"\nEnter the values of the lower triangular matrix:\n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i<j)
			{
				lt[i][j]=0;
			}
			else
			{
				cin>>lt[i][j];
			}
		}
	}
	cout<<"The lower triangular matrix is :\n\n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<lt[i][j];
			cout<<"\t";	
		}
		cout<<"\n";
	}
	cout<<"\nMapping to 1d array \n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i>=j)
			{
				l1d[k]=lt[i][j];
				k++;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		cout<<l1d[i];
		cout<<"  ";
	}
	cout<<"\nEnter the position for retreival\n\n";
	cin>>i;
	cin>>j;
	if(i<j)
	cout<<l1d[i*(i+1)/2+j];
	else
	cout<<0;
}
