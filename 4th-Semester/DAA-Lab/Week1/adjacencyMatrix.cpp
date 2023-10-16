
#include<iostream>
using namespace std;

int main(){
	int v, e ;
	cout<< "number of vertices";
	cin >> v ;
	cout << "number of edges";
	cin >> e ;
	
	int adj[v][v];
	for (int i = 0 ; i<v ; i++){
		for (int j = 0 ; j<v ; j++){
		adj[i][j]=0;
	}
	}

	for (int i =0 ; i<e ; i++){
		int u , v ;
		cin >> u >> v;
		adj[u-1][v-1] = 1 ;
		adj[v-1][u-1] = 1 ;
	
	}
	for (int i = 0 ; i<v ; i++){
		for (int j = 0 ; j<v ; j++){
			cout << adj[i][j] << " ";
		}cout<<endl;
	}
	return 0;
}
