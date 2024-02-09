# Week 5
## Q1) Write a parallel program using OpenMP to perform vector addition, subtraction, 
multiplication. Demonstrate task level parallelism. Analyze the speedup and efficiency of the 
parallelized code. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

void vector_addition(int *a, int *b, int *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}

void vector_subtraction(int *a, int *b, int *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] - b[i];
    }
}

void vector_multiplication(int *a, int *b, int *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] * b[i];
    }
}

int main() {
    int *a, *b, *result_serial, *result_parallel;
    int i;

    // Allocate memory for vectors
    a = (int *)malloc(SIZE * sizeof(int));
    b = (int *)malloc(SIZE * sizeof(int));
    result_serial = (int *)malloc(SIZE * sizeof(int));
    result_parallel = (int *)malloc(SIZE * sizeof(int));

    // Initialize vectors
    for (i = 0; i < SIZE; ++i) {
        a[i] = i;
        b[i] = SIZE - i;
    }

    // Serial vector operations
    double start_time_serial = omp_get_wtime();
    vector_addition(a, b, result_serial, SIZE);
    vector_subtraction(a, b, result_serial, SIZE);
    vector_multiplication(a, b, result_serial, SIZE);
    double end_time_serial = omp_get_wtime();

    // Parallel vector operations
    double start_time_parallel = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            vector_addition(a, b, result_parallel, SIZE);

            #pragma omp task
            vector_subtraction(a, b, result_parallel, SIZE);

            #pragma omp task
            vector_multiplication(a, b, result_parallel, SIZE);
        }
    }
    double end_time_parallel = omp_get_wtime();

    // Calculate speedup and efficiency
    double serial_time = end_time_serial - start_time_serial;
    double parallel_time = end_time_parallel - start_time_parallel;
    double speedup = serial_time / parallel_time;
    double efficiency = speedup / omp_get_max_threads();

    // Print the results
    printf("Serial Time: %f seconds\n", serial_time);
    printf("Parallel Time: %f seconds\n", parallel_time);
    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    // Free allocated memory
    free(a);
    free(b);
    free(result_serial);
    free(result_parallel);

    return 0;
}

```
## Output
```plaintext
Serial Time: 0.000000 seconds
Parallel Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
```
