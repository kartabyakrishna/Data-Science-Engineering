#include <iostream>
using namespace std;
int main()
{
	int arr[5];
    cout<<"Input array of 5 elements : (sorted elements if Binary search)"<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<"Input element"<<i+1<<endl;
		cin>>arr[i];
	}
	int ch,find;
	cout<<"1.LINEAR SEARCH 2.BINARY SEARCH \nENTER CHOICE : ";
	cin>>ch;
	cout<<"Enter element to be found : "<<endl;
	cin>>find;
	if(ch==1)
    {
    	int found=0;
    	for(int i=0;i<5;i++)
    	{
    		if(arr[i]==find)
    		{
    			cout<<"Found at : "<<i;
    			found=1;
    			break;
			}
		}
		if(found==0) cout<<"Not found";
	}
	else if(ch==2)
	{
		int low = 0, high = 4 , found=0;
		
		while(low<=high)
		{
			int mid = (low+high)/2;
			if(arr[mid]==find) 
			{
				cout<<"Found at : "<<mid;
				found = 1;
				break;
			}
			else if(arr[mid]>find)
				high = mid - 1;
			else
				low = mid + 1;
		}
		if(found==0) cout<<"Not found";
	}
}
