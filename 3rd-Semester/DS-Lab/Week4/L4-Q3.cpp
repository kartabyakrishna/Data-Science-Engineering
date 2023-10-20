#include <iostream>
using namespace std;

int fibo(int num) {
	if (num == 0) {
		return 0;
	} else if (num == 1) {
		return 1;
	} else {
		return fibo(num-1)+fibo(num-2);
	}
}

int main() {
	int num;
	
	cout << "Enter the term\n";
	cin >> num;
	
	cout << "The fibonacci series is:\n";
	for (int i = 0; i <= num; i++) {
		cout << fibo(i) << " ";
	}
	
	return 0;
}
