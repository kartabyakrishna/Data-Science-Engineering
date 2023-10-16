
#include<iostream>
using namespace std;

void selectionSort(int *arr , int n){
	int i,min,j,temp ;
	for( i=0;i<n-1;i++)
	{
		min=i;
		for( j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min])
				{
					min=j;
				}
		}
		
		if(min!=i)
		{
			temp=arr[i];
			arr[i]=arr[min];
			arr[min]=temp;	
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
	selectionSort(arr,n);
	printArray(arr,n);
}
