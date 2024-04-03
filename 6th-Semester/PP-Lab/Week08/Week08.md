# 1. Write a program in CUDA to add two vectors of length N using  
- ### a) block size as N     
```cpp
#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>

// CUDA kernel to add elements of two arrays
__global__ void add(int* x, int* y, int* z, int n) {
    int index = threadIdx.x;
    if (index < n)
        z[index] = x[index] + y[index];
}

// Function to print the vector
void printVector(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int main() {
    int N = 1024; // Example size, make sure it does not exceed your GPU's capability
    int* x, * y, * z, * d_x, * d_y, * d_z;

    // Allocate memory
    x = (int*)malloc(N * sizeof(int));
    y = (int*)malloc(N * sizeof(int));
    z = (int*)malloc(N * sizeof(int));

    cudaMalloc(&d_x, N * sizeof(int));
    cudaMalloc(&d_y, N * sizeof(int));
    cudaMalloc(&d_z, N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        x[i] = 1;
        y[i] = 2;
    }

    // Copy inputs to device
    cudaMemcpy(d_x, x, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N * sizeof(int), cudaMemcpyHostToDevice);

    // Launch add() kernel on GPU
    add << <1, N >> > (d_x, d_y, d_z, N);

    // Copy result back to host
    cudaMemcpy(z, d_z, N * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result
    printf("Result: ");
    printVector(z, N);

    // Cleanup
    cudaFree(d_x); cudaFree(d_y); cudaFree(d_z);
    free(x); free(y); free(z);

    return 0;
}

```
## Explaination
* Kernel Definition: The add function is a CUDA kernel, which is a function that will be executed on the GPU. It takes as input two integer arrays x and y, an output array z, and the size n of these arrays. Each thread computes the sum of a pair of elements from x and y and stores the result in z.
* Main Function: The main function begins by defining the size of the vectors to be processed (N), and allocating memory for the input vectors x and y, and the output vector z on the host using malloc. It also allocates memory for the vectors d_x, d_y, and d_z on the device (GPU) using cudaMalloc.
* Initialization: The host input vectors x and y are initialized such that all their elements are 1 and 2, respectively.
* Data Transfer: The initialized input vectors x and y are copied from the host to the device using cudaMemcpy.
* Kernel Invocation: The add kernel is launched with 1 block, each containing N threads.
* Result Retrieval: The result vector d_z is copied from the device to the host, and the elements of the host result vector z are printed using the printVector function.
* Memory Deallocation: Finally, the memory allocated on the device and the host is freed using cudaFree and free, respectively.

This program demonstrates a basic CUDA workflow of allocating memory, transferring data between the host and device, launching a kernel, and retrieving results. It’s a simple but fundamental example of GPU programming with CUDA. The output shows that the addition of the vectors x and y has been performed correctly, as all elements of the result vector z are 3. The program has exited with code 0, indicating successful execution. The console will automatically close when debugging stops if the corresponding setting is enabled in the debugging options. The user can press any key to close the console window.



## Output
```plaintext
Result: 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

E:Suzen\PP\Lab\Week6_MPI\Week6\CudaRuntime7\x64\Debug\CudaRuntime7.exe (process 38600) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
```

Please note that the size N is set to 1024 in this example, which is the number of threads per block. Make sure it does not exceed your GPU’s capability. If you have a GPU with a larger number of cores, you can increase N to fully utilize your GPU. However, the maximum number of threads per block is limited by the CUDA architecture, and the current limit is 1024 threads per block. If you need to process larger data, you should distribute the data across multiple blocks.

- ### b) N threads 
```cpp
#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>

__global__ void add(int* x, int* y, int* z, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n)
        z[index] = x[index] + y[index];
}

void printVector(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int main() {
    int N = 2048; // Example size
    int* x, * y, * z, * d_x, * d_y, * d_z;

    x = (int*)malloc(N * sizeof(int));
    y = (int*)malloc(N * sizeof(int));
    z = (int*)malloc(N * sizeof(int));

    cudaMalloc(&d_x, N * sizeof(int));
    cudaMalloc(&d_y, N * sizeof(int));
    cudaMalloc(&d_z, N * sizeof(int));

    for (int i = 0; i < N; i++) {
        x[i] = 1;
        y[i] = 2;
    }

    cudaMemcpy(d_x, x, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256; // Choose appropriate block size
    int numBlocks = (N + blockSize - 1) / blockSize;

    add << <numBlocks, blockSize >> > (d_x, d_y, d_z, N);

    cudaMemcpy(z, d_z, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Result: ");
    printVector(z, N);

    cudaFree(d_x); cudaFree(d_y); cudaFree(d_z);
    free(x); free(y); free(z);

    return 0;
}

```
## Explaination

* Kernel Definition: The add function is a CUDA kernel, which is a function that will be executed on the GPU. It takes as input two integer arrays x and y, an output array z, and the size n of these arrays. Each thread computes the sum of a pair of elements from x and y and stores the result in z.
* Main Function: The main function begins by defining the size of the vectors to be processed (N), and allocating memory for the input vectors x and y, and the output vector z on the host using malloc. It also allocates memory for the vectors d_x, d_y, and d_z on the device (GPU) using cudaMalloc.
* Initialization: The host input vectors x and y are initialized such that all their elements are 1 and 2, respectively.
* Data Transfer: The initialized input vectors x and y are copied from the host to the device using cudaMemcpy.
* Kernel Invocation: The add kernel is launched with numBlocks blocks, each containing blockSize threads. The number of blocks and the number of threads per block are calculated based on the size of the vectors and the chosen block size.
* Result Retrieval: The result vector d_z is copied from the device to the host, and the elements of the host result vector z are printed using the printVector function.
* Memory Deallocation: Finally, the memory allocated on the device and the host is freed using cudaFree and free, respectively.

This program demonstrates a basic CUDA workflow of allocating memory, transferring data between the host and device, launching a kernel, and retrieving results. It’s a simple but fundamental example of GPU programming with CUDA. The output shows that the addition of the vectors x and y has been performed correctly, as all elements of the result vector z are 3.

## Output
```plaintext
Result: 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

E:Suzen\PP\Lab\Week6_MPI\Week6\CudaRuntime7\x64\Debug\CudaRuntime7.exe (process 47256) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
```
Please note that the size N is set to 2048 in this example, which is the number of elements in the vectors. The block size is set to 256, and the number of blocks is calculated as (N + blockSize - 1) / blockSize to ensure that there are enough blocks to cover all elements even if N is not a multiple of blockSize. This configuration allows the program to handle vectors of size up to the maximum number of threads that your GPU supports, which is typically much larger than 1024.


# 2. Implement a CUDA program to add two vectors of length N by keeping the  number of threads per block as 256 (constant) and vary the number of blocks to handle N elements.


```cpp
#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>

// CUDA kernel to add elements of two arrays
__global__ void add(int* a, int* b, int* c, int N) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < N)
        c[index] = a[index] + b[index];
}

int main() {
    int N = 1 << 20; // Example: Number of elements in each vector (1 Million elements)
    int size = N * sizeof(int);
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock; // Calculate needed blocks

    // Allocate memory on the host
    int* h_a, * h_b, * h_c;
    h_a = (int*)malloc(size);
    h_b = (int*)malloc(size);
    h_c = (int*)malloc(size);

    // Initialize vectors on the host
    for (int i = 0; i < N; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    // Allocate vectors in device memory
    int* d_a, * d_b, * d_c;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    // Copy vectors from host memory to device memory
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    // Invoke kernel
    add << <blocksPerGrid, threadsPerBlock >> > (d_a, d_b, d_c, N);

    // Copy result from device memory to host memory
    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    // Print the results: Print the first 10 elements
    printf("Result of Vector Addition (First 10 Elements):\n");
    for (int i = 0; i < 10; i++) {
        printf("h_c[%d] = %d\n", i, h_c[i]);
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
This is a CUDA program that performs vector addition on the GPU. Here’s a brief explanation of the code:
* Kernel Definition: The add function is a CUDA kernel, which is a function that will be executed on the GPU. It takes as input two integer arrays a and b, an output array c, and the size N of these arrays. Each thread calculates the sum of a pair of elements from a and b and stores the result in c.
* Main Function: The main function begins by defining the size of the vectors to be processed (N), the size in bytes of these vectors (size), and the number of threads per block (threadsPerBlock). It also calculates the number of blocks per grid (blocksPerGrid) needed to process N elements.
* Memory Allocation: Memory for the input vectors h_a and h_b, and the output vector h_c, is allocated on the host (CPU) using malloc. Similarly, memory for the vectors d_a, d_b, and d_c is allocated on the device (GPU) using cudaMalloc.
* Initialization: The host input vectors h_a and h_b are initialized such that their i-th elements are i.
* Data Transfer: The initialized input vectors h_a and h_b are copied from the host to the device using cudaMemcpy.
* Kernel Invocation: The add kernel is launched with blocksPerGrid blocks, each containing threadsPerBlock threads.
* Result Retrieval: The result vector d_c is copied from the device to the host, and the first 10 elements of the host result vector h_c are printed.
* Memory Deallocation: Finally, the memory allocated on the device and the host is freed using cudaFree and free, respectively.
  
## Output
```plaintext
Result of Vector Addition (First 10 Elements):
h_c[0] = 0
h_c[1] = 2
h_c[2] = 4
h_c[3] = 6
h_c[4] = 8
h_c[5] = 10
h_c[6] = 12
h_c[7] = 14
h_c[8] = 16
h_c[9] = 18

E:Suzen\PP\Lab\Week8\Q2\x64\Debug\Q2.exe (process 61936) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

```
# 3. Write a program in CUDA which performs convolution operation on one dimensional input array N of size width using a mask array M of size ***mask_width*** to produce the resultant one-dimensional array P of size ***width*** 

```cpp
#include <stdio.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>

// CUDA Kernel for one-dimensional convolution
__global__ void convolution_1d(int* N, int* M, int* P, int width, int mask_width) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int k;

    // Each thread computes one element of P
    if (i < width) {
        int pValue = 0;
        // Convolution operation
        for (k = 0; k < mask_width; ++k) {
            int maskIndex = mask_width - 1 - k;
            int nIndex = i - (mask_width / 2) + k;
            if (nIndex >= 0 && nIndex < width) {
                pValue += N[nIndex] * M[maskIndex];
            }
        }
        P[i] = pValue;
    }
}

// Function to print the array
void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int width = 10; // Example array size
    int mask_width = 3; // Example mask size
    int N[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // Example input array
    int M[3] = { 1, 0, -1 }; // Example mask array
    int P[10]; // Resultant array

    int* d_N, * d_M, * d_P;

    // Allocate memory on the device
    cudaMalloc(&d_N, width * sizeof(int));
    cudaMalloc(&d_M, mask_width * sizeof(int));
    cudaMalloc(&d_P, width * sizeof(int));

    // Copy inputs to device
    cudaMemcpy(d_N, N, width * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, M, mask_width * sizeof(int), cudaMemcpyHostToDevice);

    // Launch kernel on the GPU
    convolution_1d << <(width + 255) / 256, 256 >> > (d_N, d_M, d_P, width, mask_width);

    // Copy result back to host
    cudaMemcpy(P, d_P, width * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the resultant array
    printf("Resultant array: ");
    printArray(P, width);

    // Free device memory
    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}

```
## Explaination
* Kernel Definition: The convolution_1d function is a CUDA kernel, which is a function that will be executed on the GPU. It takes as input two integer arrays N and M, an output array P, the size width of these arrays, and the size mask_width of the mask. Each thread computes the convolution of a subset of elements from N and M and stores the result in P.
* Main Function: The main function begins by defining the size of the vectors to be processed (width), the size of the mask (mask_width), and initializing the input arrays N and M and the output array P.
* Memory Allocation: Memory for the input vectors N and M, and the output vector P, is allocated on the device (GPU) using cudaMalloc.
* Data Transfer: The initialized input vectors N and M are copied from the host to the device using cudaMemcpy.
* Kernel Invocation: The convolution_1d kernel is launched with (width + 255) / 256 blocks, each containing 256 threads.
* Result Retrieval: The result vector P is copied from the device to the host, and the elements of the host result vector P are printed using the printArray function.
* Memory Deallocation: Finally, the memory allocated on the device is freed using cudaFree.

This program demonstrates a basic CUDA workflow of allocating memory, transferring data between the host and device, launching a kernel, and retrieving results. It’s a simple but fundamental example of GPU programming with CUDA for one-dimensional convolution. The convolution operation is a common operation in signal and image processing. It involves a mask (also known as a kernel) that is used to compute each element in the output array based on its corresponding input element and its neighbors. In this case, the mask is an array M of size mask_width. Each output element P[i] is computed as the sum of N[nIndex] * M[maskIndex] for all valid indices nIndex and maskIndex.

## Output
```plaintext
Resultant array: 2 2 2 2 2 2 2 2 2 -9

E:Suzen\PP\Lab\Week8\Q3\x64\Debug\Q3.exe (process 67188) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
```

# 4. Write a program in CUDA to process a ID array containing angles in radians to generate sine of the angles in the output array. Use appropriate function.

```cpp
#include <stdio.h>
#include <cuda_runtime.h>
#include <math.h>
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>

// Define M_PI if it's not defined by the math library
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// CUDA Kernel to compute sine of angles in radians
__global__ void compute_sine(float* input, float* output, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) {
        output[index] = sinf(input[index]); // Use sinf for single precision float
    }
}

// Function to print the array
void printArray(float* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", array[i]);
    }
    printf("\n");
}

int main() {
    int n = 5; // Example array size
    float inputAngles[] = { 0.0, M_PI / 6, M_PI / 4, M_PI / 2, M_PI }; // Example angles in radians

    // Allocate memory on the device
    float* d_input, * d_output;
    cudaMalloc((void**)&d_input, n * sizeof(float));
    cudaMalloc((void**)&d_output, n * sizeof(float));

    // Copy the input array from host to device
    cudaMemcpy(d_input, inputAngles, n * sizeof(float), cudaMemcpyHostToDevice);

    // Calculate the number of blocks and threads per block
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    // Allocate memory for the output array on the host
    float* output = new float[n]; // Use dynamic allocation

    // Launch the CUDA Kernel
    compute_sine << <blocksPerGrid, threadsPerBlock >> > (d_input, d_output, n);

    // Copy the result back to the host
    cudaMemcpy(output, d_output, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the resultant array
    printf("Sine of angles: ");
    printArray(output, n);

    // Free device memory
    cudaFree(d_input);
    cudaFree(d_output);

    // Free host memory
    delete[] output;

    return 0;
}

```

## Explaination

* Kernel Definition: The compute_sine function is a CUDA kernel, which is a function that will be executed on the GPU. It takes as input an array of angles in radians (input), an output array (output), and the size n of these arrays. Each thread computes the sine of an angle from input and stores the result in output.
* Main Function: The main function begins by defining the size of the array to be processed (n), and initializing the input array inputAngles with a set of angles in radians.
* Memory Allocation: Memory for the input array inputAngles and the output array output is allocated on the device (GPU) using cudaMalloc. Memory for the output array is also allocated on the host using dynamic allocation (new).
* Data Transfer: The initialized input array inputAngles is copied from the host to the device using cudaMemcpy.
* Kernel Invocation: The compute_sine kernel is launched with blocksPerGrid blocks, each containing threadsPerBlock threads.
* Result Retrieval: The result array output is copied from the device to the host, and the elements of the host result array output are printed using the printArray function.
* Memory Deallocation: Finally, the memory allocated on the device is freed using cudaFree, and the memory allocated on the host is freed using delete[].
  
This program demonstrates a basic CUDA workflow of allocating memory, transferring data between the host and device, launching a kernel, and retrieving results. It’s a simple but fundamental example of GPU programming with CUDA for computing the sine of a set of angles. The sine operation is a common operation in many fields including physics, engineering, and computer graphics.

## Output
```plaintext
Sine of angles: 0.000000 0.500000 0.707107 1.000000 -0.000000

E:Suzen\PP\Lab\Week8\Q2\x64\Debug\Q2.exe (process 76112) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

```
