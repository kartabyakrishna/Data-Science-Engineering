#include <iostream>
using namespace std;
int main()
{
	const int INF = 1e9;
	int n;
	cout<<"Input the number of vertices : ";
	cin>>n;
	int graph[n][n],dist[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
		if(i!=j)
			graph[i][j]=INF;
		else
			graph[i][j]=0;
		}
	}
	cout<<"Input the number of edges of directed graph : ";
	int e;
	cin>>e;
	for(int i=0;i<e;i++)
	{
		int a,b;
		cout<<"Enter the 2 vertices of an edge(start to end) : ";
		cin>>a>>b;
		cout<<"Enter the weight for graph["<<a<<"]["<<b<<"] : ";
		cin>>graph[a][b];
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
				dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
			}
		}
	}
	
	cout<<"\nSHORTEST PATH MATRIX IS : "<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<dist[i][j]<<" ";
		}
		cout<<endl;
	}
}
