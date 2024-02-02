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
# Q2. Write a parallel program using openMP to implement the following: Take an array of input size m. Divide the array into two parts and sort the first half using insertion sort and second half using quick sort. Use two threads to perform these tasks. Use merge sort to combine the results of these two sorted arrays.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
#define MAX_SIZE 100
 
// function to swap two elements in an array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// function to perform insertion sort on an array
void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
// function to perform quick sort on an array
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        // Select a pivot element and partition the array around it
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
 
        // Recursively sort the two partitions
        #pragma omp task shared(arr)
        quick_sort(arr, low, i);
        #pragma omp task shared(arr)
        quick_sort(arr, i + 2, high);
    }
}
 
// function to merge two sorted arrays into a single sorted array
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // create temporary arrays
    int L[n1], R[n2];
 
    // copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // merge the two arrays
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
int main() {
    int arr[MAX_SIZE], n, i;
 
    // get the size of the array from the user
    printf("Enter the size of the array: ");
    scanf("%d", &n);
 
    // get the elements of the array from the user
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
 
    // set the number of threads to use
    omp_set_num_threads(2);
 
    // sort the first half of the array using insertion sort and the second half using quick sort
    #pragma omp parallel shared(arr)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            {
                insertion_sort(arr, n/2);
            }
 
            #pragma omp section
            {
                quick_sort(arr, n/2 + 1, n-1);
            }
        }
    }
 
    // merge the two sorted halves of the array
    merge(arr, 0, n/2, n-1);
 
    // print the sorted array
    printf("\nSorted array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
 
    return 0;
}

```
# Q3.Write a parallel program using OpenMP to implement sequential search algorithm. Compute the efficiency and plot the speed up for varying input size and thread number.
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000 // Define the size of the array

// Function to perform sequential search on an array
int sequential_search(int *arr, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to perform parallel search on an array
int parallel_search(int *arr, int size, int target, int num_threads) {
    int index = -1;

    #pragma omp parallel num_threads(num_threads)
    {
        int local_index = -1;

        #pragma omp for
        for (int i = 0; i < size; i++) {
            if (arr[i] == target) {
                local_index = i;
            }
        }

        #pragma omp critical
        {
            if (local_index != -1 && index == -1) {
                index = local_index;
            }
        }
    }

    return index;
}

int main() {
    int predefined_array[ARRAY_SIZE];
    int target = 777; // Target element to search for

    // Initialize the predefined array with random values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        predefined_array[i] = rand() % 1000;
    }

    // Set the number of threads to use
    int num_threads_list[] = {2, 4, 8}; // Varying number of threads

    for (int i = 0; i < sizeof(num_threads_list) / sizeof(num_threads_list[0]); i++) {
        int num_threads = num_threads_list[i];
        int size = ARRAY_SIZE;

        // Size of the predefined array
        double start_time = omp_get_wtime();
        int result = parallel_search(predefined_array, size, target, num_threads);
        double end_time = omp_get_wtime();

        printf("Search Result with %d threads: %d\n", num_threads, result);
        printf("Search Time with %d threads: %f seconds\n", num_threads, end_time - start_time);

        // Compute efficiency and speedup
        double sequential_time = end_time - start_time;
        double parallel_time = end_time - start_time;
        double efficiency = sequential_time / (num_threads * parallel_time);
        double speedup = sequential_time / parallel_time;

        printf("Efficiency with %d threads: %f\n", num_threads, efficiency);
        printf("Speedup with %d threads: %f\n", num_threads, speedup);
    }

    return 0;
}

```
