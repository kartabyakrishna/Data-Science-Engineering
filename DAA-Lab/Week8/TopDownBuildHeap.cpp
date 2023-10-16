#include <iostream>
#include <cmath>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < n && arr[left] > arr[largest])
        largest = left;
 
    if (right < n && arr[right] > arr[largest])
        largest = right;
 
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void build_heap(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int child = i;
        int parent = floor((child - 1) / 2);

        while (child > 0 && arr[child] > arr[parent]) {
            swap(arr[child], arr[parent]);
            child = parent;
            parent = floor((child - 1) / 2);
        }
    }
}

int main() {
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    build_heap(arr, n);
 
    cout << "Heap is \n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";

    return 0;
}

