
#include <iostream>
using namespace std;
int stringMatch(string t, string p) {
	int n = t.length();
	int m = p.length();
	for (int i = 0; i <= n - m; i++)
	{
	 	 int j;
	 	for (j = 0; j < m; j++){
			if (t[i + j] != p[j]) {
		  		break;
			}
		}
		if (j == m) {
			return i;
		}
	}
		return -1;
	}

int main() {
	char t[30],p[30];
	cout<<"Enter the text:";
	gets(t);
	cout<<"Enter the pattern:";
	gets(p);
	int result = stringMatch(t, p);
	if (result == -1) {
		cout<< "Pattern not found.";
	}
	else {
		cout<< "Pattern found at index " << result << "." ;
	}
	return 0;
}
