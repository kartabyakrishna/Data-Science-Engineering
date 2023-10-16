#include <iostream>
using namespace std;

void comparisonCountingSort(int A[], int n, int Count[]) {
    int S[n];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i] < A[j]) {
                Count[j]++;
            } else {
                Count[i]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        S[Count[i]] = A[i];
    }
    for (int i = 0; i < n; i++) {
        A[i] = S[i];
    }
}

int main() {
    int A[] = {3, 1, 4, 1, 5, 9, 2, 1, 5, 3, 5,9,9};
    int n = sizeof(A) / sizeof(A[0]);
    int Count[n] = {0};
    comparisonCountingSort(A, n, Count);
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\nCount array: ";
    for (int i = 0; i < n; i++) {
        cout << Count[i] << " ";
    }
    return 0;
}

