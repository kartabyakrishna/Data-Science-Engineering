#include <iostream>
using namespace std;

int hoarePartition(int arr[], int l, int r)
{
    int p = arr[l];
    int i = l, j = r + 1;

    while (true)
    {
        do
        {
            i++;
        } while (arr[i] < p);

        do
        {
            j--;
        } while (arr[j] > p);

        if (i >= j)
            break;

        swap(arr[i], arr[j]);
    }

    swap(arr[l], arr[j]);
    return j;
}

void quickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int s = hoarePartition(arr, l, r);
        quickSort(arr, l, s - 1);
        quickSort(arr, s + 1, r);
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete[] arr;

    return 0;
}

