#include <iostream>
using namespace std;
int arr[5];
void selection_sort()
{
	int min=0,j;
	for(int i=0;i<4;i++)
	{
		min = i;
		for(j=i+1;j<5;j++)
		{
			if(arr[j]<arr[min])
			{
				min=j;
			}
		}
		int temp = arr[min];
		arr[min]=arr[i];
		arr[i]=temp;
	}
}
void bubble_sort()
{
	int i=0;
	bool sorted=false;
	while(i<=4 && sorted==false)
	{
		int j=4;
		sorted=true;
		while(j>i)
		{
			if(arr[j]<arr[j-1])
			{
				sorted =false;
				int temp=arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
			}
			j--;
		}
		i++;
	}
}
int partition(int a[],int low,int high)
{
	int key = a[low];
	int i = low+1,j=high;
	while(i<high && key>=a[i])
		i++;
	while(key<a[j]) 
		j--;
	if(i<j)
	{
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	else
	{
		int temp = a[low];
		a[low] = a[j];
		a[j] = temp;
	}
	return j;
}
void quick_sort(int a[],int low,int high)
{
	if(low<high)
	{
		int mid = partition(a,low,high);
		quick_sort(a,low,mid-1);
		quick_sort(a,mid+1,high);
	}
	for(int i=0;i<5;i++)
	{
		arr[i] = a[i];
	}
}
void insertion_sort()
{
	int i=1;
	int t;
	while(i<5)
	{
		t = arr[i];
		int j = i-1;
		while(j>=0 && t<arr[j])
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1]=t;
		i++;
	}
}
int main()
{
	cout<<"Input array of 5 elements : "<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<"Input element"<<i+1<<endl;
		cin>>arr[i];
	}
	
	int ch;
	cout<<"\n1.SS\n2.BS\n3.MS\n4.QS\nEnter Choice : ";
	cin>>ch;
	if(ch==1)
		selection_sort();
	else if (ch==2)
		bubble_sort();
 	else if(ch==3)
		quick_sort(arr,0,4);
	else if(ch==4)
		insertion_sort();
	else 
		cout<<"INVALID CHOICE"<<endl;
		
	//DISPLAY THE ARRAY
	for(int i=0;i<5;i++)
		cout<<arr[i]<<" ";
	return 0;
}
