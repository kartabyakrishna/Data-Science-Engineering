#include <iostream>
using namespace std;

int factorial(int num) {
	if (num == 1 || num == 0) {
		return 1;
	} else {
		return factorial(num - 1) * num;
	}
}

int main() {
	int num;
	
	cout << "Enter a number : \n";
	cin >> num;
	
	cout << "The factorial is of " << num << " is " <<factorial(num);
	
	return 0;
}
