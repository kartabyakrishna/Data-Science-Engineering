// UPPER TRIANGULAR MATRIX
#include<iostream>
using namespace std;
int main()
{
	int m,i,j,k=0,ut[30][30],u1d[30];
	cout<<"Enter the number of rows and columns:";
	cin>>m;
	cout<<"\nEnter the values of the upper triangular matrix:\n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i>j)
			{
				ut[i][j]=0;
			}
			else
			{
				cin>>ut[i][j];
			}
		}
	}
    cout<<"\nThe upper triangular matrix is :\n\n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<ut[i][j];
			cout<<"\t";	
		}
		cout<<"\n";
	}
	cout<<"\nMapping to 1d array \n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++) 
		{
			if(i<=j)
			{
				u1d[k]=ut[i][j];
				k++;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		cout<<u1d[i];
		cout<<"  ";
	}
	cout<<"\nEnter the position i & j for retreival \n\n";
	cin>>i;
	cin>>j;
	if(i>j)
	cout<<u1d[(m*i)+j-(i*(i+1)/2)];
	else
	cout<<0;
}
