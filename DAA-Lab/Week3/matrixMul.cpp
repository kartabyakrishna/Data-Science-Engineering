
#include <iostream>
using namespace std;
void multiply(int A[][10], int B[][10], int C[][10], int m, int n, int p) {
for (int i = 0; i < m; i++) {
for (int j = 0; j < p; j++) {
C[i][j] = 0;
for (int k = 0; k < n; k++) {
C[i][j] += A[i][k] * B[k][j];
}
}
}
}
int main() {
int A[10][10], B[10][10], C[10][10];
int m, n, p;
cout << "Enter the number of rows of matrix A: ";
cin >> m;
cout << "Enter the number of columns of matrix A: ";
cin >> n;
cout << "Enter the elements of matrix A: " << endl;
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++) {
cin >> A[i][j];
}
}
cout << "Enter the number of rows of matrix B: ";
cin >> n;
cout << "Enter the number of columns of matrix B: ";
cin >> p;
cout << "Enter the elements of matrix B: " << endl;
for (int i = 0; i < n; i++) {
for (int j = 0; j < p; j++) {
cin >> B[i][j];
}
}
multiply(A, B, C, m, n, p);
cout << "Resultant matrix: " << endl;
for (int i = 0; i < m; i++) {
for (int j = 0; j < p; j++) {
cout << C[i][j] << " ";
}
cout << endl;
}
return 0;
}
