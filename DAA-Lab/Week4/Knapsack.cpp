
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    int count = pow(2, n);
    int matrix[count][n + 2];

    for (int i = 0; i < count; i++) {
        int k = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                matrix[i][k++] = j;
            }
        }

        for (int j = k; j < n; j++) {
            matrix[i][j] = -1;
        }
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Enter the weight for the given items: ";
    int weight[n];
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter the cost for the given items: ";
    int cost[n];
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
	cout << "enter the max weight ";
	int maxWeight ;
	cin >> maxWeight ;
	
    for (int i = 0; i < count; i++) {
        int w = 0;
        int c = 0;
        for (int k = 0; k < n && matrix[i][k] != -1; k++) {
            c += cost[matrix[i][k]];
            w += weight[matrix[i][k]];
        }
        matrix[i][n] = c;
        matrix[i][n + 1] = w;
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < n + 2; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    int sol = 0;
	for(int i = 0 ; i<count; i++){
		if(matrix[i][n+1]<=maxWeight && matrix[i][n] > matrix[sol][n]){
			sol = i;
		}
	
	}
	cout<<"required solution is : ";
	for(int i = 0 ; i<n+2;i++){
		cout << matrix[sol][i]<< " ";
	}
    return 0;
}

