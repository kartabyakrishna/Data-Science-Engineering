#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

int deleteMin(int arr[], int& n)
{
    if (n == 0)
    {
        cout << "Heap is empty.";
        return -1;
    }

    int root = arr[0];
    arr[0] = arr[n - 1];
    n--;

    heapify(arr, n, 0);

    return root;
}

int main()
{
    int n;
    cout << "Enter the number of elements in the heap: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Enter the elements of the heap: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // Building the heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    cout << "Original heap: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    int minValue = deleteMin(arr, n);
    cout << "Deleted element of smallest value: " << minValue << endl;

    cout << "Heap after deletion: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete[] arr;

    return 0;
}

