## Q1) Write a parallel program using OpenMP to perform vector addition, subtraction, multiplication. Demonstrate task level parallelism. Analyze the speedup and efficiency of the parallelized code. 

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
### Output
```plaintext
Serial Time: 0.000000 seconds
Parallel Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
```
## Q2) Write a parallel program using OpenMP to find sum of N numbers using the following constructs/clauses. 
#### a. Critical section 
#### b. Atomic 
#### c. Reduction 
#### d. Master 
#### e. Locks 
```c
#include <omp.h>
#include <stdio.h>

int main() {
  int n = 100;
  int sum = 0;

  #pragma omp parallel
  {
    #pragma omp critical
    {
      sum += 1;
      printf("After critical: %d\n", sum);
    }

    #pragma omp atomic
    sum += 1;
    printf("After atomic: %d\n", sum);

    #pragma omp for reduction(+:sum)
    for(int i=0; i<n; i++) {
      sum += i;
    }
    printf("After reduction: %d\n", sum);

    #pragma omp master
    {
      sum += 1;
      printf("After master: %d\n", sum);
    }

    omp_lock_t lock;
    omp_init_lock(&lock);
    omp_set_lock(&lock);
    sum += 1; 
    omp_unset_lock(&lock);
    omp_destroy_lock(&lock);
    printf("After lock: %d\n", sum);
  }

  printf("Final Sum = %d\n", sum);

  return 0;
}
```
### Output
```plaintext
After critical: 1
After atomic: 2
After critical: 3
After atomic: 74
After critical: 75
After atomic: 195
After critical: 196
After atomic: 365
After critical: 366
After atomic: 550
After critical: 551
After atomic: 771
After critical: 772
After atomic: 1028
After critical: 1029
After atomic: 1321
After critical: 1322
After atomic: 1650
After critical: 1651
After atomic: 2051
After critical: 2052
After atomic: 2416
After critical: 2417
After atomic: 2889
After critical: 2890
After atomic: 3398
After critical: 3399
After atomic: 3421
After critical: 3422
After atomic: 3858
After critical: 3859
After atomic: 4403
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After master: 4995
After reduction: 4982
After reduction: 4982
After lock: 4983
After lock: 4984
After lock: 4985
After lock: 4986
After lock: 4987
After lock: 4988
After lock: 4989
After lock: 4990
After lock: 4991
After lock: 4992
After lock: 4993
After lock: 4994
After reduction: 4982
After lock: 4996
After lock: 4997
After lock: 4998
After lock: 4999
Final Sum = 4999
```
## Q3) Write a parallel program using OpenMP to implement the Odd-even transposition sort. Vary the input size and analyse the program efficiency.
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void odd_even_sort(int *a, int n) {
    int phase, i, temp;

    for (phase = 0; phase < n; ++phase) {
        if (phase % 2 == 0) {
            // Even phase
            #pragma omp parallel for private(i, temp) shared(a)
            for (i = 1; i < n - 1; i += 2) {
                if (a[i] > a[i + 1]) {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
        } else {
            // Odd phase
            #pragma omp parallel for private(i, temp) shared(a)
            for (i = 0; i < n - 1; i += 2) {
                if (a[i] > a[i + 1]) {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int n, i;
    double start_time, end_time;

    // Vary the input size
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    // Initialize the array with random values
    for (i = 0; i < n; ++i) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }

    // Display the unsorted array
    printf("Unsorted array:\n");
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Measure time before sorting
    start_time = omp_get_wtime();

    // Sort the array using Odd-Even Transposition Sort
    odd_even_sort(arr, n);

    // Measure time after sorting
    end_time = omp_get_wtime();

    // Display the sorted array
    printf("\nSorted array:\n");
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Display the time taken for sorting
    printf("Time taken: %f seconds\n", end_time - start_time);

    free(arr);

    return 0;
}
```
### Output
```plaintext
Enter the size of the array: 15
Unsorted array:
41 67 34 0 69 24 78 58 62 64 5 45 81 27 61

Sorted array:
0 5 24 27 34 41 45 58 61 62 64 67 69 78 81
Time taken: 0.015000 seconds
```

## Q4) Write an OpenMP program to find the Summation of integers from a given interval. Analyze the performance of various iteration scheduling strategies.
```c
#include <stdio.h>
#include <omp.h>

#define N 1000000000

int main() {
    long long sum = 0;
    int i;

    // Static Scheduling
    double start_time_static = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_static = omp_get_wtime();

    printf("Sum using Static Scheduling: %lld\n", sum);
    printf("Time taken with Static Scheduling: %f seconds\n", end_time_static - start_time_static);

    sum = 0;

    // Dynamic Scheduling
    double start_time_dynamic = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_dynamic = omp_get_wtime();

    printf("\nSum using Dynamic Scheduling: %lld\n", sum);
    printf("Time taken with Dynamic Scheduling: %f seconds\n", end_time_dynamic - start_time_dynamic);

    sum = 0;

    // Guided Scheduling
    double start_time_guided = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(guided)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_guided = omp_get_wtime();

    printf("\nSum using Guided Scheduling: %lld\n", sum);
    printf("Time taken with Guided Scheduling: %f seconds\n", end_time_guided - start_time_guided);

    return 0;
}

```
### Output
```plaintext
Sum using Static Scheduling: 500000000500000000
Time taken with Static Scheduling: 0.093000 seconds

Sum using Dynamic Scheduling: 500000000500000000
Time taken with Dynamic Scheduling: 21.003000 seconds

Sum using Guided Scheduling: 500000000500000000
Time taken with Guided Scheduling: 0.084000 seconds
```

## Q5) Write a parallel program using OpenMP to generate the histogram of the given array A. 
`Hint: To generate histogram, we simply divide the range of the data up into equal sized sub intervals, or bins and determine the number of measurements (frequency) in each 
bin.`
#### Example: 
`1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3, 4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9`
```c
code
```
### Output
```plaintext
output
```
