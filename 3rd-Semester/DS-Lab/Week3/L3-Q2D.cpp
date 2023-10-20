#include<iostream>
using namespace std;
int main()
{
    char s1[100],s2[100],s3[100];
    cout<<"Enter the string:"<<endl;
    gets(s1);
    cout<<"Enter the substring to be deleted:"<<endl;
    gets(s2);
    int i=0,j=0,k=0,n=0,l2,flag;
       for(i=0;s2[i]!='\0';i++)
    {
    	l2++;
	}
	i=0;
    for(i=0;s1[i]!='\0';i++)
    {
    	k=i;
    	while (s1[i]==s2[j])
    	{
    		i++;
    		j++;
    		if(j==l2)
    		{
    			flag=1;
    			break;
			}
		}
		j=0;
		if(flag==0)
			i=k;
		else
			flag=0;
		s3[n++]=s1[i];
	}
	s3[n]='\0';
	cout<<"The string after deleting substring is : ";
	puts(s3);
	return 0;
}

