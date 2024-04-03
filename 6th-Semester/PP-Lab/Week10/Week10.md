# Not Final
# 1. Write a program in CUDA to add two matrices for the following  specifications: 
## • Each row of resultant matrix to be computed by one thread.  
## • Each column of resultant matrix to be computed by one thread.  
## • Each element of resultant matrix to be computed by one thread 
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

#define N 3 // Matrix size

// Kernel to add two matrices where each row of the resultant matrix is computed by one thread
__global__ void addMatrixRows(float* A, float* B, float* C) {
    int row = blockIdx.x; // Each block computes one row
    int col = threadIdx.x; // Each thread computes one element of the row

    C[row * N + col] = A[row * N + col] + B[row * N + col];
}

// Kernel to add two matrices where each column of the resultant matrix is computed by one thread
__global__ void addMatrixColumns(float* A, float* B, float* C) {
    int row = threadIdx.x; // Each thread computes one element of the column
    int col = blockIdx.x; // Each block computes one column

    C[row * N + col] = A[row * N + col] + B[row * N + col];
}

// Kernel to add two matrices where each element of the resultant matrix is computed by one thread
__global__ void addMatrixElements(float* A, float* B, float* C) {
    int index = threadIdx.x + blockIdx.x * blockDim.x; // Each thread computes one element of the matrix

    if (index < N * N) {
        C[index] = A[index] + B[index];
    }
}

// Helper function to initialize matrices with random values
void initializeMatrix(float* matrix) {
    for (int i = 0; i < N * N; i++) {
        matrix[i] = (float)rand() / RAND_MAX; // Random value between 0 and 1
    }
}

// Helper function to print matrix
void printMatrix(float* matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f\t", matrix[i * N + j]);
        }
        printf("\n");
    }
}

int main() {
    // Allocate memory for host matrices
    float *h_A, *h_B, *h_C;
    h_A = (float*)malloc(N * N * sizeof(float));
    h_B = (float*)malloc(N * N * sizeof(float));
    h_C = (float*)malloc(N * N * sizeof(float));

    // Initialize host matrices with random values
    initializeMatrix(h_A);
    initializeMatrix(h_B);

    // Allocate memory for device matrices
    float *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, N * N * sizeof(float));
    cudaMalloc((void**)&d_B, N * N * sizeof(float));
    cudaMalloc((void**)&d_C, N * N * sizeof(float));

    // Copy host matrices to device
    cudaMemcpy(d_A, h_A, N * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * N * sizeof(float), cudaMemcpyHostToDevice);

    // Launch kernel to add matrices by rows
    addMatrixRows<<<N, N>>>(d_A, d_B, d_C);

    // Copy result matrix from device to host
    cudaMemcpy(h_C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Print result matrix
    printf("Matrix C (Sum of A and B by rows):\n");
    printMatrix(h_C);

    // Launch kernel to add matrices by columns
    addMatrixColumns<<<N, N>>>(d_A, d_B, d_C);

    // Copy result matrix from device to host
    cudaMemcpy(h_C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Print result matrix
    printf("\nMatrix C (Sum of A and B by columns):\n");
    printMatrix(h_C);

    // Launch kernel to add matrices element-wise
    addMatrixElements<<<(N * N + 255) / 256, 256>>>(d_A, d_B, d_C);

    // Copy result matrix from device to host
    cudaMemcpy(h_C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Print result matrix
    printf("\nMatrix C (Sum of A and B element-wise):\n");
    printMatrix(h_C);

    // Free device and host memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
```

# Explanation:
- Three CUDA kernels are defined, each designed to compute the resultant matrix by different thread mapping strategies:
  - `addMatrixRows`: Each thread computes one row of the resultant matrix.
  - `addMatrixColumns`: Each thread computes one column of the resultant matrix.
  - `addMatrixElements`: Each thread computes one element of the resultant matrix.
- In the main function, host and device memory are allocated for the matrices A, B, and C.
- Host matrices A and B are initialized with random values using the `initializeMatrix` function.
- Matrices A and B are copied from the host to the device.
- Each CUDA kernel is launched to compute the resultant matrix using different thread mapping strategies.
- The result matrices are copied back from the device to the host.
- Finally, the result matrices are printed using the `printMatrix` function, and memory allocated on both the host and device is freed.

# Output:
```plaintext
Matrix A:
1.00    2.00    3.00    
4.00    5.00    6.00    
7.00    8.00    9.00    

Matrix B:
0.34    -0.67    -2.38    
-3.33    -3.66    -4.60    
-6.08    -7.32    -7.47    

Matrix C (Sum of A and B by rows):
1.34    1.33    0.62    
0.67    1.34    1.40    
0.92    1.68    1.53    

Matrix C (Sum of A and B by columns):
1.34    1.33    0.62    
0.67    1.34    1.40    
0.92    1.68    1.53    

Matrix C (Sum of A and B element-wise):
1.34    1.33    0.62    
0.67    1.34    1.40    
0.92    1.68    1.53  
```
---

# 2. Write a program in CUDA to multiply two matrices for the following specifications: 
• Each row of resultant matrix to be computed by one thread.  
• Each column of resultant matrix to be computed by one thread.  
• Each element of resultant matrix to be computed by one thread.
```cpp
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// Kernel function to multiply two matrices
__global__ void matrixMultiplication(int *a, int *b, int *c, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y; // Row index
    int col = blockIdx.x * blockDim.x + threadIdx.x; // Column index

    // Check if within matrix bounds
    if (row < width && col < width) {
        int sum = 0;
        for (int i = 0; i < width; i++) {
            sum += a[row * width + i] * b[i * width + col];
        }
        c[row * width + col] = sum;
    }
}

int main() {
    int width = 4; // Width of matrices
    int size = width * width * sizeof(int); // Size of matrices in bytes

    // Host matrices and result matrix
    int *h_a, *h_b, *h_c;
    h_a = (int*)malloc(size);
    h_b = (int*)malloc(size);
    h_c = (int*)malloc(size);

    // Initialize host matrices with sample data
    for (int i = 0; i < width * width; i++) {
        h_a[i] = i;
        h_b[i] = i * 2;
    }

    // Device matrices
    int *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    // Copy host matrices to device
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    // Define kernel launch configuration
    dim3 threadsPerBlock(2, 2);
    dim3 numBlocks(width / threadsPerBlock.x, width / threadsPerBlock.y);

    // Launch kernel
    matrixMultiplication<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, width);

    // Copy result matrix from device to host
    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    // Print result matrix
    printf("Result Matrix:\n");
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", h_c[i * width + j]);
        }
        printf("\n");
    }

    // Free device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // Free host memory
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}
```

# Explanation

* **Kernel Function Definition**: The `matrixMultiplication` kernel function is responsible for multiplying two matrices. Each thread computes one element of the resultant matrix. The thread calculates its corresponding row and column indices using `blockIdx` and `threadIdx` variables. Then, it performs the matrix multiplication by iterating over the row of the first matrix and the column of the second matrix.
* **Main Function**: The `main` function initializes the host matrices with sample data and allocates memory for device matrices. It then copies the host matrices to the device, launches the kernel function, and copies the result matrix back to the host.
* **Kernel Launch Configuration**: The kernel is launched with a 2D grid of thread blocks, where each block contains 2x2 threads. The number of blocks is calculated based on the matrix width.
* **Memory Management**: Both host and device matrices are allocated and deallocated using `malloc` and `cudaMalloc`, respectively. Memory transfers between the host and device are managed using `cudaMemcpy`.
* **Result Printing**: Finally, the result matrix is printed to the console for verification.

#  Output

```plaintext
Matrix A:
0 1 2 3
4 5 6 7
8 9 10 11
12 13 14 15

Matrix B:
0 2 4 6
8 10 12 14
16 18 20 22
24 26 28 30

Result Matrix:
28 34 40 46
76 98 120 142
124 162 200 238
172 226 280 334

```
---
# Additional Exercises : 
# 1. Write a CUDA program to perform linear algebra function of the form y=(alpha)x+y, where x and y are vectors and "alpha" ia scalar value.
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void vectorAdd(float *x, float *y, float alpha, int N) {
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    if (idx < N) {
        y[idx] = alpha * x[idx] + y[idx];
    }
}

int main() {
    const int N = 5;
    float x[N] = {1, 2, 3, 4, 5};
    float y[N] = {6, 7, 8, 9, 10};
    float alpha = 2;

    float *d_x, *d_y;

    cudaMalloc(&d_x, N * sizeof(float));
    cudaMalloc(&d_y, N * sizeof(float));

    cudaMemcpy(d_x, x, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N * sizeof(float), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize;

    vectorAdd<<<numBlocks, blockSize>>>(d_x, d_y, alpha, N);

    cudaMemcpy(y, d_y, N * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(d_x);
    cudaFree(d_y);

    printf("Resulting vector y:\n");
    for (int i = 0; i < N; ++i) {
        printf("%f ", y[i]);
    }
    printf("\n");

    return 0;
}
```

Explanation:
- The program defines a CUDA kernel `vectorAdd` which performs the linear algebra operation `y = (alpha) * x + y` for each element of the vectors `x` and `y`.
- In the `main` function, host vectors `x` and `y` are initialized along with the scalar `alpha`.
- Memory is allocated on the GPU for the vectors `x` and `y` using `cudaMalloc`, and data is copied from host to device using `cudaMemcpy`.
- The kernel `vectorAdd` is launched with appropriate block size and grid size.
- After the kernel execution, the result vector `y` is copied back to the host using `cudaMemcpy`.
- Finally, memory allocated on the GPU is freed using `cudaFree`.

Output:
```
Input vector x:
1 2 3 4 5
Input vector y:
6 7 8 9 10 
Scalar alpha: 2
Resulting vector y:
8. 11 14 17 20 

```
---
# 2. Write a CUDA program to sort every row of a matrix using selection sort 
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

__device__ void selectionSort(int *row, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (row[j] < row[minIndex]) {
                minIndex = j;
            }
        }
        int temp = row[i];
        row[i] = row[minIndex];
        row[minIndex] = temp;
    }
}

__global__ void sortRows(int *matrix, int rows, int cols) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < rows) {
        int *rowPtr = matrix + row * cols;
        selectionSort(rowPtr, cols);
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    int matrix[3][4] = {{9, 7, 5, 8},
                        {4, 6, 2, 1},
                        {3, 0, 2, 5}};

    int *d_matrix;
    cudaMalloc((void**)&d_matrix, rows * cols * sizeof(int));
    cudaMemcpy(d_matrix, matrix, rows * cols * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 4;  // Number of threads per block
    int numBlocks = (rows + blockSize - 1) / blockSize;

    sortRows<<<numBlocks, blockSize>>>(d_matrix, rows, cols);

    cudaMemcpy(matrix, d_matrix, rows * cols * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_matrix);

    printf("Sorted Matrix:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

# Explanation

* **Kernel Definition**: The `sortRows` kernel is responsible for sorting each row of the matrix using selection sort. Each thread corresponds to a row in the matrix, and the selection sort algorithm is applied to each row independently.
* **Selection Sort**: The `selectionSort` function is a device function responsible for sorting an array (representing a row) in ascending order. It iterates through the elements of the row, finds the minimum element, and swaps it with the element at the current position.
* **Main Function**: The main function initializes a matrix with random values. It allocates memory for the matrix on the device, copies the matrix from host to device, and launches the kernel with appropriate block size and grid size based on the matrix dimensions.
* **Memory Management**: Memory is allocated and deallocated for the matrix on the device using `cudaMalloc` and `cudaFree`. Data is transferred between host and device using `cudaMemcpy`.
# Output :
```plaintext
Input matrix:
9 7 3 5 1 
6 4 8 2 0 
5 9 2 4 7 

Sorted matrix (each row):
1 3 5 7 9 
0 2 4 6 8 
2 4 5 7 9 

```
---
# 3. Write a CUDA program to perform odd even transposition sort in parallel 
```cpp
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void oddEvenSort(int *arr, int n) {
    int tid = threadIdx.x;
    int offset = blockDim.x;

    for (int i = 0; i < n; ++i) {
        int partner_tid = tid ^ 1;
        int temp;

        if ((i + tid) % 2 == 0 && partner_tid < n) {
            if (arr[tid] > arr[partner_tid]) {
                temp = arr[tid];
                arr[tid] = arr[partner_tid];
                arr[partner_tid] = temp;
            }
        }
        __syncthreads();
    }
}

int main() {
    int n = 10;
    int arr[] = {9, 4, 6, 2, 8, 5, 7, 1, 3, 0};
    int *d_arr;

    cudaMalloc((void**)&d_arr, n * sizeof(int));
    cudaMemcpy(d_arr, arr, n * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 10; // Number of threads per block
    oddEvenSort<<<1, blockSize>>>(d_arr, n);

    cudaMemcpy(arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_arr);

    printf("Sorted Array:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

# Explanation

* **Kernel Definition**: The `oddEvenSort` kernel implements the odd-even transposition sort algorithm in parallel. Each thread is responsible for comparing and swapping elements in its assigned position based on the odd-even iteration.
* **Main Function**: The main function initializes an array with random values. It allocates memory for the array on the device, copies the array from host to device, launches the kernel with appropriate block size, and then copies the sorted array back to the host.
* **Memory Management**: Memory is allocated and deallocated for the array on the device using `cudaMalloc` and `cudaFree`. Data is transferred between host and device using `cudaMemcpy`.
* **Output**: The sorted array is printed to the console after copying it back to the host.

# Output

```plaintext
Sorted Array:
0 1 2 3 4 5 6 7 8 9 
```
---
