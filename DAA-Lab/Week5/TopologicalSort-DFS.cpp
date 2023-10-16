#include<iostream>
using namespace std;

int n,adj[100][100],indegree[100],stack[100],top=-1;

void dfs(int v,bool visited[],int stack[])
{
    visited[v]=true;

    for(int i=0;i<n;i++)
    {
        if(adj[v][i] == 1 && !visited[i])
        {
            dfs(i,visited,stack);
        }
    }

    stack[++top] = v;
}

void topsort()
{
    bool visited[100] = {false};
    int i, j;

    for(i=0;i<n;i++)
    {
        if(!visited[i])
        {
            dfs(i,visited,stack);
        }
    }

    cout<<"The Topological Order of the Graph is : ";
    for(i=top;i>=0;i--)
    {
        cout<<stack[i]<<" ";
    }
}

int main()
{
    int i,j,e,u,v;

    cout<<"Enter the number of vertices in the Graph : ";
    cin>>n;

    cout<<"Enter the number of edges in the Graph : ";
    cin>>e;

    cout<<"Enter the edges of the Graph : "<<endl;

    for(i=0;i<e;i++)
    {
        cin>>u>>v;
        adj[u][v] = 1;
    }

    topsort();

    return 0;
}

