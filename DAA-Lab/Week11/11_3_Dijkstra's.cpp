#include <iostream>
using namespace std;

const int MAX_NODES = 1000;
const int INF = 1e9;

int dist[MAX_NODES];
bool visited[MAX_NODES]; 
int graph[MAX_NODES][MAX_NODES]; 
int n;

void setDefault(int source) 
{
	
    for (int i = 0; i < n; i++) 
	{
        dist[i] = INF;
        visited[i] = false;
    }
    dist[source] = 0;
}

int find_min_distance() 
{
    int min_dist = INF, min_node = -1;
    for (int i = 0; i < n; i++) 
	{
        if (!visited[i] && dist[i] < min_dist) 
		{
            min_dist = dist[i];
            min_node = i;
        }
    }
    return min_node;
}

void dijkstra(int source) 
{ 
    setDefault(source);

    for (int i = 0; i < n - 1; i++) 
	{ 
        int u = find_min_distance(); 
        visited[u] = true;

        for (int v = 0; v < n; v++) 
		{ 
            if (!visited[v] && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v]; 
            
        }
    }

    cout << "Shortest distances from the source node to all other nodes:" << endl;
    for (int i = 0; i < n; i++) 
        cout << i << ": " << dist[i] << endl;
    
}

int main() 
{
    int m;
    cout<<"Input Nodes : ";
    cin >> n; 
    cout<<"INput edges : ";
    cin>>m;
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++) 
            graph[i][j] = 0;
        
    }

    for (int i = 0; i < m; i++) 
	{
        int u, v, w;
        cout<<"INPUT 2 POINTS OF AN EDGE : \n";
        cin >> u >> v; 
        cout<<"Input weight : ";cin>>w;
		graph[u][v] = w;
    }

    dijkstra(0);

    return 0;
}

