#include <iostream>
using namespace std;

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	} else if (a == 0) {
		return b;
	} else {
		return gcd(b, a % b);
	}
}

int main() {
	int a, b;
	
	cout<< "Enter Num1, a : \n" ;
	cin >> a ;
	cout<< "Enter Num2, b : \n" ;
	cin >> b ;
	cout << "The GCD of " << a <<" & " << b << " is "<< gcd(a, b);
	
	return 0;
}
