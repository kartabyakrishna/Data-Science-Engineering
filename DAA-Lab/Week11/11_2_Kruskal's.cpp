#include <iostream>
using namespace std;

const int MAX_NODES= 1000;

int parent[MAX_NODES]; 
int edges[MAX_NODES * (MAX_NODES - 1) / 2][3]; 
int num_edges; 

void setDefault(int n) 
{
    for (int i = 0; i < n; i++)
        parent[i] = i;
    num_edges = 0;
}

int find(int u) 
{ // find the root of the set containing u
    while (u != parent[u]) 
        u = parent[u];
    
    return u;
}

void merge(int u, int v) 
{ // merge the sets containing u and v
    parent[find(u)] = find(v);
}

void kruskal(int n) 
{ // n is the number of nodes in the graph
    int mst_weight = 0; // weight of the minimum spanning tree

    for (int i = 0; i < num_edges; i++) 
	{ // sort the edges in increasing order of weight
        for (int j = i + 1; j < num_edges; j++) 
		{
            if (edges[i][2] > edges[j][2]) 
			{
                swap(edges[i], edges[j]);
            }
        }
    }

    for (int i = 0; i < num_edges; i++) 
	{ // loop through all edges in the sorted order
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        if (find(u) != find(v)) 
		{ // check if u and v belong to different sets
            merge(u, v); 
            mst_weight += w; // add the weight of the edge to the total weight of the minimum spanning tree
            cout << u << " - " << v <<"("<<w<<") "<<endl; // print the edge in the minimum spanning tree
        }
    }

    cout << "Weight of the minimum spanning tree: " << mst_weight << endl;
}

int main() 
{
    int n, m;
    cout<<"ENTER NUMBER OF NODES AND EDGES : ";
    cin >> n >> m;
    
    setDefault(n); 
    
    for (int i = 0; i < m; i++) 
	{
        int u, v, w;
        cout<<"ENTER 2 POINTS OF AN EDGE : \n";
        cin >> u >> v; // input an edge (u, v) with weight w
        cout<<"ENTER WEIGHT : ";
        cin>>w;
        edges[num_edges][0] = u;
        edges[num_edges][1] = v;
        edges[num_edges][2] = w;
        num_edges++; // add the edge to the edges array and update the number of edges
    }

    kruskal(n); // run Kruskal's Algorithm

    return 0;
}

