#include<iostream>
#include<stdio.h>
using namespace std;
struct poly{
	int coeff,exp;
};
int main()
{
	int n1,n2,i,j;
	cout<<"Enter the number of terms in polynomial 1:";
	cin>>n1;
	poly p1[n1];
	cout<<"Enter the details for polynomial 1:"<<endl;
	p1[0].coeff=n1;
	for(i=1;i<=n1;i++)
	{
		cout<<"Coefficient:";
		cin>>p1[i].coeff;
		cout<<"Exponent:";
		cin>>p1[i].exp;
	}
	cout<<"Enter the number of terms in polynomial 2:";
	cin>>n2;
	poly p2[n2];
	cout<<"Enter the details for polynomial 2:"<<endl;
	p2[0].coeff=n2;
	for(i=1;i<=n2;i++)
	{
		cout<<"Coefficient:";
		cin>>p2[i].coeff;
		cout<<"Exponent:";
		cin>>p2[i].exp;
	}
	cout<<"Displaying polynomials:\n";
	cout<<"Polynomial 1:";
	for(i=1;i<=n1;i++)
	{
		if(p1[i].exp!=0)
			cout<<p1[i].coeff<<"x^"<<p1[i].exp<<"+";
		else
			cout<<p1[i].coeff;
	}
	cout<<"\nPolynomial 2:";
	for(i=1;i<=n2;i++)
	{
		if(p2[i].exp!=0)
			cout<<p2[i].coeff<<"x^"<<p2[i].exp<<"+";
		else
			cout<<p2[i].coeff;
	}
	cout<<"\nAddition of both the polynomials:";
	poly p3[n1];
	int n3=0;
	i=1,j=1;
	while(i<=n1 && j<=n2)
	{
		if(p1[i].exp==p2[j].exp)
		{
		
			int sum=p1[i].coeff+p2[j].coeff;
			if(sum!=0)
			{
				n3++;
				p3[n3].exp=p1[i].exp;
				p3[n3].coeff=p1[i].coeff+p2[j].coeff;
				
			}	i++;
				j++;	
		}
			else if(p1[i].exp>p2[j].exp)
			{
				n3++;
				p3[n3].coeff=p1[i].coeff;
				p3[n3].exp=p1[i].exp;
				i++;
			}
		else 
		{
			n3++;
			p3[n3].coeff=p2[j].coeff;
			p3[n3].exp=p2[j].exp;
			j++;	
		}

	}
	while(i<=n1)
	{
		n3++;
		p3[n3].coeff=p1[i].coeff;
		p3[n3].exp=p1[i].exp;
		i++;
	}
	while(j<=n2)
	{
		n3++;
		p3[n3].coeff=p2[j].coeff;
		p3[n3].exp=p2[j].exp;
		j++;
	}
	p3[0].coeff=n3;
	for(i=1;i<=n3;i++)
	{
		if(p3[i].exp!=0)
			cout<<p3[i].coeff<<"x^"<<p3[i].exp<<"+";
		else
			cout<<p3[i].coeff;
	}
	return 0;
}
