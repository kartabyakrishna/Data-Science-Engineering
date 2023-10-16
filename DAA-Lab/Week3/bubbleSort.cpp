
#include <iostream>
using namespace std;

void bubbleSort(int *arr, int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

void printArray (int *arr, int n){
	cout <<"Sorted array is : " ;
	for(int i = 0 ; i<n ; i++){
		cout << arr[i] << " " ;
	}
}

int main(){
	int n;
	int arr[100];
	
	cout << "enter the number of numbers to sort : " <<endl ;
	cin>> n ;
	
	cout << "enter the numbers for sorting : " << endl;
	for (int i = 0 ; i<n ; i++){
		cin>> arr[i];
	}
	
	bubbleSort(arr,n);
	printArray(arr,n);
	
}
