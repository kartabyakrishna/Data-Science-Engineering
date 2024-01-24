
### 1) Reverse Digits of an Integer Array
```c
#include <stdio.h>

void reverseDigits(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        int num = arr[i];
        int reversed = 0;
        
        while (num > 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }
        
        arr[i] = reversed;
    }
}

int main() {
    int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Reverse the digits
    reverseDigits(arr, size);

    // Display the reversed array
    printf("Output array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

### 2) Calculator Simulation
```c
#include <stdio.h>

int main() {
    double A, B;

    // Input values
    printf("Enter value for A: ");
    scanf("%lf", &A);
    printf("Enter value for B: ");
    scanf("%lf", &B);

    // Perform operations
    printf("A + B = %.2f\n", A + B);
    printf("A - B = %.2f\n", A - B);
    printf("A * B = %.2f\n", A * B);

    // Check for division by zero
    if (B != 0) {
        printf("A / B = %.2f\n", A / B);
    } else {
        printf("Cannot divide by zero.\n");
    }

    return 0;
}
```

### 3) Toggle Characters in a String
```c
#include <stdio.h>

void toggleCharacters(char str[]) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A');
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        }
    }
}

int main() {
    char str[] = "HeLLo";

    // Toggle characters
    toggleCharacters(str);

    // Display the result
    printf("Toggled string: %s\n", str);

    return 0;
}
```

### 4) Pattern Generation from Input Word
```c
#include <stdio.h>

void printPattern(char word[], int length) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < i; ++j) {
            printf("%c", word[i]);
        }
    }
    printf("\n");
}

int main() {
    char word[20];
    
    // Input word
    printf("Enter a word: ");
    scanf("%s", word);

    // Display the pattern
    printPattern(word, strlen(word));

    return 0;
}
```
Certainly! Here are the C programs for the scenarios you provided:

### 5) Concatenate Alternate Characters from Two Strings
```c
#include <stdio.h>

void alternateConcat(char s1[], char s2[], int length) {
    char result[2 * length + 1]; // +1 for the null terminator

    for (int i = 0; i < length; ++i) {
        result[2 * i] = s1[i];
        result[2 * i + 1] = s2[i];
    }

    result[2 * length] = '\0';

    printf("Resultant String: %s\n", result);
}

int main() {
    char s1[] = "string";
    char s2[] = "length";
    int length = strlen(s1);

    // Concatenate alternate characters
    alternateConcat(s1, s2, length);

    return 0;
}
```

### 6) Matrix-Vector Product
```c
#include <stdio.h>

#define SIZE 3

void matrixVectorProduct(int matrix[SIZE][SIZE], int vector[SIZE], int result[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        result[i] = 0;
        for (int j = 0; j < SIZE; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int matrix[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int vector[SIZE] = {1, 2, 3};
    int result[SIZE];

    // Perform matrix-vector product
    matrixVectorProduct(matrix, vector, result);

    // Display the result
    printf("Resultant Vector: ");
    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
```

### 7) Matrix Operations with Diagonal Elements and Row Values
```c
#include <stdio.h>

#define SIZE 5

void processMatrix(int A[SIZE][SIZE], int B[SIZE][SIZE]) {
    // Set diagonal elements of B to 0
    for (int i = 0; i < SIZE; ++i) {
        B[i][i] = 0;
    }

    // Replace elements in B based on A values
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (j < i) {
                // Below diagonal, replace with maximum of the row
                int maxVal = A[i][0];
                for (int k = 1; k < SIZE; ++k) {
                    if (A[i][k] > maxVal) {
                        maxVal = A[i][k];
                    }
                }
                B[i][j] = maxVal;
            } else if (j > i) {
                // Above diagonal, replace with minimum of the row
                int minVal = A[i][0];
                for (int k = 1; k < SIZE; ++k) {
                    if (A[i][k] < minVal) {
                        minVal = A[i][k];
                    }
                }
                B[i][j] = minVal;
            }
        }
    }
}

void displayMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[SIZE][SIZE] = {{1, 2, 3, 4, 5},
                         {5, 4, 3, 2, 4},
                         {10, 3, 13, 14, 15},
                         {11, 2, 11, 33, 44},
                         {1, 12, 5, 4, 6}};

    int B[SIZE][SIZE];

    // Process the matrix
    processMatrix(A, B);

    // Display the resultant matrix B
    printf("B Matrix:\n");
    displayMatrix(B);

    return 0;
}
```

### 8) Matrix Operations - 1's Complement and D Matrix
```c
#include <stdio.h>

#define SIZE 4

void processMatrix(int A[SIZE][SIZE], int B[SIZE][SIZE], int D[SIZE][SIZE]) {
    // Replace non-border elements of B with 1's complement
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            B[i][j] = 1 - A[i][j];
        }
    }

    // Copy elements of A to D
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            D[i][j] = A[i][j];
        }
    }
}

void displayMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[SIZE][SIZE] = {{1, 2, 3, 4},
                         {6, 5, 8, 3},
                         {2, 4, 10, 1},
                         {9, 1, 2, 5}};

    int B[SIZE][SIZE];
    int D[SIZE][SIZE];

    // Process the matrix
    processMatrix(A, B, D);

    // Display the resultant matrix B
    printf("B Matrix:\n");
    displayMatrix(B);

    // Display the matrix D
    printf("D Matrix:\n");
    displayMatrix(D);

    return 0;
}
```

### 9) Write a C program that reads a character type matrix and integer type matrix B of size MxN. It produces and output string STR such that, every character of A is repeated r times (where r is the integer value in matrix B which is having the same index as that of the character taken in A).
| A |    |    |
|---|----|----|
| p | C  | a  |
| e | X  | a  |
| P | a  | M  |

| B |    |    |
|---|----|----|
| 1 | 2  | 4  |
| 2 | 3  | 2  |
| 4 | 3  | 2  |

Output string STR: `pCCaaaaPPPeeXXXXaaaMM`

```c
#include <stdio.h>

#define SIZE 2

void generateString(char A[SIZE][SIZE], int B[SIZE][SIZE], char STR[], int strLength) {
    int strIndex = 0;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < B[i][j]; ++k) {
                STR[strIndex++] = A[i][j];
            }
        }
    }

    STR[strIndex] = '\0';
}

int main() {
    char A[SIZE][SIZE] = {{'p', 'C'}, {'a', 'P'}};
    int B[SIZE][SIZE] = {{1, 2}, {4, 3}};
    char STR[20];



    // Generate the output string
    generateString(A, B, STR, 20);

    // Display the resultant string
    printf("Output string STR: %s\n", STR);

    return 0;
}
```
