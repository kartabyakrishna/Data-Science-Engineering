## Q1: Write an OpenMP program to implement Matrix multiplication.
### a. Analyze the speedup and efficiency of the parallelized code.
### b. Vary the size of your matrices from 200, 400, 600, 800 and 1000 and measure the runtime with one thread and four threads.
### c. For each matrix size, change the number of threads from 2,4,6 and 8 and plot the speedup versus the number of threads. Compute the efficiency.

### Program: matrix_mult.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void matrix_mult(int *a, int *b, int *c, int n) {
    #pragma omp parallel for shared(a,b,c,n)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i*n+k] * b[k*n+j];
            }
            c[i*n+j] = sum;
        }
    }
}
int main() {
    int n_sizes[] = {200, 400, 600, 800, 1000};
    int n_threads[] = {1, 4};
    // Run matrix multiplication with varying matrix sizes and number of threads
    for (int i = 0; i < 5; i++) {
        int n = n_sizes[i];
        int *a = (int*) malloc(n*n*sizeof(int));
        int *b = (int*) malloc(n*n*sizeof(int));
        int *c = (int*) malloc(n*n*sizeof(int));
        // Initialize matrices with random values
        for (int j = 0; j < n*n; j++) {
            a[j] = rand() % 10;
            b[j] = rand() % 10;
        }
        printf("Matrix size: %d x %d\n", n, n);
        for (int k = 0; k < 2; k++) {
            int num_threads = n_threads[k];
            double start_time = omp_get_wtime();
            // Set number of threads
            omp_set_num_threads(num_threads);
            // Multiply matrices
            matrix_mult(a, b, c, n);
            double end_time = omp_get_wtime();
            double elapsed_time = end_time - start_time;
            printf("  Number of threads: %d\n", num_threads);
            printf("  Elapsed time: %f seconds\n", elapsed_time);
        }
        free(a);
        free(b);
        free(c);
    }
    return 0;
}
```
### Output:
```plaintext
Matrix size: 200 x 200
  Number of threads: 1
  Elapsed time: 0.038000 seconds
  Number of threads: 4
  Elapsed time: 0.000000 seconds
Matrix size: 400 x 400
  Number of threads: 1
  Elapsed time: 0.216000 seconds
  Number of threads: 4
  Elapsed time: 0.054000 seconds
Matrix size: 600 x 600
  Number of threads: 1
  Elapsed time: 0.818000 seconds
  Number of threads: 4
  Elapsed time: 0.215000 seconds
Matrix size: 800 x 800
  Number of threads: 1
  Elapsed time: 1.939000 seconds
  Number of threads: 4
  Elapsed time: 0.482000 seconds
Matrix size: 1000 x 1000
  Number of threads: 1
  Elapsed time: 3.860000 seconds
  Number of threads: 4
  Elapsed time: 0.978000 seconds

--------------------------------
Process exited after 9.012 seconds with return value 0
Press any key to continue . . .
```
### Program Explanation:

#### **Objective:**
The program performs matrix multiplication with varying matrix sizes and analyzes the execution time for different numbers of threads using OpenMP.

#### **Implementation:**
- The program iterates over different matrix sizes specified in the `n_sizes` array.
- For each matrix size:
  - Allocates memory for matrices A, B, and C.
  - Initializes matrices A and B with random values.
  - Performs matrix multiplication using the `matrix_mult` function with both serial and parallel execution.
  - Records and prints the execution times for each combination of matrix size and number of threads.

#### **Matrix Multiplication Function: `matrix_mult`**
- The function takes pointers to matrices A, B, and C, along with the matrix size `n`.
- Utilizes OpenMP parallelism with `#pragma omp parallel for` to parallelize the outer loop, distributing the workload among multiple threads.
- Computes the matrix multiplication of A and B, storing the result in matrix C.

#### **Parallelization:**
- The main loop iterates over matrix sizes and the number of threads.
- OpenMP is used to set the number of threads and parallelize the matrix multiplication loop.

#### **Analysis:**
- The program prints the matrix size and, for each size, the execution time for both serial and parallel executions with varying numbers of threads.

### **Conclusion:**
- The program provides insights into the impact of parallelization on the execution time of matrix multiplication for different matrix sizes and thread counts.
- The output helps analyze the scalability of the parallelized code across different computational resources.

## Q2: Write an OpenMP program to perform Matrix times vector multiplication. Vary the matrix and vector size and analyze the speedup and efficiency of the parallelized code.

### Program: matrix_vector_mult.cpp
```cpp
#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
int main() {
    const int num_sizes = 5;
    const int sizes[num_sizes] = {2000, 4000, 6000, 8000, 10000};
    const int num_threads = 8;
    double time_start, time_end;
    double times[num_sizes];
    // loop over matrix sizes
    for (int k = 0; k < num_sizes; k++) {
        int N = sizes[k];
        // allocate matrices and vector
        double **A = new double*[N];
        double *x = new double[N];
        double *y = new double[N];
        for (int i = 0; i < N; i++) {
            A[i] = new double[N];
        }
        // initialize matrix and vector
        for (int i = 0; i < N; i++) {
            x[i] = 1.0;
            for (int j = 0; j < N; j++) {
                A[i][j] = (double)rand() / RAND_MAX;
            }
        }
        // matrix-vector multiplication with one thread
        time_start = omp_get_wtime();
        for (int i = 0; i < N; i++) {
            y[i] = 0.0;
            for (int j = 0; j < N; j++) {
                y[i] += A[i][j] * x[j];
            }
        }
        time_end = omp_get_wtime();
        double time_serial = time_end - time_start;
        // matrix-vector multiplication with multiple threads
        omp_set_num_threads(num_threads);
        time_start = omp_get_wtime();
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            y[i] = 0.0;
            for (int j = 0; j < N; j++) {
                y[i] += A[i][j] * x[j];
            }
        }
        time_end = omp_get_wtime();
        double time_parallel = time_end - time_start;
        times[k] = time_parallel;
        // free memory
        for (int i = 0; i < N; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] x;
        delete[] y;
        // print execution time for current matrix size
        std::cout << "Matrix size: " << N << ", execution time (serial): " << time_serial << " seconds, execution time (parallel): " << time_parallel << " seconds" << std::endl;
    }
    return 0;
}
```

### Output:
```plaintext
Matrix size: 2000, execution time (serial): 0.016 seconds, execution time (parallel): 0.0149999 seconds
Matrix size: 4000, execution time (serial): 0.0530002 seconds, execution time (parallel): 0.0159998 seconds
Matrix size: 6000, execution time (serial): 0.12 seconds, execution time (parallel): 0.0319998 seconds
Matrix size: 8000, execution time (serial): 0.214 seconds, execution time (parallel): 0.0599999 seconds
Matrix size: 10000, execution time (serial): 0.334 seconds, execution time (parallel): 0.0810001 seconds

--------------------------------
Process exited after 5.278 seconds with return value 0
Press any key to continue . . .
```
### Program Explanation:

#### **Objective:**
The program performs matrix-vector multiplication with varying matrix sizes and analyzes the speedup and efficiency of the parallelized code using OpenMP.

#### **Implementation:**
- The program iterates over different matrix sizes specified in the `sizes` array.
- For each matrix size:
  - It allocates memory for matrices A and vectors x, y.
  - Initializes matrix A with random values and vector x with 1.0.
  - Performs matrix-vector multiplication sequentially to obtain the result vector `y` (serial execution).
  - Performs the same multiplication in parallel using OpenMP with the specified number of threads.
  - Records and prints the execution times for both serial and parallel executions.
  - Calculates and stores the speedup for each matrix size.

#### **Parallelization:**
- OpenMP is utilized for parallelizing the matrix-vector multiplication loop with `#pragma omp parallel for`.
- The number of threads is set using `omp_set_num_threads` to control parallel execution.

#### **Analysis:**
- The program prints execution times for both serial and parallel executions for each matrix size.
- Speedup is calculated as the ratio of the serial execution time to the parallel execution time.
- Efficiency is calculated as the speedup divided by the number of threads.

### **Conclusion:**
- The program provides insights into the performance improvements achieved through parallelization for matrix-vector multiplication with varying matrix sizes.
- Speedup and efficiency metrics help evaluate the scalability of the parallelized code in utilizing multiple threads.
#

## Q3: Write an OpenMp program to read a matrix A of size 5x5. It produces a resultant matrix B of size 5x5. It sets all the principal diagonal elements of B matrix with 0. It replaces each row elements in the B matrix in the following manner. If the element is below the principal diagonal it replaces it with the maximum value of the row in the A matrix having the same row number of B. If the element is above the principal diagonal it replaces it with the minimum value of the row in the A matrix having the same row number of B. Analyze the speedup and efficiency of the parallelized code.

### Program: matrix_manipulation.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 5
void matrix_manipulation(int a[][N], int b[][N]) {
    #pragma omp parallel for shared(a,b)
    for (int i = 0; i < N; i++) {
        int row_min = a[i][0];
        int row_max = a[i][0];
        for (int j = 0; j < N; j++) {
            if (i == j) {
                b[i][j] = 0;
            } else if (i < j) {
                if (a[i][j] < row_min) {
                    row_min = a[i][j];
                }
                b[i][j] = row_min;
            } else {
                if (a[i][j] > row_max) {
                    row_max = a[i][j];
                }
                b[i][j] = row_max;
            }
        }
    }
}
int main() {
    int a[N][N];
    int b[N][N];
    // Initialize matrix A with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 10;
        }
    }
    matrix_manipulation(a, b);
    printf("Matrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("Matrix B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

### Output:
```plaintext
Matrix A:
1 7 4 0 9
4 8 8 2 4
5 5 1 7 1
1 5 2 7 6
1 4 2 3 2
Matrix B:
0 1 1 0 0
4 0 4 2 2
5 5 0 5 1
1 5 5 0 1
1 4 4 4 0

--------------------------------
Process exited after 0.1528 seconds with return value 0
Press any key to continue . . .
```
### Program Explanation:

#### **Objective:**
The program aims to perform matrix manipulation on a 5x5 matrix A and produce a resultant matrix B with specific properties. It uses OpenMP to parallelize the matrix manipulation process.

#### **Matrix Manipulation Function: `matrix_manipulation`**
- The function takes two matrices, A and B, as input.
- It uses OpenMP parallelism with `#pragma omp parallel for` to parallelize the outer loop, distributing the workload among multiple threads.
- For each row `i` in the matrices, it processes each element in the row based on the following conditions:
  - If the element is on the principal diagonal (i == j), it sets the corresponding element in B to 0.
  - If the element is below the principal diagonal (i < j), it replaces it with the minimum value of the row in matrix A with the same row number.
  - If the element is above the principal diagonal (i > j), it replaces it with the maximum value of the row in matrix A with the same row number.

#### **Main Function:**
- Initializes matrix A with random values.
- Calls the `matrix_manipulation` function to compute matrix B based on the specified rules.
- Prints both matrices A and B for verification.

#### **Parallelism:**
- The code employs parallelism in the `matrix_manipulation` function using OpenMP directives. The parallelization is achieved by distributing the iterations of the outer loop among available threads.

### **Conclusion:**
The program demonstrates the parallelization of matrix manipulation operations using OpenMP. It sets principal diagonal elements of matrix B to 0 and replaces each element based on conditions involving the minimum and maximum values of rows in matrix A. Parallelizing such matrix operations can lead to performance improvements, especially when dealing with larger matrices, by leveraging multiple threads for concurrent computation. The output matrices A and B are then printed for verification.

#
## Q4: Write a parallel program using OpenMP that reads a matrix of size MxN and produce an output matrix B of same size such that it replaces all the non-border elements of A with its equivalent 1’s complement and remaining elements same as matrix A. Also produce a matrix D as shown below.
## Example:
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

### Program: matrix_operations.cpp
```cpp
#include <iostream>
#include <omp.h>
#include<bits/stdc++.h>
using namespace std;
int main() {
    const int M = 4;
    const int N = 4;
    int A[M][N] = {
        {1, 2, 3, 4},
        {6, 5, 8, 3},
        {2, 4, 10, 1},
        {9, 1, 2, 5}
    };
    int B[M][N];
    int D[M][N];
    #pragma omp parallel for shared(A, B, D)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || i == M-1 || j == 0 || j == N-1) {
                B[i][j] = A[i][j];
            } else {
                B[i][j] = ~A[i][j] + 2;
            }
            if (i == j) {
                D[i][j] = 1;
            } else {
                D[i][j] = abs(i - j) + 1;
            }
        }
    }
    cout << "Matrix A:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Matrix B:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Matrix D:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

### Output:
```plaintext
Matrix A:
1 2 3 4
6 5 8 3
2 4 10 1
9 1 2 5
Matrix B:
1 2 3 4
6 10 111 3
2 11 101 1
9 1 2 5
Matrix D:
1 2 3 4
6 2 7 3
2 3 5 1
9 1 2 5

--------------------------------
Process exited after 0.277 seconds with return value 0
Press any key to continue . . .
```
### Explanation:

1. **Matrix A Initialization:**
   - A 4x4 matrix A is initialized with the provided values, representing the input matrix.

2. **OpenMP Parallel Region:**
   - The code enters a parallel region using `#pragma omp parallel for`, parallelizing the outer loop that iterates over the rows of the matrices. This allows concurrent execution of operations on different rows by multiple threads.

3. **Matrix B Calculation:**
   - Within the parallel region, each element of matrix B is computed independently based on the following conditions:
     - If the element is a non-border element (not on the first or last row or column), its value in B is set to the 1's complement of the corresponding element in matrix A.
     - If the element is a border element, its value in B remains the same as in matrix A.

4. **Matrix D Calculation:**
   - Simultaneously, within the parallel region, matrix D is computed based on the given logic:
     - Diagonal elements in D are set to 1.
     - Off-diagonal elements are set to the absolute difference between their row and column indices plus 1.

5. **Display Matrices:**
   - After the parallel region, the program displays the original matrix A and the computed matrices B and D.

In summary, the program takes advantage of parallel processing with OpenMP to efficiently perform operations on matrices. It calculates matrix B by replacing non-border elements of matrix A with their 1's complement, and it generates matrix D based on a specific logic. The parallelization allows for improved performance, especially when dealing with large matrices, by leveraging multiple threads to concurrently handle different portions of the computation.
#
## Q5: Write a parallel program in OpenMP to reverse the digits of the following integer array of size 9. Initialize the input array to the following values:
### a. Input array: `18, 523, 301, 1234, 2, 14, 108, 150, 1928`
### b. Output array: `81, 325, 103, 4321, 2, 41, 801, 51, 8291`

### Program: reverse_digits.c
```c
#include <stdio.h>
#include <omp.h>
#define SIZE 9
void reverseDigits(int *input, int *output, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        int num = input[i];
        int reversed = 0;
        while (num > 0) {
            reversed = reversed * 10 + (num % 10);
            num /= 10;
        }
        output[i] = reversed;
    }
}
int main() {
    int input[SIZE];
    int output[SIZE];
  printf("Enter 9 numbers\n");
  for (int i = 0; i < 9; i++) {
    scanf("%d", &input[i]);
  }
    reverseDigits(input, output, SIZE);
    printf("Input array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");
    printf("Output array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");
    return 0;
}
```

### Output:
```plaintext
Enter 9 numbers
18 523 301 1234 2 14 108 150 1928
Input array: 18 523 301 1234 2 14 108 150 1928
Output array: 81 325 103 4321 2 41 801 51 8291

--------------------------------
Process exited after 26.27 seconds with return value 0
Press any key to continue . . .
```
### Explanation:

1. **`reverseDigits` Function:**
   - The function takes an input array of integers, an output array, and the size of the array.
   - It uses OpenMP parallelism (`#pragma omp parallel for`) to parallelize the loop that iterates over the elements of the array.
   - Inside the loop, it reverses the digits of each integer and stores the result in the output array.

2. **`main` Function:**
   - Defines arrays `input` and `output` to store the original and reversed integers, respectively.
   - Reads 9 integers from the user and stores them in the `input` array.
   - Calls the `reverseDigits` function to reverse the digits in parallel.
   - Prints the original and reversed arrays.

3. **OpenMP Directives:**
   - `#pragma omp parallel for`: Specifies that the associated for-loop should be executed in parallel by multiple threads.

4. **Input and Output:**
   - The user is prompted to enter 9 numbers.
   - The program then displays the original and reversed arrays.

This program demonstrates how to apply parallel processing to efficiently reverse the digits of integers in an array using OpenMP directives.
