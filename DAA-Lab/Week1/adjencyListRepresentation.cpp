

#include<iostream>
 using namespace std;
 
int main()
{
	int i, v, e, j, count;
 
	// take the input of the number of vertex and edges.
	cout<<"Enter the number of vertexes of the graph: ";
	cin>>v;
	cout<<"\nEnter the number of edges of the graph: ";
	cin>>e;
	int edge[e][2];
 
	// Take the input of the adjacent vertex pairs of the given graph.
	for(i = 0; i < e; i++)
	{
		cout<<"\nEnter the vertex pair for edge "<<i+1;
		cout<<"\nV(1): ";
		cin>>edge[i][0];
		cout<<"V(2): ";
		cin>>edge[i][1];
	}
 
	// Print the adjacency list representation of the graph.
	cout<<"\n\nThe adjacency list representation for the given graph: ";
	for(i = 0; i < v; i++)
	{
		count = 0;
		// For each vertex print, its adjacent vertex.
		cout<<"\n\t"<<i+1<<"-> { ";
		for(j = 0; j < e; j++)
		{
			if(edge[j][0] == i+1)
			{
				cout<<edge[j][1]<<"  ";
				count++;
			}
			else if(edge[j][1] == i+1)
			{
				cout<<edge[j][0]<<"  ";
				count++;
			}
			else if(j == e-1 && count == 0)
				cout<<"Isolated Vertex!";
		}
		cout<<" }";
	}
}
