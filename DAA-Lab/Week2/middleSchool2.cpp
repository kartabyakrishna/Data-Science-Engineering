#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
vector<int> primeFactors(int n) {
    vector<int> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }
    if (n > 2) {
        factors.push_back(n);
    }
    return factors;
}
int gcd(int a, int b) {
    vector<int> factorsA = primeFactors(a);
    vector<int> factorsB = primeFactors(b);
    int i = 0, j = 0, result = 1;
    while (i < factorsA.size() && j < factorsB.size()) {
        if (factorsA[i] == factorsB[j]) {
            result *= factorsA[i];
            i++;
            j++;
        } else if (factorsA[i] < factorsB[j]) {
            i++;
        } else {
            j++;
        }
    }
    return result;
}
int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    int result = gcd(a, b);
    cout << "The GCD of " << a << " and " << b << " is " << result << endl;
    return 0;
}
