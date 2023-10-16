#include <iostream>
using namespace std;
int main()
{
	int n;
	cout<<"Input the number of vertices : ";
	cin>>n;
	int graph[n][n],dist[n][n];
	cout<<"Input the number of edges of directed graph : ";
	int e;
	cin>>e;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			graph[i][j]=0;
		}
	}
	for(int i=0;i<e;i++)
	{
		int a,b;
		cout<<"Enter the 2 vertices of an edge(start to end) : ";
		cin>>a>>b;
		graph[a][b]=1;
	}
	cout<<"WEIGHTED ADJACENCY MATRIX IS : "<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			dist[i][j]=graph[i][j];
			cout<<graph[i][j]<<"  ";
		}
		cout<<endl;
	}
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(dist[i][k]==1 && dist[k][j]==1)
				{
					dist[i][j] = 1;
				}
			}
		}
	}
	cout<<"\nTRANSITIVE CLOSURE IS : "<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<dist[i][j]<<" ";
		}
		cout<<endl;
	}
}
