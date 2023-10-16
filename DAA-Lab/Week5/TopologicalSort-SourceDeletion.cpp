#include<iostream>
using namespace std;

int n,adj[100][100],inDeg[100];

bool topSort()
{
   int i,j,k;
   bool cyclic = false;

   for(i=0;i<n;i++)
   {
      inDeg[i]=0;
   }

   for(i=0;i<n;i++)
   {
      for(j=0;j<n;j++)
      {
         if(adj[i][j]==1)
         {
            inDeg[j]++;
         }
      }
   }

   cout<<"The Topological Order of the Graph is : ";

   for(i=0;i<n;i++)
   {
      bool found = false;
      for(j=0;j<n;j++)
      {
         if(inDeg[j]==0)
         {
            found = true;
            cout<<j<<" ";
            inDeg[j]=-1;

            for(k=0;k<n;k++)
            {
               if(adj[j][k]==1)
               {
                  inDeg[k]--;
               }
            }
            break;
         }
      }

      if(!found) {
         cyclic = true;
         break;
      }
   }

   if(cyclic) {
      cout << "\nThe given graph is cyclic.\n";
   } else {
      cout << "\nThe given graph is acyclic.\n";
   }

   return !cyclic;
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

   bool isAcyclic = topSort();

   if(isAcyclic) {
      cout << "\nThe given graph has a Topological order.\n";
   } else {
      cout << "\nThe given graph does not have a Topological order.\n";
   }

   return 0;
}

