#include<iostream>
using namespace std;
int main()
{
	int m,i,j,td[30][30],td1d[30],k=0;
	cout<<"Enter the number of rows and columns:";
	cin>>m;
	cout<<"\nEnter the values of tri-diagonal matrix :";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
				if(i-j>1 || i-j<-1)
			{
				td[i][j]=0;
			}
			else
			{
				cin>>td[i][j];
			}
		}
	}
	cout<<"the tri diagonal matrix is :\n\n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<td[i][j];
			cout<<"\t";	
		}
		cout<<"\n";
	}
	cout<<"\nmapping to 1d array \n";
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(i-j>1 || i-j<-1)
			{
				;
			}
			else
			{
				td1d[k]=td[i][j];
				k++;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		cout<<td1d[i];
		cout<<"  ";
	}
	cout<<"\nenter the position for retreival\n\n";
	cin>>i;
	cin>>j;
	if(i-j>1 || i-j<-1)
	cout<<td1d[2*i+j];
	else
	cout<<0;
}
