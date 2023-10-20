#include <iostream>
using namespace std;

int main() {
	char str[50];
	
	cout << "Enter the string\n";
	gets(str);
	
	int count = 0;
	while(str[count] != '\0') {
		count++;
	}
	
	cout << count;
	
	return 0;
}
