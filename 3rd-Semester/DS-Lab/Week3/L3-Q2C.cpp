#include <iostream>
using namespace std;
int main()
{
    int i=0,flag=0;
    char str1[100],str2[100];
    cout<<"enter first string:"<<endl;
    cin>>str1;
    cout<<"enter second string:"<<endl;
    cin>>str2;
    while(str1[i]!='\0' || str2[i]!='\0')
    {
    	if(str1[i]!=str2[i])
    	{
		flag=1;
		break;
		}
		i++;
	}
	if(flag==0)
	{
		cout<<"The strings are equal.";
	}
	else
	cout<<"The strings are not equal."<<endl;
	return 0;
}

