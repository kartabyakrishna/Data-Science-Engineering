# NOT FINAL !!!!!!!!
### 1) Write a program in C to reverse the digits of the following integer array of size 9. Initialize the input array to the following values.
### Example : 
### Input array: `18, 523, 301, 1234, 2, 14, 108, 150, 1928`
### Output array: `81, 325, 103, 4321, 2, 41, 801, 51, 8291`
```c
#include <stdio.h>
#include <omp.h>

void reverseDigitsSerial(int arr[], int size) {
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

void reverseDigitsParallel(int arr[], int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        int num = arr[i];
        int reversed = 0;

        while (num > 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }

        #pragma omp critical
        arr[i] = reversed;
    }
}

int main() {
    int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Serial execution
    double start_serial = omp_get_wtime();
    reverseDigitsSerial(arr, size);
    double end_serial = omp_get_wtime();

    // Display the reversed array
    printf("Output array (Serial): ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Serial Execution Time: %f seconds\n", end_serial - start_serial);

    // Reset array for parallel version
    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }

    // Parallel execution
    double start_parallel = omp_get_wtime();
    reverseDigitsParallel(arr, size);
    double end_parallel = omp_get_wtime();

    // Display the reversed array
    printf("Output array (Parallel): ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Parallel Execution Time: %f seconds\n", end_parallel - start_parallel);

    printf("Speedup: %f\n", (end_serial - start_serial) / (end_parallel - start_parallel));
    printf("Efficiency: %f\n", ((end_serial - start_serial) / (end_parallel - start_parallel)) / omp_get_max_threads());

    return 0;
}
```
### Output
```plaintext
Output array (Serial): 81 325 103 4321 2 41 801 51 8291
Serial Execution Time: 0.000000 seconds
Output array (Parallel): 18 523 301 1234 2 14 108 15 1928
Parallel Execution Time: 0.001000 seconds
Speedup: 0.000000
Efficiency: 0.000000
```

### 2) Write a program in C to simulate the all the operations of a calculator. Given inputs A and B, find the output for A+B, A-B, A*B and A/B.
```c
#include <stdio.h>
#include <omp.h>

int main() {
    double A, B;

    // Input values
    printf("Enter value for A: ");
    scanf("%lf", &A);
    printf("Enter value for B: ");
    scanf("%lf", &B);

    // Serial execution
    double start_serial = omp_get_wtime();

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

    double end_serial = omp_get_wtime();
    printf("Serial Execution Time: %f seconds\n", end_serial - start_serial);

    // Reset values for parallel version
    double A_parallel, B_parallel;
    A_parallel = A;
    B_parallel = B;

    // Parallel execution
    double start_parallel = omp_get_wtime();

    // Perform operations in parallel
    #pragma omp parallel sections
    {
        #pragma omp section
        printf("A + B (Parallel) = %.2f\n", A_parallel + B_parallel);

        #pragma omp section
        printf("A - B (Parallel) = %.2f\n", A_parallel - B_parallel);

        #pragma omp section
        printf("A * B (Parallel) = %.2f\n", A_parallel * B_parallel);

        #pragma omp section
        {
            if (B_parallel != 0) {
                printf("A / B (Parallel) = %.2f\n", A_parallel / B_parallel);
            } else {
                printf("Cannot divide by zero in parallel.\n");
            }
        }
    }

    double end_parallel = omp_get_wtime();
    printf("Parallel Execution Time: %f seconds\n", end_parallel - start_parallel);

    printf("Speedup: %f\n", (end_serial - start_serial) / (end_parallel - start_parallel));
    printf("Efficiency: %f\n", ((end_serial - start_serial) / (end_parallel - start_parallel)) / omp_get_max_threads());

    return 0;
}
```
### Output
```plaintext
Enter value for A: 25
Enter value for B: 69
A + B = 94.00
A - B = -44.00
A * B = 1725.00
A / B = 0.36
Serial Execution Time: 0.000000 seconds
A + B (Parallel) = 94.00
A - B (Parallel) = -44.00
A * B (Parallel) = 1725.00
A / B (Parallel) = 0.36
Parallel Execution Time: 0.001000 seconds
Speedup: 0.000000
Efficiency: 0.000000
```

### 3) Write a program in C to toggle the character of a given string.
### Example: 
### suppose the string is `HeLLo`, then the output should be `hEllO`.
```c
#include <stdio.h>
#include <omp.h>

void toggleCharactersSerial(char str[], int length) {
    for (int i = 0; i < length; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A');
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        }
    }
}

void toggleCharactersParallel(char str[], int length) {
    #pragma omp parallel for
    for (int i = 0; i < length; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A');
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        }
    }
}

int main() {
    char str[] = "HeLLo";
    int length = 5;  // Length of the input string

    // Serial execution
    double start_serial = omp_get_wtime();
    toggleCharactersSerial(str, length);
    double end_serial = omp_get_wtime();

    // Display the result
    printf("Toggled string (Serial): %s\n", str);
    printf("Serial Execution Time: %f seconds\n", end_serial - start_serial);

    // Reset string for parallel version
    char strParallel[] = "HeLLo";

    // Parallel execution
    double start_parallel = omp_get_wtime();
    toggleCharactersParallel(strParallel, length);
    double end_parallel = omp_get_wtime();

    // Display the result
    printf("Toggled string (Parallel): %s\n", strParallel);
    printf("Parallel Execution Time: %f seconds\n", end_parallel - start_parallel);

    // Calculate speedup and efficiency
    double speedup = (end_serial - start_serial) / (end_parallel - start_parallel);
    double efficiency = speedup / omp_get_max_threads();

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    return 0;
}
```
### Output
```plaintext
Toggled string (Serial): hEllO
Serial Execution Time: 0.000000 seconds
Toggled string (Parallel): hEllO
Parallel Execution Time: 0.001000 seconds
Speedup: 0.000000
Efficiency: 0.000000
```

### 4) Write a C program to read a word of length N and produce the pattern as shown in the example.
### Example: 
### Input: `PCBD` Output: `PCCBBBDDDD`
```c
#include <stdio.h>
#include <string.h>
#include <omp.h>

void printPatternSerial(char word[], int length) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j <= i; ++j) {
            printf("%c", word[i]);
        }
    }
    printf("\n");
}

void printPatternParallel(char word[], int length) {
    #pragma omp parallel for
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j <= i; ++j) {
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

    int length = strlen(word);

    // Serial execution
    double start_serial = omp_get_wtime();
    printPatternSerial(word, length);
    double end_serial = omp_get_wtime();

    // Display the result
    printf("Serial Execution Time: %f seconds\n", end_serial - start_serial);

    // Reset word for parallel version
    char wordParallel[20];
    strcpy(wordParallel, word);

    // Parallel execution
    double start_parallel = omp_get_wtime();
    printPatternParallel(wordParallel, length);
    double end_parallel = omp_get_wtime();

    // Display the result
    printf("Parallel Execution Time: %f seconds\n", end_parallel - start_parallel);

    // Calculate speedup and efficiency
    double speedup = (end_serial - start_serial) / (end_parallel - start_parallel);
    double efficiency = speedup / omp_get_max_threads();

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    return 0;
}

```
### Output
```plaintext
Enter a word: PCBD
PCCBBBDDDD
Serial Execution Time: 0.000000 seconds
CCBBBPDDDD
Parallel Execution Time: 0.001000 seconds
Speedup: 0.000000
Efficiency: 0.000000
```

### 5) Write a C program to read two strings S1 and S2 of same length and produce the resultant string as shown below.
### Example: 
### S1: `string` S2:`length` Resultant String: `slternigntgh`
```c
d
```
### Output
```plaintext
f
```

### 6) Write a C program to perform Matrix times vector product operation.
```c
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    int matrix[3][3] = {{5, 2, 7}, {7, 6, 8}, {8, 8, 1}};
    int vector[3] = {1, 1, 3};
    int result[3] = {0};

    // Sequential version
    clock_t start_time_seq = clock();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            result[i] += matrix[i][j] * vector[j];
    }

    clock_t end_time_seq = clock();
    double execution_time_seq = ((double)(end_time_seq - start_time_seq)) / CLOCKS_PER_SEC;

    printf("Sequential Execution Time: %f seconds\n", execution_time_seq);

    // Parallel version
    clock_t start_time_par = clock();

    #pragma omp parallel for
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            result[i] += matrix[i][j] * vector[j];
    }

    clock_t end_time_par = clock();
    double execution_time_par = ((double)(end_time_par - start_time_par)) / CLOCKS_PER_SEC;

    printf("Parallel Execution Time: %f seconds\n", execution_time_par);

    // Speedup and Efficiency calculations
    double speedup = execution_time_seq / execution_time_par;
    double efficiency = speedup / omp_get_max_threads();  // Number of threads

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    // Print Resultant Vector
    printf("Resultant Vector: ");
    for (int i = 0; i < 3; ++i)
        printf("%d ", result[i]);

    return 0;
}

```
### Output
```plaintext
Sequential Execution Time: 0.000000 seconds
Parallel Execution Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
Resultant Vector: 56 74 38
```

### 7) Write a C program to read a matrix A of size 5x5. It produces a resultant matrix B of size 5x5. It sets all the principal diagonal elements of B matrix with 0. It replaces each row elements in the B matrix in the following manner. If the element is below the principal diagonal it replaces it with the maximum value of the row in the A matrix having the same row number of B. If the element is above the principal diagonal it replaces it with the minimum value of the row in the A matrix having the same row number of B.

### Example: 

| **A** |   |   |   |   |
|-------|---|---|---|---|
| 1 | 2 | 3 | 4 | 5 |
| 5 | 4 | 3 | 2 | 4 |
|10 | 3 | 13| 14| 15|
|11 | 2 | 11| 33| 44|
| 1 |12 | 5 | 4 | 6 |

| **B** |   |   |   |   |
|-------|---|---|---|---|
| 0 | 1 | 1 | 1 | 1 |
|5| 0 | 2 | 2 | 2 |
|15|15 | 0 | 3 | 3 |
|44 |44 |44 | 0 | 2 |
| 12 |12 |12 |12 | 0 |

```c
d
```
### Output
```plaintext
f
```

### 8) Write a C program that reads a matrix of size MxN and produce an output matrix B of same size such that it replaces all the non-border elements of A with its equivalent 1’s complement and remaining elements same as matrix A. Also produce a matrix D as shown below.
| **A** |     |     |     |     
|-------|-----|-----|-----|
|   1   |  2  |  3  |  4  |     
|   6   |  5  |  8  |  3  |     
|   2   |  4  |  10 |  1  |     
|   9   |  1  |  2  |  5  |     

| **B** |    |      |      |    
|-------|----|------|------|
|   1   |  2 |   3  |   4  |     
|   6   | **10** |**111**|   3  |     
|   2   | **11** |**101**|   1  |     
|   9   |  1 |   2  |   5  |     

| **D** |     |     |     | 
|-------|-----|-----|-----|
|   1   |  2  |  3  |  4  |     
|   6   |  **2**  |  **7**  |  3  |     
|   2   |  **3**  |  **5**  |  1  |     
|   9   |  1  |  2  |  5  |


```c
d
```
### Output
```plaintext
f
```

### 9) Write a C program that reads a character type matrix and integer type matrix B of size MxN. It produces and output string STR such that, every character of A is repeated r times (where r is the integer value in matrix B which is having the same index as that of the character taken in A).
### Example: 
| **A** |    |    |
|---|----|----|
| p | C  | a  |
| e | X  | a  |
| P | a  | M  |

| **B** |    |    |
|---|----|----|
| 1 | 2  | 4  |
| 2 | 3  | 2  |
| 4 | 3  | 2  |


### Output string STR: `pCCaaaaPPPeeXXXXaaaMM`

```c
d
```
### Output
```plaintext
f
```
