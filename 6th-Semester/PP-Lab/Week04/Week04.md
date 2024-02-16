# NOT FINAL
# Q1. Write a parallel program using OpenMP to implement the Selection sort algorithm. Compute the efficiency and plot the speed up for varying input size and thread number.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>SSE
#include <math.h>

void selection_sort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        #pragma omp parallel for shared(arr, min_idx) private(j)
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

double get_execution_time(int arr[], int n, int num_threads) {
    omp_set_num_threads(num_threads);
    double start_time = omp_get_wtime();
    selection_sort(arr, n);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
    int max_threads = omp_get_max_threads();

    printf("Selection Sort using OpenMP\n\n");
    printf("Number of threads: %d\n", max_threads);

    printf("\nInput size\tThreads\tExecution Time\tEfficiency\tSpeedup\n");

    for (int n = 10000; n <= 100000; n += 10000) {
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % n;
        }

        printf("%d\t\t%d\t", n, 1);
        double seq_time = get_execution_time(arr, n, 1);
        printf("%f\t%f\t%f\n", seq_time, 1.0, 1.0);

        for (int num_threads = 2; num_threads <= max_threads; num_threads++) {
            printf("%d\t\t%d\t", n, num_threads);
            double par_time = get_execution_time(arr, n, num_threads);
            double efficiency = seq_time / (num_threads * par_time);
            double speedup = seq_time / par_time;
            printf("%f\t%f\t%f\n", par_time, efficiency, speedup);
        }
    }

    return 0;
}

```
## Output
```plaintext

```
# Q2. Write a parallel program using openMP to implement the following: Take an array of input size m. Divide the array into two parts and sort the first half using insertion sort and second half using quick sort. Use two threads to perform these tasks. Use merge sort to combine the results of these two sorted arrays.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define MAX_SIZE 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);

        #pragma omp task shared(arr)
        quick_sort(arr, low, i);
        #pragma omp task shared(arr)
        quick_sort(arr, i + 2, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int main() {
    int arr[MAX_SIZE], n, i;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    double serial_start_time = omp_get_wtime();

    insertion_sort(arr, n);
    quick_sort(arr, 0, n - 1);
    merge(arr, 0, n / 2, n - 1);

    double serial_end_time = omp_get_wtime();
    double serial_execution_time = serial_end_time - serial_start_time;

    printf("\nSorted array (serial):\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Serial Execution Time: %lf seconds\n", serial_execution_time);

    double parallel_start_time = omp_get_wtime();

    omp_set_num_threads(2);

    #pragma omp parallel shared(arr)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            {
                insertion_sort(arr, n / 2);
            }

            #pragma omp section
            {
                quick_sort(arr, n / 2, n - 1);
            }
        }
    }

    merge(arr, 0, n / 2, n - 1);

    double parallel_end_time = omp_get_wtime();
    double parallel_execution_time = parallel_end_time - parallel_start_time;

    printf("\nSorted array (parallel):\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Parallel Execution Time: %lf seconds\n", parallel_execution_time);

    double speedup = serial_execution_time / parallel_execution_time;
    double efficiency = speedup / omp_get_max_threads();

    printf("Speedup: %lf\n", speedup);
    printf("Efficiency: %lf\n", efficiency);

    return 0;
}
```
## Output
```plaintext

```
# Q3.Write a parallel program using OpenMP to implement sequential search algorithm. Compute the efficiency and plot the speed up for varying input size and thread number.
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Sequential search algorithm
int sequentialSearch(int *arr, int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if not found
}

// Parallel search algorithm using OpenMP
int parallelSearch(int *arr, int size, int target, int num_threads) {
    int index = -1;

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            #pragma omp critical
            {
                if (index == -1 || i < index) {
                    index = i;
                }
            }
        }
    }

    return index;
}

int main() {
    int max_size = 1000000;
    int target = 42;  // Change the target value as needed

    printf("Size\tThreads\tTime\tSpeedup\tEfficiency\n");

    for (int size = 1000; size <= max_size; size *= 10) {
        for (int num_threads = 1; num_threads <= 8; num_threads *= 2) {
            int *arr = (int *)malloc(size * sizeof(int));

            // Initialize array with random values
            for (int i = 0; i < size; ++i) {
                arr[i] = rand() % 100;
            }

            double start_time = omp_get_wtime();

            // Uncomment one of the search methods below to test
            // int index = sequentialSearch(arr, size, target);
            int index = parallelSearch(arr, size, target, num_threads);

            double end_time = omp_get_wtime();

            free(arr);

            double elapsed_time = end_time - start_time;
            double speedup = elapsed_time / (end_time - start_time);
            double efficiency = speedup / num_threads;

            printf("%d\t%d\t%f\t%f\t%f\n", size, num_threads, elapsed_time, speedup, efficiency);
        }
    }

    return 0;
}
```
## Output
```plaintext

```