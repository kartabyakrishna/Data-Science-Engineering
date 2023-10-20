#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
class EMPLOYEE{
    int Employee_Number ;
    char Employee_Name[30] ;
    int Basic;
    int DA;
    int IT;
    int Net_Salary;
    int Gross_Salary;
    
    public:
    readData(){
        cout << "Enter Employee No : ";
        cin >> Employee_Number ;
        cout <<"\nEmployee Name : ";
        cin >> Employee_Name ;
        cout <<"\nEnter Your Basic Amount: ";
        cin >> Basic ;
        
    }
GrossSalary(){
	DA = 0.12 * Basic ;
	Gross_Salary = Basic + DA;
}
NetSalary(){
	IT = (0.18*Gross_Salary);
	Net_Salary = Gross_Salary - IT ;
	
}
display(){
	cout << "\n Gross Salary = "<<Gross_Salary ;
	cout << "\n Net Salary = "<< Net_Salary ;
	cout << "\n" ;
}
};
int main (){
	int n ;
	cout << "\n Enter Number of Employees :";
	cin >> n ;
	int i ;
	EMPLOYEE e[n] ;
	for (i=0 ;i<n ; i++){
		e[i].readData();
		e[i].GrossSalary();
		e[i].NetSalary();
		e[i].display();
	}
return 0 ;
}
