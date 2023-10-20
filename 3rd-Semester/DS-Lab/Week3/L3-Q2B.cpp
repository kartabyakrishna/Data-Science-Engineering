#include <iostream>
using namespace std;

int main() {
	char str[50];
	char other_str[50];
	
	cout << "Enter the first string\n";
	gets(str);
	cout << "Enter the second string\n";
	gets(other_str);
	
	int length = 0;
	while(str[length] != '\0') {
		length++;
	}

	int count = 0;
	for (int i = length + 1; other_str[count] != '\0'; i++) {
		str[i] = other_str[count];
		count++;	
	}

	for (int i = 0; i < (count + length + 1) ; i++) {
		cout << str[i];
	}
	
	return 0;
}
