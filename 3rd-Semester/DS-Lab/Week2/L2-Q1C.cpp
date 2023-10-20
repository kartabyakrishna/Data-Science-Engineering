#include<iostream>
using namespace std;
int main()
{
	int m,i,j,d[30][30],d1d[30],k=0;
	cout<<"Enter the number of rows and columns:";
	cin>>m;
	cout<<"\nEnter the values of diagonal matrix :";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i==j)
			{
			cin>>d[i][j];
			}
			else
			{
				d[i][j]=0;
			}
		}
	}
	cout<<"The diagonal matrix is :\n\n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<d[i][j];
			cout<<"\t";
		}
		cout<<"\n";
	}
	cout<<"\nMapping to 1d array \n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i==j)
			{
				d1d[k]=d[i][j];
				k++;
			}
		}
	}
		for(i=0;i<k;i++)
		{
		cout<<d1d[i];
		cout<<"  ";
		}
	cout<<"\nEnter the position for retreival\n\n";
	cin>>i;
	cin>>j;
	if(i==j)
	cout<<d1d[(i+j)/2];
	else
	cout<<0;
	
}
