# OpenMP Lab Programs

## Q1: Matrix Multiplication

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

## Q2: Matrix-Vector Multiplication

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

## Q3: Matrix Manipulation

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

## Q4: Advanced Matrix Operations

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

## Q5: Reverse Digits in an Array

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
1234
123
54
856
467
35
84
2
455
Input array: 1234 123 54 856 467 35 84 2 455
Output array: 4321 321 45 658 764 53 48 2 554

--------------------------------
Process exited after 9.44 seconds with return value 0
Press any key to continue . . .
```
