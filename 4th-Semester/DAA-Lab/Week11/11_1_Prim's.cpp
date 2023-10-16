#include <iostream>
using namespace std;

const int MAX_NODES = 1000;
const int INF = 1e9;

int graph[MAX_NODES][MAX_NODES]; 
int parent[MAX_NODES]; 
int key[MAX_NODES]; 
bool visited[MAX_NODES];

void setDefault(int n) 
{
    for (int i = 0; i < n; i++) 
	{
        parent[i] = -1;
        key[i] = INF;
        visited[i] = false;
        for (int j = 0; j < n; j++) 
            graph[i][j] = 0;
    }
}

void prim(int n) 
{ 
    key[0] = 0;

    for (int i = 0; i < n - 1; i++) 
	{ 
        int min_key = INF, u;
        for (int j = 0; j < n; j++) 
		{
            if (!visited[j] && key[j] < min_key) 
			{
                min_key = key[j];
                u = j;
            }
        }
        visited[u] = true; 

        for (int v = 0; v < n; v++) 
		{ 
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) 
			{
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
}

int main() {
    int n, m;
    cout<<"ENTER NUMBER OF NODES : ";
    cin >> n;
	cout<<"ENTER NUMBER OF EDGES : ";
	cin>>m;
	
    setDefault(n); 

    for (int i = 0; i < m; i++) 
	{
        int e1, e2, w;
        cout<<"ENTER 2 POINTS OF EDGE : ";
        cin >> e1 >> e2; 
        cout<<"ENTER THE WEIGHT OF THE EDGE : ";
        cin>>w;
		graph[e1][e2] = graph[e2][e1] = w; 
    }

    prim(n); 

	int cost=0;
    cout<<"EDGES IN MINIMUM SPANNING TREE ARE : \n";
    for (int i = 1; i < n; i++) 
	{
        cout << parent[i] << " - " << i << endl;
        cost+=graph[parent[i]][i];
    }
	cout<<"MINIMUM COST OF SPANNING TREE IS : "<<cost;
    return 0;
}

