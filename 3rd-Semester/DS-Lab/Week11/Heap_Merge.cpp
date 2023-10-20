#include <iostream>
using namespace std;
void heapify(int arr[], int N, int i)
{
    int largest = i;
    int l = 2 * i + 1; 
    int r = 2 * i + 2;
    if (l < N && arr[l] > arr[largest])
        largest = l;
    if (r < N && arr[r] > arr[largest])
        largest = r;
    if (largest != i) 
	{
        //swap(arr[i], arr[largest]);
        int t = arr[i]; arr[i] = arr[largest]; arr[largest] = t;
        heapify(arr, N, largest);
    }
}
void heapSort(int arr[], int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
    for (int i = N - 1; i > 0; i--) 
	{
        //swap(arr[0], arr[i]);
        int t = arr[0]; arr[0] = arr[i]; arr[i] = t;
        heapify(arr, i, 0);
    }
}

void merge(int array[], int left, int mid,int right)
{
    int a1 = mid - left + 1;
    int a2 = right - mid;
 
    // Create temp arrays
    int *leftArray = new int[a1] , *rightArray = new int[a2];
 
    for (int i = 0; i < a1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < a2; j++)
        rightArray[j] = array[mid + 1 + j];
 
    int pos_a1= 0, pos_a2= 0; 
    int merged = left;
 
    // Merge the temp arrays back into array[left..right]
    while (pos_a1 < a1 && pos_a2 < a2) 
	{
        if (leftArray[pos_a1] <= rightArray[pos_a2]) 
		{
            array[merged] = leftArray[pos_a1];
            pos_a1++;
        }
        else 
		{
            array[merged] = rightArray[pos_a2];
            pos_a2++;
        }
        merged++;
    }
    while (pos_a1 < a1) 
	{
        array[merged] = leftArray[pos_a1];
        pos_a1++;
        merged++;
    }
    while (pos_a2 < a2) 
	{
        array[merged] = rightArray[pos_a2];
        pos_a2++;
        merged++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
void mergeSort(int a[], int begin, int end)
{
    if (begin >= end)
        return; 
 	
	int mid = begin + (end - begin) / 2;
    mergeSort(a, begin, mid);
    mergeSort(a, mid + 1, end);
    merge(a, begin, mid, end);
}
int main()
{
	int arr[5];
    cout<<"Input array of 5 elements : "<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<"Input element"<<i+1<<endl;
		cin>>arr[i];
	}
	int ch;
	cout<<"1.HEAPSORT 2.MERGESORT\nENTER CHOICE : ";
	cin>>ch;
	if(ch==1)
    	heapSort(arr, 5);
    else if(ch==2)
		mergeSort(arr,0,4);    
		
    cout << "Sorted array is \n";
    for (int i = 0; i < 5; ++i)
        cout << arr[i] << " ";
}
