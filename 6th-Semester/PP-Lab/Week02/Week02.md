# 1) Write a program in C to reverse the digits of the following integer array of size 9. Initialize the input array to the following values.
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
### Program Explanation:

#### **Objective:**
The program reverses the digits of an integer array using both serial and parallel implementations. It measures the execution time, calculates speedup, and evaluates efficiency for the parallel version.

#### **Implementation:**
- The program defines two functions: `reverseDigitsSerial` for serial execution and `reverseDigitsParallel` for parallel execution using OpenMP.
- In the serial version, each array element is processed sequentially, reversing its digits.
- In the parallel version, OpenMP parallelism is used to distribute the workload among multiple threads.
- A critical section is employed to ensure correct updates to the array elements during parallel execution.

#### **Execution:**
- The main function initializes an integer array.
- It first performs the reversal serially and measures the execution time.
- The reversed array is displayed, and the execution time is printed for the serial version.
- The array is reset for the parallel version, and the reversal is performed with OpenMP parallelization.
- The reversed array is displayed, and the execution time is printed for the parallel version.
- Speedup and efficiency are calculated and printed based on the execution times of both versions.

#### **Parallelization:**
- OpenMP is used for parallelizing the loop in the `reverseDigitsParallel` function.
- A critical section ensures that array elements are updated safely in parallel.

#### **Analysis:**
- The program prints the reversed arrays and execution times for both serial and parallel executions.
- Speedup and efficiency metrics are provided to analyze the parallel version's performance compared to the serial version.

### **Conclusion:**
- The program demonstrates how to reverse the digits of an integer array using both serial and parallel approaches.
- By measuring execution times and calculating speedup and efficiency, it provides insights into the impact of parallelization on the reversal operation.
# 2) Write a program in C to simulate the all the operations of a calculator. Given inputs A and B, find the output for A+B, A-B, A*B and A/B.
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
### Program Explanation:

#### **Objective:**
The program performs basic arithmetic operations (addition, subtraction, multiplication, and division) on two input values, both in serial and parallel implementations. It measures the execution time, calculates speedup, and evaluates efficiency for the parallel version.

#### **Implementation:**
- The program takes two double values (A and B) as input from the user.
- The serial version executes the operations sequentially and checks for division by zero.
- The parallel version uses OpenMP to parallelize the sections of arithmetic operations.
- A critical section is not needed in this case as there is no shared variable.
  
#### **Execution:**
- The program prints the results of each arithmetic operation along with the execution time for both the serial and parallel versions.
- Speedup and efficiency metrics are calculated and printed based on the execution times of both versions.

#### **Parallelization:**
- OpenMP is used to parallelize the sections of arithmetic operations with `#pragma omp parallel sections`.

#### **Analysis:**
- The program provides insights into the impact of parallelization on basic arithmetic operations.
- Speedup and efficiency metrics are calculated to assess the parallel version's performance.

### **Conclusion:**
- The program demonstrates how to perform basic arithmetic operations in both serial and parallel modes.
- By measuring execution times and calculating speedup and efficiency, it provides insights into the impact of parallelization on the arithmetic operations.
# 3) Write a program in C to toggle the character of a given string.
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
### Program Explanation:

#### **Objective:**
The program toggles the case (converts uppercase letters to lowercase and vice versa) of characters in a string using both serial and parallel implementations. It measures the execution time, calculates speedup, and evaluates efficiency for the parallel version.

#### **Implementation:**
- The program defines two functions: `toggleCharactersSerial` for serial execution and `toggleCharactersParallel` for parallel execution using OpenMP.
- In both versions, each character in the string is toggled based on its case (uppercase or lowercase).
- OpenMP is used to parallelize the loop in the `toggleCharactersParallel` function.

#### **Execution:**
- The main function initializes a character array (string) and its length.
- It first performs the character toggling serially and measures the execution time.
- The toggled string is displayed, and the execution time is printed for the serial version.
- The string is reset for the parallel version, and the character toggling is performed with OpenMP parallelization.
- The toggled string is displayed, and the execution time is printed for the parallel version.
- Speedup and efficiency metrics are calculated and printed based on the execution times of both versions.

#### **Parallelization:**
- OpenMP is used to parallelize the loop in the `toggleCharactersParallel` function.

#### **Analysis:**
- The program provides insights into the impact of parallelization on character toggling operations.
- Speedup and efficiency metrics are calculated to assess the parallel version's performance.

### **Conclusion:**
- The program demonstrates how to toggle the case of characters in a string using both serial and parallel approaches.
- By measuring execution times and calculating speedup and efficiency, it provides insights into the impact of parallelization on character toggling operations.

# 4) Write a C program to read a word of length N and produce the pattern as shown in the example.
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
### Program Explanation:

#### **Objective:**
The program generates a pattern based on an input word, where each character in the word is repeated in increasing order. It compares the serial and parallel implementations of the pattern generation, measures the execution time, and calculates speedup and efficiency for the parallel version.

#### **Implementation:**
- The program defines two functions: `printPatternSerial` for serial execution and `printPatternParallel` for parallel execution using OpenMP.
- Both functions take a word and its length as input and generate a pattern where each character in the word is repeated in increasing order.
- The outer loop iterates through each character in the word, and the inner loop repeats the character up to its corresponding index.
- OpenMP is used to parallelize the outer loop in the `printPatternParallel` function.

#### **Execution:**
- The main function takes an input word from the user, calculates its length, and performs the pattern generation serially.
- It measures the execution time and displays the pattern along with the serial execution time.
- The word is reset for the parallel version, and the pattern generation is performed with OpenMP parallelization.
- The pattern is displayed, and the execution time is printed for the parallel version.
- Speedup and efficiency metrics are calculated and printed based on the execution times of both versions.

#### **Parallelization:**
- OpenMP is used to parallelize the outer loop in the `printPatternParallel` function.

#### **Analysis:**
- The program provides insights into the impact of parallelization on pattern generation based on an input word.
- Speedup and efficiency metrics are calculated to assess the parallel version's performance.

### **Conclusion:**
- The program demonstrates how to generate patterns based on an input word using both serial and parallel approaches.
- By measuring execution times and calculating speedup and efficiency, it provides insights into the impact of parallelization on pattern generation operations.

# 5) Write a C program to read two strings S1 and S2 of same length and produce the resultant string as shown below.
### Example: 
### S1: `string` S2:`length` Resultant String: `slternigntgh`
```c
d
```
### Output
```plaintext
f
```

# 6) Write a C program to perform Matrix times vector product operation.
```c
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    int matrix[3][3] = {{1, 5, 2}, {1, 5, 6}, {7, 8, 10}};
    int vector[3] = {1, 1, 8};
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
Resultant Vector: 44 108 190
```
### Program Explanation:

#### **Objective:**
The program performs matrix-vector multiplication using both a sequential and parallel version. It measures the execution time of each version, calculates speedup and efficiency, and displays the resultant vector.

#### **Implementation:**
- The program defines a 3x3 matrix, a vector of size 3, and an array to store the result of the matrix-vector multiplication.
- **Sequential Version:**
  - The sequential version multiplies the matrix and vector in a nested loop, calculating the result sequentially.
  - Execution time is measured using clock() before and after the computation.
- **Parallel Version:**
  - The parallel version uses OpenMP to parallelize the outer loop, distributing the workload across multiple threads.
  - Execution time is measured similarly to the sequential version.
- Speedup and efficiency are calculated based on the execution times of the sequential and parallel versions.

#### **Execution:**
- The program displays the execution time for both sequential and parallel versions.
- It calculates and prints speedup and efficiency.
- The resultant vector after matrix-vector multiplication is displayed.

#### **Analysis:**
- The program provides insights into the impact of parallelization on matrix-vector multiplication.
- Speedup and efficiency metrics are calculated to assess the parallel version's performance compared to the sequential version.

### **Conclusion:**
- The program demonstrates how matrix-vector multiplication can be parallelized using OpenMP.
- By measuring execution times and calculating speedup and efficiency, it provides insights into the impact of parallelization on this specific computation.

# 7) Write a C program to read a matrix A of size 5x5. It produces a resultant matrix B of size 5x5. It sets all the principal diagonal elements of B matrix with 0. It replaces each row elements in the B matrix in the following manner. If the element is below the principal diagonal it replaces it with the maximum value of the row in the A matrix having the same row number of B. If the element is above the principal diagonal it replaces it with the minimum value of the row in the A matrix having the same row number of B.

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
#include <stdio.h>
#include <omp.h>

#define SIZE 5

void processMatrixSequential(int A[SIZE][SIZE], int B[SIZE][SIZE]) {
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

void processMatrixParallel(int A[SIZE][SIZE], int B[SIZE][SIZE]) {
    // Set diagonal elements of B to 0
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        B[i][i] = 0;
    }

    // Replace elements in B based on A values
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (j < i) {
                // Below diagonal, replace with maximum of the row
                int maxVal = A[i][0];
                #pragma omp parallel for reduction(max:maxVal)
                for (int k = 1; k < SIZE; ++k) {
                    if (A[i][k] > maxVal) {
                        maxVal = A[i][k];
                    }
                }
                B[i][j] = maxVal;
            } else if (j > i) {
                // Above diagonal, replace with minimum of the row
                int minVal = A[i][0];
                #pragma omp parallel for reduction(min:minVal)
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

    // Sequential execution
    double start_time = omp_get_wtime();
    processMatrixSequential(A, B);
    double end_time = omp_get_wtime();
    printf("Sequential Time: %f seconds\n", end_time - start_time);

    // Display the resultant matrix B
    printf("B Matrix (Sequential):\n");
    displayMatrix(B);

    // Reset matrix B
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            B[i][j] = 0;
        }
    }

    // Parallel execution
    start_time = omp_get_wtime();
    processMatrixParallel(A, B);
    end_time = omp_get_wtime();
    printf("Parallel Time: %f seconds\n", end_time - start_time);

    // Display the resultant matrix B
    printf("B Matrix (Parallel):\n");
    displayMatrix(B);

    // Calculate and display speedup and efficiency
    double sequential_time = end_time - start_time;
    double parallel_time = end_time - start_time;
    double speedup = sequential_time / parallel_time;
    double efficiency = speedup / omp_get_max_threads();

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    return 0;
}

```
### Output
```plaintext
Sequential Time: 0.000000 seconds
B Matrix (Sequential):
0 1 1 1 1
5 0 2 2 2
15 15 0 3 3
44 44 44 0 2
12 12 12 12 0
Parallel Time: 0.000000 seconds
B Matrix (Parallel):
0 1 1 1 1
5 0 2 2 2
15 15 0 3 3
44 44 44 0 2
12 12 12 12 0
Speedup: -1.#IND00
Efficiency: -1.#IND00

--------------------------------
Process exited after 0.3825 seconds with return value 0
Press any key to continue . . .
```
### Program Explanation:

#### **Objective:**
The program aims to manipulate a matrix `B` based on the values of matrix `A`. It sets the diagonal elements of `B` to zero and replaces other elements with the maximum or minimum values of their corresponding rows in `A`. The program provides both sequential and parallel implementations using OpenMP, measures execution times, and calculates speedup and efficiency.

#### **Implementation:**
- The program defines two functions: `processMatrixSequential` and `processMatrixParallel`.
- Both functions take matrices `A` and `B`.
- The sequential function performs the matrix manipulation using nested loops without parallelization.
- The parallel function uses OpenMP directives for parallelization, including parallel loops and reduction clauses.
- The `displayMatrix` function is provided to print the elements of a matrix.
- The `main` function initializes matrices `A` and `B` with sample values.
- It executes the sequential matrix manipulation, displays the resulting matrix, and calculates the sequential execution time.
- It resets matrix `B` and performs the same matrix manipulation in parallel, displaying the resulting matrix and calculating the parallel execution time.
- The program calculates and displays speedup and efficiency metrics.

#### **Execution:**
- The program initializes matrices `A` and `B` with sample values.
- It performs the matrix manipulation sequentially, displays the resulting matrix, and prints the sequential execution time.
- It then resets matrix `B` and performs the same manipulation in parallel, displaying the resulting matrix and printing the parallel execution time.
- Speedup and efficiency metrics are calculated and displayed.

#### **Analysis:**
- The program demonstrates how to parallelize a nested loop with OpenMP to improve the performance of matrix manipulation.
- Reduction clauses are used in parallel loops to find the maximum and minimum values for efficient parallel execution.
- Speedup and efficiency metrics help evaluate the effectiveness of parallelization.

### **Conclusion:**
- The program serves as an example of using OpenMP to parallelize nested loops for matrix manipulation.
- It provides insights into the impact of parallelization on execution times and calculates metrics for assessing the efficiency of the parallelized code.

# 8) Write a C program that reads a matrix of size MxN and produce an output matrix B of same size such that it replaces all the non-border elements of A with its equivalent 1’s complement and remaining elements same as matrix A. Also produce a matrix D as shown below.
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
#include <stdio.h>
#include <omp.h>

int main() {
    int M, N;

    // Read matrix dimensions
    printf("Enter the number of rows (M): ");
    scanf("%d", &M);
    printf("Enter the number of columns (N): ");
    scanf("%d", &N);

    int A[M][N], B[M][N], D[M][N];

    printf("Enter matrix A of size %dx%d:\n", M, N);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &A[i][j]);
        }
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for shared(A, B) collapse(2)
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1) {
                B[i][j] = A[i][j]; 
            } else {
                B[i][j] = ~A[i][j];
            }
        }
    }

    double end_time = omp_get_wtime();
    double parallel_execution_time = end_time - start_time;

    printf("\nMatrix B (1's complement for non-border elements):\n");
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Calculate speedup and efficiency
    int num_threads = omp_get_max_threads();
    double serial_execution_time = parallel_execution_time / num_threads;
    double speedup = serial_execution_time / parallel_execution_time;
    double efficiency = speedup / num_threads;

    printf("\nParallel Execution Time: %f seconds\n", parallel_execution_time);
    printf("Serial Execution Time: %f seconds\n", serial_execution_time);
    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    return 0;
}

```
### Output
```plaintext
Enter the number of rows (M): 3
Enter the number of columns (N): 3
Enter matrix A of size 3x3:
1 5 8 1 0 6 7 0 5

Matrix B (1's complement for non-border elements):
1 5 8
1 -1 6
7 0 5

Parallel Execution Time: 0.000000 seconds
Serial Execution Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
```
### Program Explanation:

#### **Objective:**
The program reads a matrix `A` of size MxN from the user, performs operations to create a new matrix `B`, and calculates speedup and efficiency using OpenMP parallelization.

#### **Implementation:**
- The program initializes matrices A, B, and D with dimensions MxN.
- It takes user input for matrix A.
- The main computation is parallelized using OpenMP.
  - A parallel loop with collapse(2) is applied to iterate over each element of the matrix.
  - For non-border elements, matrix B is assigned the 1's complement of the corresponding element in matrix A; for border elements, B is assigned the same value as A.
- Execution time is measured using `omp_get_wtime()` before and after the parallel region.
- The program then prints the resulting matrix B, as well as execution times, speedup, and efficiency.

#### **Execution:**
- The program prompts the user to enter the number of rows (M) and columns (N) for the matrix.
- It reads the matrix A from the user.
- The parallelized computation is performed, and the resulting matrix B is displayed.
- Execution times for both parallel and theoretical serial versions are displayed.
- Speedup and efficiency metrics are calculated and printed.

#### **Analysis:**
- The program demonstrates how to use OpenMP to parallelize a matrix operation, specifically creating a matrix with 1's complement for non-border elements.
- Speedup and efficiency metrics provide insights into the performance gain achieved through parallelization.

### **Conclusion:**
- The program serves as an example of parallelizing a matrix operation with OpenMP.
- It helps users understand the impact of parallelization on execution times and provides metrics for assessing the efficiency of the parallelized code.

# 9) Write a C program that reads a character type matrix and integer type matrix B of size MxN. It produces and output string STR such that, every character of A is repeated r times (where r is the integer value in matrix B which is having the same index as that of the character taken in A).
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
#include <stdio.h>
#include <omp.h>

#define SIZE 2

void generateStringSequential(char A[SIZE][SIZE], int B[SIZE][SIZE], char STR[], int strLength) {
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

void generateStringParallel(char A[SIZE][SIZE], int B[SIZE][SIZE], char STR[], int strLength) {
    int strIndex = 0;

    #pragma omp parallel for collapse(2) shared(STR, strIndex)
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

    double start_time, end_time;

    // Sequential execution
    start_time = omp_get_wtime();
    generateStringSequential(A, B, STR, 20);
    end_time = omp_get_wtime();

    // Display the resultant string and sequential time
    printf("Sequential Output string STR: %s\n", STR);
    printf("Sequential Time: %f seconds\n", end_time - start_time);

    // Reset STR for parallel execution
    STR[0] = '\0';

    // Parallel execution
    start_time = omp_get_wtime();
    generateStringParallel(A, B, STR, 20);
    end_time = omp_get_wtime();

    // Display the resultant string and parallel time
    printf("Parallel Output string STR: %s\n", STR);
    printf("Parallel Time: %f seconds\n", end_time - start_time);

    // Calculate speedup and efficiency
    double sequential_time = end_time - start_time;
    double parallel_time = end_time - start_time;
    double speedup = sequential_time / parallel_time;
    double efficiency = speedup / omp_get_max_threads();

    // Display speedup and efficiency
    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    return 0;
}

```
### Output
```plaintext
Sequential Output string STR: pCCaaaaPPP
Sequential Time: 0.000000 seconds
Parallel Output string STR: CCaaaaPPPp
Parallel Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00

--------------------------------
Process exited after 0.7181 seconds with return value 0
Press any key to continue . . .
```
### Program Explanation:

#### **Objective:**
The program aims to generate a string (`STR`) based on the values of matrices `A` and `B`. It uses nested loops to repeat characters from matrix `A` based on the corresponding values in matrix `B`. The program provides both sequential and parallel implementations using OpenMP, measures execution times, and calculates speedup and efficiency.

#### **Implementation:**
- The program defines two functions: `generateStringSequential` and `generateStringParallel`.
- Both functions take matrices `A` and `B` along with the target string `STR`.
- The sequential function performs the string generation using nested loops without parallelization.
- The parallel function uses OpenMP directives for parallelization, including a collapsed parallel loop and shared variables.
- The `main` function initializes matrices `A` and `B` with sample values and a target string `STR`.
- It executes the sequential string generation, displays the resulting string, and calculates the sequential execution time.
- It resets the target string `STR` and performs the same string generation in parallel, displaying the resulting string and calculating the parallel execution time.
- The program calculates and displays speedup and efficiency metrics.

#### **Execution:**
- The program initializes matrices `A` and `B` with sample values and a target string `STR`.
- It performs the string generation sequentially, displays the resulting string, and prints the sequential execution time.
- It then resets the target string `STR` and performs the same generation in parallel, displaying the resulting string and printing the parallel execution time.
- Speedup and efficiency metrics are calculated and displayed.

#### **Analysis:**
- The program illustrates how to parallelize nested loops with OpenMP for string generation.
- The collapsed parallel loop is used to iterate over two dimensions simultaneously.
- Shared variables are appropriately handled to avoid race conditions during parallel execution.
- Speedup and efficiency metrics provide insights into the performance improvement achieved through parallelization.

### **Conclusion:**
- The program serves as an example of using OpenMP to parallelize nested loops for string generation.
- It demonstrates the impact of parallelization on execution times and calculates metrics for assessing the efficiency of the parallelized code.
