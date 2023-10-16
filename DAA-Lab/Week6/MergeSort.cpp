#include <iostream>

using namespace std;

void merge(int B[], int p, int C[], int q, int A[]) {
    int i = 0, j = 0, k = 0;

    while (i < p && j < q) {
        if (B[i] <= C[j]) {
            A[k] = B[i];
            i++;
        } else {
            A[k] = C[j];
            j++;
        }
        k++;
    }

    if (i == p) {

        while (j < q) {
            A[k] = C[j];
            j++;
            k++;
        }
    } else {

        while (i < p) {
            A[k] = B[i];
            i++;
            k++;
        }
    }
}

void mergeSort(int A[], int n) {
    if (n > 1) {
        int mid = n / 2;
        int B[mid];
        int C[n - mid];


        for (int i = 0; i < mid; i++)
            B[i] = A[i];
        for (int i = mid; i < n; i++)
            C[i - mid] = A[i];


        mergeSort(B, mid);
        mergeSort(C, n - mid);

        merge(B, mid, C, n - mid, A);
    }
}

int main() {
    int A[] = {5, 2, 8, 3, 1};
    int n = sizeof(A) / sizeof(A[0]);

    cout << "Before sorting: ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;

    mergeSort(A, n);

    cout << "After sorting: ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;

    return 0;
}

