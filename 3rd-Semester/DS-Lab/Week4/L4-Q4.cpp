#include <iostream>
#include <math.h>
using namespace std ;

void toh (int num, string source, string dest, string auxiliary ){
	if (num ==1){
		cout<< "Move from " << source << " to " << dest << endl;
		return ;
	}
	else {
		toh (num-1 , source , auxiliary, dest);
		cout<< "Move from " << source << " to " << dest <<endl ; 
		toh (num-1 , auxiliary ,dest , source );
	}
}
int main(){
	int n ;
	cout<<"Enter the number of discs :" ;
	cin >> n;
	cout << "Total number of moves is " << pow(2,n)-1 <<endl ;
	cout <<"Moves are : " <<endl ;
	toh (n, "s", "d","a");
	return 0 ;

