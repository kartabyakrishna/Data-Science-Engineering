
#include <iostream>
using namespace std;

int gcd(int a,int b) {
  int R;
  while ((a % b) > 0)  {
    R = a % b;
    a = b ;
    b = R ;
  }
  return b;
}

int main(){
	int a , b;
	cout<<"enter the two numbers :"<< endl;
	cin >> a>> b ;
	cout<< "gcd of "<< a << " "<< b  <<"is " << gcd(a,b);

	return 0;
}
