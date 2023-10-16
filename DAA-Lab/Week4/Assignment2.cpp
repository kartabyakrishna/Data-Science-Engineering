#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 10; 
const int MAXC = 3628800;

int n; 
int a[MAXN][MAXN]; 
int p[MAXN];
bool used[MAXN]; 

int results[MAXC][MAXN + 1]; 
int num_results = 0; 

void search(int i) {
    if (i == n) {
        for (int j = 0; j < n; j++) {
            results[num_results][j] = p[j];
        }
        int cost = 0;
        for (int j = 0; j < n; j++) {
            cost += a[j][p[j]];
        }
        results[num_results][n] = cost;
        num_results++;
        return;
    }

    for (int j = 0; j < n; j++) {
        if (!used[j]) {
            used[j] = true;
            p[i] = j;
            search(i + 1);
            used[j] = false;
        }
    }
}

int main() {
	cout<< "enter the number of jobs and people";
    cin >> n;
	cout<<"enter the job cost matrix";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    search(0);

    cout << "All permutations and their costs:" << endl;
    for (int i = 0; i < num_results; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << results[i][j];
            if (j != n - 1) cout << ", ";
        }
        cout << "] with cost " << results[i][n] << endl;
    }

    return 0;
}
