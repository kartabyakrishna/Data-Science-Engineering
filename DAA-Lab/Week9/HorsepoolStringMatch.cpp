#include <iostream>
#include <cstring>
using namespace std;

void shift_table(char* pattern, int m, int* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i] = m;
    }
    for (int j = 0; j < m - 1; j++) {
        table[pattern[j]] = m - 1 - j;
    }
}

int horspool_matching(char* pattern, int m, char* text, int n) {
    int table[256];
    shift_table(pattern, m, table, 256);
    int i = m - 1;
    while (i <= n - 1) {
        int k = 0;
        while (k <= m - 1 && pattern[m - 1 - k] == text[i - k]) {
            k++;
        }
        if (k == m) {
            return i - m + 1;
        } else {
            i += table[text[i]];
        }
    }
    return -1;
}

int main() {
    char text[] = "Hello World";
    char pattern[] = "World";
    int n = strlen(text);
    int m = strlen(pattern);
    int result = horspool_matching(pattern, m, text, n);
    if (result != -1) {
        cout << "Pattern found at index " << result << endl;
    } else {
        cout << "Pattern not found" << endl;
    }
    return 0;
}

